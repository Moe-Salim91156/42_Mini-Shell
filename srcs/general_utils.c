/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:49:28 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 16:51:36 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_payloads(t_cmd_list *list)
{
	t_cmd	*pay;

	pay = list->head;
	while (pay)
	{
		list->payload_count++;
		pay = pay->next;
	}
	return (list->payload_count);
}
