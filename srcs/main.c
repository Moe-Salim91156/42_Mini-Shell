/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/04/09 16:39:44 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_beginning_spaces(char *str)
{
	while (*str == ' ')
		str++;
}

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

void	free_command_list(t_cmd_list *cmd_list)
{
	t_cmd	*current;
	t_cmd	*temp;
	int		i;

	current = cmd_list->head;
	while (current)
	{
		temp = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
				free(current->argv[i++]);
			free(current->argv);
		}
		free(current);
		current = temp;
	}
	free(cmd_list);
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
		input = readline("rbsh$ ");
		if (!input)
			break ;
		if (input)
		{
			if (!strcmp(input, "exit"))
			{
				free_tokens(tokens);
				free(input);
				exit(1);
			}
			if (!strcmp(input, "pwd"))
			{
				bltn_pwd();
				// exit(1);
			}
			add_history(input);
			if (!tokenizer(input, tokens))
				return (0);
			lexing(tokens);
			print_tokens(tokens);
			expander_main(tokens);
			build_cmd(tokens, cmd_list);
      lexer_cmd_list(cmd_list);
			print_command(cmd_list);
			locate_heredoc(cmd_list);
			free_tokens(tokens);
			free_command_list(cmd_list);
			tokens = NULL;
			tokens = init_list();
			cmd_list = init_cmd_list();
		}
	}
	free(input);
	return (0);
}
