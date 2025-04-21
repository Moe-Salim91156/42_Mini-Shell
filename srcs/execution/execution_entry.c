/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/21 18:31:37 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



static void fork_child(t_shell *shell, t_cmd *current_payload, int *status,int *pipe)
{
	int		pid;

	pid = fork();
	if (!pid)
		manage_child(shell, current_payload,pipe);//no child lives past this function.
	wait(status);
	if (WIFEXITED(*status))
		current_payload->exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		current_payload->exit_status = 128 + WTERMSIG(*status);
}

int	execution_entry(t_shell *shell)
{
	t_cmd	*current_payload;
	int		status;
	int		current_index;

	status = 0;
	current_index = 0;
	current_payload = shell->cmd_list->head;
	if (shell->cmd_list->payload_count == 1)
	{
		if (is_bltn(current_payload->argv))//case1
			shell->last_status = manage_bltn(shell, current_payload, NULL);
		else
			fork_child(shell, current_payload, &status,NULL);
	}
	// else
		//case 3
	shell->last_status = current_payload->exit_status;
	return (0);
}

