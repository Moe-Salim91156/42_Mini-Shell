/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:22 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/07 13:32:53 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token_list *list)
{
	t_token	*current;
	t_token	*temp;

	current = list->head;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	free(list);
}

void	free_payload_array(char **payload_array)
{
	int	i;

	i = 0;
	if (!payload_array)
		return ;
	while (payload_array[i])
	{
		free(payload_array[i]);
		i++;
	}
	free(payload_array);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_command_list(t_cmd_list *cmd_list)
{
	t_cmd	*current;
	t_cmd	*temp;

	current = cmd_list->head;
	while (current)
	{
		free_split(current->payload_array);
		free_split(current->argv);
		free(current->type);
		temp = current->next;
		free(current);
		current = temp;
	}
	free(cmd_list);
}
