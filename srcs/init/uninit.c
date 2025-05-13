/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:22 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/13 18:46:18 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token_list *list)
{
	t_token	*current;
	t_token	*temp;

	if (!list)
		return ;
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

void	free_split(char **split)
{
	int	i;

	if (!split && !split[0])
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

	if (!cmd_list)
		return ;
	current = cmd_list->head;
	while (current)
	{
		if (current->heredoc_delimiter)
			free(current->heredoc_delimiter);
		if (current->payload_array)
			free_split(current->payload_array);
		if (current->argv)
			free_split(current->argv);
		if (current->type)
			free(current->type);
		temp = current->next;
		free(current);
		current = temp;
	}
	free(cmd_list);
}
