/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:10 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 14:30:52 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_command(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		i;
	int		index;

	i = 0;
	index = 0;
	cmd = cmd_list->head;
	while (cmd)
	{
		printf("command %d\n", index);
		i = 0;
		while (cmd->args[i])
		{
			printf("args[%d] : %s\n", i, cmd->args[i]);
			i++;
		}
		printf("args[%d] : NULL\n", i);
		cmd = cmd->next;
		index++;
	}
	printf("number of arguments in total allocated %d\n", cmd_list->count);
}

void	print_tokens(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		lexemes(current);
		printf("token: ([%s] :: type %d)\n", current->value, current->type);
		current = current->next;
	}
}
