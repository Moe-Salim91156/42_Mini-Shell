/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:10:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/30 19:27:42 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*
 * Configures the command input/output file descriptors for piping
 */
static void	config_pipe_fds(t_cmd *cmd, int **pipes, int pipe_index, int cmd_count)
{

	if (pipe_index > 0)
	{
		cmd->in_fd = pipes[pipe_index - 1][0];
	}
	else if (cmd->has_heredoc && cmd->heredoc_fd > 0)
		cmd->in_fd = cmd->heredoc_fd;// heredoc first cmd case
	if (pipe_index < cmd_count - 1)
	{
		cmd->out_fd = pipes[pipe_index][1];
	}
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


void manage_fork(t_cmd *current, int **pipes, int pipe_index,int cmd_count,t_shell *shell)
{
	config_pipe_fds(current, pipes, pipe_index, cmd_count);
	close_unused_pipes(pipes, pipe_index, cmd_count);
	if (is_bltn(current->argv))
		shell->last_status = manage_bltn(shell, current);
	else
		manage_child(shell, current);
	exit(shell->last_status);
}

static void parent_close_pipes(int **pipes, int pipe_index, int cmd_count)
{
	if (pipe_index > 0)
	{
		close(pipes[pipe_index - 1][0]);
		pipes[pipe_index - 1][0] = -1;
	}
	if (pipe_index < cmd_count - 1)
	{
		close(pipes[pipe_index][1]);
		pipes[pipe_index][1] = -1;
	}
}

//this is just so I can lay out the logic, defentily needs a refactor and rework later.
void	manage_pipeline(t_shell *shell, t_cmd *list_head,int cmd_count)
{
	int		**pipes;
	int		pipe_index;
	pid_t	pids[2046];
	t_cmd	*current;

	pipes = lay_pipeline(cmd_count);
	if (!pipes)
		return ;
	current = list_head;
	pipe_index = 0;
	while (current && pipe_index < cmd_count)
	{
		pids[pipe_index] = fork();
		if (pids[pipe_index] == -1)
			fork_error(pipes, cmd_count);
		if (!pids[pipe_index])
			manage_fork(current, pipes, pipe_index, cmd_count, shell);
		parent_close_pipes(pipes, pipe_index, cmd_count);
		current = current->next;
		pipe_index++;
	}
	wait_for_children(shell, cmd_count, pids);
}
