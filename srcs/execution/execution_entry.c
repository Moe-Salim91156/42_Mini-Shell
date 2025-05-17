/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 21:54:34 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fork_single_child(t_shell *shell, t_cmd *current_payload,
		int *status)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->last_status = 1;
		return ;
	}
	if (!pid)
	{
		set_signal(1);
		manage_child(shell, current_payload);
		restore_io(current_payload);
		ft_exit(shell, current_payload->exit_status);
	}
	set_signal(3);
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		current_payload->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		current_payload->exit_status = WTERMSIG(*status) + 128;
	if (current_payload->exit_status)
		child_perror(current_payload->exit_status, NULL);
}

int	execution_entry(t_shell *shell)
{
	t_cmd	*current_payload;
	int		heredoc_result;

	current_payload = shell->cmd_list->head;
	heredoc_result = process_all_heredocs(shell);
	if (heredoc_result == -1)
		return (shell->last_status);
	if (shell->cmd_list->payload_count == 1)
	{
		if (is_bltn(current_payload->argv))
			shell->last_status = manage_bltn(shell, current_payload, 0);
		else
			fork_single_child(shell, current_payload, &shell->last_status);
		shell->last_status = current_payload->exit_status;
	}
	else
		manage_pipeline(shell, shell->cmd_list->head,
			shell->cmd_list->payload_count);
	cleanup_all_heredocs(shell);
	set_signal(0);
	return (shell->last_status);
}
