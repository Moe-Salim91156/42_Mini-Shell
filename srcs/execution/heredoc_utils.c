/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:14:53 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/13 18:51:29 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Cleans up heredoc resources for a command
** Closes any open heredoc file descriptors
*/
int	run_heredoc(t_cmd *cmd, t_shell *shell, char **envp)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	set_signal(4);
	if (heredoc_read_loop(cmd, envp, pipefd[1], shell) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		set_signal(0);
		return (-1);
	}
	close(pipefd[1]);
	set_signal(0);
	return (pipefd[0]);
}

int	heredoc_init_and_handle_signal(t_shell *shell, int write_fd, int *infd)
{
	*infd = dup(STDIN_FILENO);
	if (*infd == -1)
		return (-1);
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		cleanup_all_heredocs(shell);
		close(write_fd);
		dup2(*infd, STDIN_FILENO);
		close(*infd);
		shell->last_status = 130;
		return (-1);
	}
	return (0);
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
