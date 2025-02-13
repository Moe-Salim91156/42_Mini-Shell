/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:01:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/10 16:51:00 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize(char *str, t_token_list *token)
{
	char	*pipe_token;
	char	*next_pipe;
	char	*word;

	skip_beginning_spaces(str);
	pipe_token = str;
	while (pipe_token)
	{
		next_pipe = ft_strchr(pipe_token, '|');
		if (next_pipe)
		{
			*next_pipe = '\0';
			next_pipe++;
			skip_beginning_spaces(next_pipe);
		}
		word = strtok(pipe_token, " ");
		while (word)
		{
			add_token(token, word);
			word = strtok(NULL, " ");
		}
		if (next_pipe)
			add_token(token, "|");
		pipe_token = next_pipe;
	}
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
