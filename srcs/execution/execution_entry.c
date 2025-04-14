/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 16:50:04 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handle heredocs
// handle redirections
// is_cmd
char	*locate_cmd(void)
{
}
int	execution_entry(t_shell *shell)
{

	t_cmd *current_payload;

	current_payload = shell->cmd_list->head;
	if (shell->cmd_list->count == 1)
	{
		if (is_bltn(current_payload->argv))//case1
		{
			shell->last_status = manage_bltn(shell);
		}
		else
		{
			//case 2
		}
	}
	else
		//case 3
	return (0);
}

