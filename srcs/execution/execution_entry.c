/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/28 23:09:17 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void fork_single_child(t_shell *shell, t_cmd *current_payload, int *status)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->last_status = 1;
		return;
	}
	if (!pid)
		manage_child(shell, current_payload);
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		current_payload->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		current_payload->exit_status = 128 + WTERMSIG(*status);
}

int	execution_entry(t_shell *shell)
{
	t_cmd	*current_payload;
	int		*status;
	int		heredoc_result;

	status = &shell->last_status;
	current_payload = shell->cmd_list->head;
	heredoc_result = process_all_heredocs(shell);
	if (heredoc_result == -1)
	{
		shell->last_status = 1;
		return (shell->last_status);
	}
	if (shell->cmd_list->payload_count == 1)
	{
		if (is_bltn(current_payload->argv))
			shell->last_status = manage_bltn(shell, current_payload);
		else
			fork_single_child(shell, current_payload, status);
		shell->last_status = current_payload->exit_status;
	}
	else
	{
		manage_pipeline(shell, shell->cmd_list->head);
	}
	cleanup_all_heredocs(shell);
	return (shell->last_status);
}
