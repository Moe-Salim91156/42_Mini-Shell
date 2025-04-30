/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:17:42 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/30 19:28:24 by yokitane         ###   ########.fr       */
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
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
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

void fork_error(int **pipes, int cmd_count)
{
	close_pipes(pipes, cmd_count);
	perror("fork");
	exit(1);
}

void end_pipeline(t_shell *shell, int cmd_count , int *pids, int **pipes)
{
	wait_for_children(shell, cmd_count, pids);
	close_pipes(pipes, cmd_count);
	if (pipes)
	{
		int i = 0;
		while (i < cmd_count - 1 && pipes[i])
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}
