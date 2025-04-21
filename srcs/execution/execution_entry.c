/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/21 18:47:27 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




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

