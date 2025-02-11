/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:20 by msalim            #+#    #+#             */
/*   Updated: 2025/02/11 19:40:30 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "../includes/minishell.h"

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
  cmd->count = 0;
  cmd->name = NULL;
	cmd->next = NULL;
	return (cmd);
}
