/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:01:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/10 16:07:59 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_list	*init_list(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->size = 0;
	return (token_list);
}

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

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
  token->type = 0;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

t_cmd	*init_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}
