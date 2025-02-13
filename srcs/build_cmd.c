/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:21:51 by msalim            #+#    #+#             */
/*   Updated: 2025/02/13 18:51:23 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd_tokens(t_token_list *list)
{
	t_token	*current;
	int		arg_cmd;

	arg_cmd = 0;
	current = list->head;
	while (current)
	{
		if (current->type == WORD || current->type == ARGS)
			arg_cmd++;
		current = current->next;
	}
	return (arg_cmd);
}

char	**allocate_cmd_args(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	return (args);
}

void	fill_command(t_cmd *cmd, t_token_list *list)
{
	t_token	*current;
	int		i;

	current = list->head;
	i = 0;
	while (current)
	{
		/*
			* sepeartion will be here, this should and will be refactored
			* but the idea is there and its working,
			* yes i've used gpt code lastly but i came up with the code
			* it just added few checks and corrected a stupid move im doing;
			* now we have each command has its args 2d array that contains
			* the command name and its arguments;
			*
			*/
		if (current->type == PIPE)
		{
			cmd->args[i] = NULL;
			cmd->next = init_command();
			if (!cmd->next)
			{
				fprintf(stderr, "Error: malloc failed for cmd->next\n");
				return ;
			}
			cmd = cmd->next;
			cmd->args = allocate_cmd_args(count_cmd_tokens(list));
			if (!cmd->args)
				return ;
			i = 0;
		}
		else
		{
			if (!current->value)
			{
				fprintf(stderr, "Error: current->value is NULL\n");
				return ;
			}
			cmd->args[i] = malloc(strlen(current->value) + 1);
			if (!cmd->args[i])
			{
				fprintf(stderr, "Error: malloc failed for cmd->args[i]\n");
				return ;
			}
			strcpy(cmd->args[i], current->value);
			i++;
		}
		current = current->next;
	}
	cmd->args[i] = NULL;
}

t_cmd	*build_cmd(t_token_list *list, t_cmd_list *cmd_list)
{
	t_cmd	*cmd;

	cmd_list->count = count_cmd_tokens(list);
	cmd_list->head = init_command();
	if (!cmd_list->head)
	{
		fprintf(stderr, "Error: malloc failed for cmd_list->head\n");
		return (NULL);
	}
	cmd = cmd_list->head;
	cmd->args = allocate_cmd_args(cmd_list->count);
	if (!cmd->args)
		return (NULL);
	fill_command(cmd, list);
	return (cmd_list->head);
}
