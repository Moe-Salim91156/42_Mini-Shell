/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:10:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/26 23:52:33 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"


/*
	safe closure of pipes.
	*pass num of cmds not num of pipes.!!
*/
void close_pipes(int **pipes, int cmd_count)
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
	pipes = ft_calloc(sizeof(int *) , (cmd_count - 1));//not sure about calloc, need to checl
	if (!pipes)														//but could help in a cleaner exit(null ended array)
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
			close_pipes( pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

//mess of a function.. I need sleep and this needs a big refactor.
void	manage_pipeline(t_shell *shell, t_cmd *list_head, int *status)
{
	int		**pipes;
	int		pipe_index;
	int		pid;
	t_cmd	*visit;

	pipes = lay_pipeline(shell->cmd_list->payload_count);
	if (!pipes)
		exit(1);
	visit = list_head;
	pipe_index = 0;
	while (list_head)
	{
		if (list_head->next)
		{
			list_head->out_fd = pipes[pipe_index][1];
			list_head->in_fd = pipes[pipe_index - 1][0];
		}
		locate_heredoc(visit, shell);
		*status = parse_redirs(visit, visit->argv);
		pid = fork();
		if (pid == -1)
		{
			close_pipes(pipes, shell->cmd_list->payload_count);
			perror("fork");
			exit(1);// merge into exit handler later 😴
		}
		if (!pid)
		{
			if (is_bltn(list_head->argv))
				shell->last_status = manage_bltn(shell, list_head, pipes[pipe_index], pipe_index);
			else
				manage_child(shell, list_head, pipes[pipe_index], pipe_index);
		}

		list_head = list_head->next;
		pipe_index++;
	}
}
