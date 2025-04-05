/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:10 by msalim            #+#    #+#             */
/*   Updated: 2025/04/05 17:19:17 by yokitane         ###   ########.fr       */
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
		printf("Payload %d\n", index);
		i = 0;
		while (cmd->argv[i])
		{
			printf("argv[%d] : %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("argv[%d] : NULL\n", i);
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
		printf("token: ([%s] :: type %d)\n", current->value, current->type);
		current = current->next;
	}
}
