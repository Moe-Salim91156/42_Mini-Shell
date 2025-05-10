/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:14:53 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/10 20:00:45 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Cleans up heredoc resources for a command
** Closes any open heredoc file descriptors
*/

static void	handle_child_heredoc(t_cmd *p, t_shell *s, char **envp, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_read_loop(p, envp, fd[1]);
	close(fd[1]);
	s->last_status = 130;
	free_split(envp);
}

static int	handle_parent_heredoc(pid_t pid, int *fd, t_shell *s)
{
	int	status;

	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signal(0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		s->last_status = 130;
		close(fd[0]);
		g_sig = SIGINT;
		return (-1);
	}
	return (fd[0]);
}

int	run_heredoc(t_cmd *p, t_shell *s, char **envp, t_cmd *head)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		handle_child_heredoc(p, s, envp, fd);
		free(p->heredoc_delimiter);
		while (head != p)
		{
			if (head->heredoc_fd > 0)
				close(head->heredoc_fd);
			head = head->next;
		}
		ft_exit(s, 130);
	}
	else if (pid > 0)
		return (handle_parent_heredoc(pid, fd, s));
	close(fd[0]);
	close(fd[1]);
	return (-1);
}

void	cleanup_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_fd > 0)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (cmd->heredoc_delimiter)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
	}
	cmd->has_heredoc = 0;
}

/*
** Cleans up all heredoc resources for all commands in the shell
*/
void	cleanup_all_heredocs(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd_list->head;
	while (current)
	{
		cleanup_heredoc(current);
		current = current->next;
	}
}
