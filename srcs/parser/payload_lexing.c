/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload_lexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:34:41 by msalim            #+#    #+#             */
/*   Updated: 2025/04/09 17:11:20 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	assign_redirection_type(char **payload, t_token_type *type, int *i)
{
	if (!ft_strcmp(payload[*i], ">"))
		type[*i] = REDIRECT_OUT;
	else if (!ft_strcmp(payload[*i], "<"))
		type[*i] = REDIRECT_IN;
	else if (!ft_strcmp(payload[*i], ">>"))
		type[*i] = APPEND;
	else if (!ft_strcmp(payload[*i], "<<"))
	{
		type[*i] = HEREDOC;
		if (payload[*i + 1])
		{
			type[*i + 1] = HEREDOC_DELIMITER;
			(*i)++;
		}
	}
}

static void	handle_payload(char **payload, t_token_type *type)
{
	int	i;
	int	next_is_cmd;
	int	saw_redirect;

	i = 0;
	next_is_cmd = 1;
	saw_redirect = 0;
	while (payload[i])
	{
		if (!ft_strcmp(payload[i], "|"))
			type[i] = PIPE, next_is_cmd = 1, saw_redirect = 0;
		else if (!ft_strcmp(payload[i], "<<") || !ft_strcmp(payload[i], ">>")
			|| !ft_strcmp(payload[i], ">") || !ft_strcmp(payload[i], "<"))
			assign_redirection_type(payload, type, &i), saw_redirect = 1;
		else if (saw_redirect)
			type[i] = FILE_TOKEN, saw_redirect = 0;
		else if (next_is_cmd)
			type[i] = COMMAND, next_is_cmd = 0;
		else
			type[i] = ARGS;
		i++;
	}
	type[i] = -1;
}


void	lexer_cmd_list(t_cmd_list *list)
{
	t_cmd	*cmd;
	int		i;

	cmd = list->head;
	while (cmd)
	{
		i = 0;
		while (cmd->payload_array[i])
			i++;
		cmd->type = malloc(sizeof(t_token_type) * (i + 1));
		if (!cmd->type)
			exit(1);
		handle_payload(cmd->payload_array, cmd->type);
		cmd = cmd->next;
	}
}

