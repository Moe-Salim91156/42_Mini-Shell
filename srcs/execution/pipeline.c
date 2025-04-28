/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:10:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/29 00:21:07 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


/*
	safe closure of pipes.
	*pass num of cmds not num of pipes.!!
*/
void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	if (pipes == 0)
		return ;
	i = 0;
	while (i < cmd_count - 1 && pipes[i])
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**lay_pipeline(int cmd_count)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc(sizeof(int *) , (cmd_count - 1));
	if (!pipes)
		return (NULL);
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			close_pipes(pipes, i);
			return (NULL);
		}
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		if (pipe(pipes[i]) == -1)
		{
			close_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/*
 * Configures the command input/output file descriptors for piping
 */
static void	config_pipe_fds(t_cmd *cmd, int **pipes, int pipe_index, int cmd_count)
{
	if (cmd->has_heredoc && cmd->heredoc_fd > 0)
	{
		if (pipe_index == 0)
			cmd->in_fd = cmd->heredoc_fd;
		else
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
			cmd->in_fd = pipes[pipe_index - 1][0];
		}
	}
	else if (pipe_index > 0)
		cmd->in_fd = pipes[pipe_index - 1][0];
	if (pipe_index < cmd_count - 1)
		cmd->out_fd = pipes[pipe_index][1];
}

/*
 * Closes file descriptors that aren't needed by the current command
 */
static void	close_unused_pipes(int **pipes, int pipe_index, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (i != pipe_index - 1)
			if (pipes[i][0] != -1)
				close(pipes[i][0]);
		if (i != pipe_index)
			if (pipes[i][1] != -1)
				close(pipes[i][1]);
		i++;
	}
}

//this is just so I can lay out the logic, defentily needs a refactor and rework later.
void	manage_pipeline(t_shell *shell, t_cmd *list_head)
{
	int		**pipes;
	int		pipe_index;
	pid_t	pids[2046];
	t_cmd	*current;
	int		cmd_count;

	cmd_count = shell->cmd_list->payload_count;
	pipes = lay_pipeline(cmd_count);
	if (!pipes)
		return ;
	current = list_head;
	pipe_index = 0;
	while (current && pipe_index < cmd_count)
	{
		config_pipe_fds(current, pipes, pipe_index, cmd_count);
		pids[pipe_index] = fork();
		if (pids[pipe_index] == -1)
		{
			close_pipes(pipes, cmd_count);
			perror("fork");
			exit(1);
		}
		if (!pids[pipe_index])
		{
			close_unused_pipes(pipes, pipe_index, cmd_count);
			if (is_bltn(current->argv))
				shell->last_status = manage_bltn(shell, current);
			else
				manage_child(shell, current);
			exit(shell->last_status);
		}
		if (pipe_index > 0 && pipes[pipe_index - 1][0] != -1)
			close(pipes[pipe_index - 1][0]);
		if (pipe_index < cmd_count - 1 && pipes[pipe_index][1] != -1)
			close(pipes[pipe_index][1]);
		current = current->next;
		pipe_index++;
	}
	wait_for_children(shell, shell->cmd_list->payload_count, pids);
}
