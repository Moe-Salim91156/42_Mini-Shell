/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/21 17:43:38 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execution_entry(t_shell *shell)
{
	t_cmd	*current_payload;
	int		pid;
	int		status;

	current_payload = shell->cmd_list->head;
	if (shell->cmd_list->payload_count == 1)
	{
		if (is_bltn(current_payload->argv)) // case1
			shell->last_status = manage_bltn(shell, current_payload, NULL);
		else
		{
			pid = fork();
			if (!pid)
				manage_child(shell, current_payload, NULL);
					// no child lives past this function.
			wait(&status);
			if (WIFEXITED(status))
				current_payload->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				current_payload->exit_status = 128 + WTERMSIG(status);
		}
	}
	else
		// case 3
		return (0);
	return (-1);
}
