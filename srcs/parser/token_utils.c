/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:01:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/16 17:31:13 by msalim           ###   ########.fr       */
/*   Updated: 2025/02/15 16:23:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_token_list *list, char *value)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = init_token();
	if (!new_node)
		return ;
	new_node->value = strdup(value);
	new_node->next = NULL;
	if (!list->head)
		list->head = new_node;
	else
	{
		temp = list->head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	list->size++;
}
