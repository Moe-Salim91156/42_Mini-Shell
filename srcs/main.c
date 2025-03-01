/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/03/01 15:47:09 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   Updated: 2025/02/15 16:18:03 by yokitane         ###   ########.fr       */
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
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		free(current);
		current = temp;
	}
	free(cmd_list);
}

int	main(void)
{
	t_token_list	*tokens;
	char			*input;

	tokens = init_list();
	while (1)
	{
		input = readline(COLOR_MAGENTA "rbsh$ " COLOR_RESET);
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
			add_history(input);
			if (!tokenizer(input, tokens))
				return (0);
			lexing(tokens);
			expander_main(tokens);
			print_tokens(tokens);
			free_tokens(tokens);
			tokens = NULL;
			tokens = init_list();
		}
	}
	free(input);
	return (0);
}
