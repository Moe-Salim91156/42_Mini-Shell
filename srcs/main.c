/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/15 19:31:51 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	skip_beginning_spaces(char *str)
{
	while (*str == ' ')
		str++;
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

int	main(void)
{
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	char			*input;

	tokens = init_list();
	cmd_list = init_cmd_list();
	while (1)
	{
		input = readline(COLOR_MAGENTA "Ashen$ " COLOR_RESET);
		if (!input)
			break ;
		tokenize(input, tokens);
		print_tokens(tokens);
		build_cmd(tokens, cmd_list);
		print_command(cmd_list);
		free(input);
	}
	return (0);
}
