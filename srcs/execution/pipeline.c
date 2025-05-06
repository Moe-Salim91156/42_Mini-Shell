/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:10:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/05 23:28:09 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Configures the command input/output file descriptors for piping
 */
static void	config_pipe_fds(t_cmd *cmd, int **pipes, int pipe_index,
		int cmd_count)
{
	if (pipe_index > 0)
	{
		cmd->in_fd = pipes[pipe_index - 1][0];
	}
	else if (cmd->has_heredoc && cmd->heredoc_fd > 0)
		cmd->in_fd = cmd->heredoc_fd; // heredoc first cmd case
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

void	manage_fork(t_cmd *current, t_pipe *pipe, int cmd_count, t_shell *shell)
{
	config_pipe_fds(current, pipe->pipes, pipe->pipe_index, cmd_count);
	close_unused_pipes(pipe->pipes, pipe->pipe_index, cmd_count);
	if (is_bltn(current->argv))
		shell->last_status = manage_bltn(shell, current, 1);
	else
		manage_child(shell, current);
	ft_exit(shell, 0);
}

static void	parent_close_pipes(int **pipes, int pipe_index, int cmd_count)
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

void	manage_pipeline(t_shell *shell, t_cmd *list_head, int cmd_count)
{
	pid_t	pids[2046];
	t_cmd	*current;
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		ft_exit(shell, -1);
	if (!lay_pipeline(cmd_count, pipe))
		pipe_error(shell, pipe);
	current = list_head;
	while (current && pipe->pipe_index < cmd_count)
	{
		pids[pipe->pipe_index] = fork();
		if (pids[pipe->pipe_index] == -1)
			fork_error(pipe, cmd_count, shell);
		if (!pids[pipe->pipe_index])
			manage_fork(current, pipe, cmd_count, shell);
		parent_close_pipes(pipe->pipes, pipe->pipe_index, cmd_count);
		restore_io(current);
		current = current->next;
		pipe->pipe_index++;
	}
	end_pipeline(shell, cmd_count, pids, pipe);
}
