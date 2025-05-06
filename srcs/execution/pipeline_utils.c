/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:17:42 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/05 22:35:37 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	safe closure of pipes.
	*pass num of cmds not num of pipes.!!
*/
void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < cmd_count - 1 && pipes[i])
	{
		if (pipes[i][0] != -1)
			close(pipes[i][0]);
		if (pipes[i][1] != -1)
			close(pipes[i][1]);
		free(pipes[i]);
		pipes[i] = NULL;
		i++;
	}
	free(pipes);
	pipes = NULL;
}

t_pipe	*lay_pipeline(int cmd_count, t_pipe *tpipe)
{
	int	i;

	i = -1;
	tpipe->pipe_index = 0;
	tpipe->pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!tpipe->pipes)
		return (NULL);
	while (++i < cmd_count - 1)
	{
		tpipe->pipes[i] = malloc(sizeof(int) * 2);
		if (!tpipe->pipes[i])
		{
			close_pipes(tpipe->pipes, i);
			return (NULL);
		}
		tpipe->pipes[i][0] = -1;
		tpipe->pipes[i][1] = -1;
		if (pipe(tpipe->pipes[i]) == -1)
		{
			close_pipes(tpipe->pipes, i);
			return (NULL);
		}
	}
	return (tpipe);
}

void	fork_error(t_pipe *tpipe, int cmd_count, t_shell *shell)
{
	close_pipes(tpipe->pipes, cmd_count);
	free(tpipe);
	shell->last_status = -1;
	perror("fork");
	ft_exit(shell, 0);
}
void	pipe_error(t_shell *shell, t_pipe *tpipe)
{
	close_pipes(tpipe->pipes, tpipe->pipe_index);
	free(tpipe->pipes);
	tpipe->pipes = NULL;
	free(tpipe);
	shell->last_status = -1;
	ft_exit(shell, -1);
}
void	end_pipeline(t_shell *shell, int cmd_count, int *pids, t_pipe *pipe)
{
	wait_for_children(shell, cmd_count, pids);
	close_pipes(pipe->pipes, cmd_count);
	free(pipe);
	pipe = NULL;
}