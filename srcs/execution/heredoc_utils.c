/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:14:53 by yokitane          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Cleans up heredoc resources for a command
** Closes any open heredoc file descriptors
*/


/*static void	handle_child_heredoc(t_cmd *p, t_shell *s, char **envp, int *fd)
{
	close(fd[0]);
	set_signal(3);
  heredoc_read_loop(p, envp, fd[1],s);
  if (g_sig == SIGINT)
  {
    close(fd[1]);
    printf("exited in child");
    ft_exit(s,SIGINT);
  }
  close(fd[1]);
  ft_exit(s,130);
}
static int	handle_parent_heredoc(pid_t pid, int *fd, t_shell *s)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	set_signal(0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
	{
		close(fd[0]);
		s->last_status = 130;
    ft_exit(s,SIGINT);
		return (-1);
	}
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		s->last_status = 128 + WTERMSIG(status);
		return (-1);
	}
	return (fd[0]);
}
*/
int	run_heredoc(t_cmd *cmd, t_shell *shell, char **envp, t_cmd *head)
{
	int	pipefd[2];

	(void)head;
	if (pipe(pipefd) == -1)
		return (-1);

	set_signal(3);
	if (heredoc_read_loop(cmd, envp, pipefd[1], shell) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		set_signal(0);
		return (-1);
	}
	close(pipefd[1]);
	set_signal(0);
	return pipefd[0];
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
