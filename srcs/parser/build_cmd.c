/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:21:51 by msalim            #+#    #+#             */
/*   Updated: 2025/02/16 17:30:07 by msalim           ###   ########.fr       */
/*   Updated: 2025/02/15 16:23:27 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	is_seperator(int type)
{
	/*
		* here we would put the NEWLINE enum new value
		* for seperating commands(payload);
		* */
	return (type == PIPE);
}

int	add_argument(t_cmd *cmd, t_token *current, int i)
{
	/*
		* this func simply adds payload args in the cmd->args array;
		* example :
		* [ls],[-l],[NULL]
		*/
	if (!current->value)
	{
		ft_putstr_fd("Error: Value NULL\n", 2);
		return (0);
	}
	cmd->args[i] = malloc(ft_strlen(current->value) + 1);
	if (!cmd->args[i])
		return (0);
	ft_strcpy(cmd->args[i], current->value);
	return (i + 1);
}

t_cmd	*handle_seperator(t_cmd *cmd, t_token_list *list)
{
	/*
		* when finding a new seperator (pipe, newline);
		* it means there is new command (payload);
		* this function does the magic
		* inits a new command
		* and moves to it
		* */
	cmd->next = init_command();
	if (!cmd->next)
	{
		ft_putstr_fd("erorr init-ing new command\n", 2);
		// free
		exit(1);
	}
	cmd = cmd->next;
	cmd->args = allocate_cmd_args(count_cmd_tokens(list));
	if (!cmd->args)
	{
		ft_putstr_fd("error mallocating a new args\n", 2);
		// free
		exit(1);
	}
	return (cmd);
}

void	fill_command(t_cmd *cmd, t_token_list *list)
{
	t_token	*current;
	int		i;

	/*
		* this function is responsible for calling all the functions mentioned above
		* handling seperator, add_argument
		* result is payload(0) , payload(1);
		* command(0), command(1);
		* u get the idea;
		* this was one functions nightmare
		* all i did is norminette and seperate them
		*/
	current = list->head;
	i = 0;
	while (current)
	{
		if (is_seperator(current->type))
		{
			cmd->args[i] = NULL;
			cmd = handle_seperator(cmd, list);
			i = 0;
		}
		else
		{
			i = add_argument(cmd, current, i);
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
		ft_putstr_fd("Error mallocating first command", 2);
		return (NULL);
	}
	cmd = cmd_list->head;
	cmd->args = allocate_cmd_args(cmd_list->count);
	if (!cmd->args)
		return (NULL);
	fill_command(cmd, list);
	return (cmd_list->head);
}
