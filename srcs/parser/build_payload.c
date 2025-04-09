/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:21:51 by msalim            #+#    #+#             */
/*   Updated: 2025/04/05 17:19:17 by yokitane         ###   ########.fr       */
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
		if (current->type != PIPE)
			arg_cmd++;
		current = current->next;
	}
	return (arg_cmd);
}

/*
 * this func simply adds payload argv in the cmd->argv array;
 * example :
 * [ls],[-l],[NULL]
 */

int	add_argument(t_cmd *cmd, t_token *current, int i)
{
	if (!current->value)
	{
		ft_putstr_fd("Error: Value NULL\n", 2);
		return (0);
	}
	cmd->payload_array[i] = malloc(ft_strlen(current->value) + 1);
	if (!cmd->payload_array[i])
		return (0);
	ft_strcpy(cmd->payload_array[i], current->value);
	return (i + 1);
}

/*
 * when finding a new seperator (pipe, newline);
 * it means there is new command (payload);
 * this function does the magic
 * inits a new command
 * and moves to it
 * */

t_cmd	*handle_seperator(t_cmd *cmd, t_token_list *list)
{
	cmd->next = init_command();
	if (!cmd->next)
	{
		ft_putstr_fd("erorr init-ing new command\n", 2);
		/* free */
		exit(1);
	}
	cmd = cmd->next;
	cmd->payload_array = allocate_cmd_argv(count_cmd_tokens(list));
	if (!cmd->payload_array)
	{
		ft_putstr_fd("error mallocating a new argv\n", 2);
		// free
		exit(1);
	}
	return (cmd);
}

/*
 * this function is responsible for calling all the functions mentioned above
 * handling seperator, add_argument
 * result is payload(0) , payload(1);
 * command(0), command(1);
 * u get the idea;
 * this was one functions nightmare
 * all i did is norminette and seperate them
 */

void	fill_command(t_cmd *cmd, t_token_list *list)
{
	t_token	*current;
	int		i;

	current = list->head;
	i = 0;
	while (current)
	{
		if (is_seperator(current->type))
		{
			cmd->payload_array[i] = NULL;
			cmd = handle_seperator(cmd, list);
			i = 0;
		}
		else
		{
			i = add_argument(cmd, current, i);
		}
		current = current->next;
	}
	cmd->payload_array[i] = NULL;
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
	cmd->payload_array = allocate_cmd_argv(cmd_list->count);
	if (!cmd->payload_array)
		return (NULL);
	fill_command(cmd, list);
	return (cmd_list->head);
}
