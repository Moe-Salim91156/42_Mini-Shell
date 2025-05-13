/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:01:06 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 13:34:53 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_seperator_token(char c)
{
	return (c == ' ' || c == '|');
}

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_redirect(char c)
{
	return (c == '>' || c == '<');
}

int	add_last_token(char *input, int start, int i, t_token_list *tokens)
{
	char	*result;

	if (start < i)
	{
		result = ft_substr(input, start, i - start);
		if (!result)
			return (0);
		if (!add_token(tokens, result))
			return (0);
		free(result);
	}
	return (1);
}

int	add_token(t_token_list *list, char *value)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = init_token();
	if (!new_node)
		return (0);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (0);
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
	return (1);
}
