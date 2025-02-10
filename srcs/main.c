/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/10 16:36:36 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	skip_beginning_spaces(char *str)
{
	while (*str == ' ')
		str++;
}

void	tokenize(char *str, t_token_list *token)
{
	char	*pipe_token;
	char	*next_pipe;
	char	*word;

	pipe_token = str;
	while (pipe_token)
	{
		next_pipe = ft_strchr(pipe_token, '|');
		if (next_pipe)
		{
			*next_pipe = '\0';
			next_pipe++;
			while (*next_pipe == ' ')
				next_pipe++;
		}
		word = strtok(pipe_token, " ");
		while (word)
		{
			add_token(token, word);
			word = strtok(NULL, " ");
		}
		if (next_pipe)
			add_token(token, "|");
		pipe_token = next_pipe;
	}
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

int	main(void)
{
	t_token_list	*tokens;
	char			*input;

	tokens = init_list();
	while (1)
	{
		input = readline("Ashen$ ");
		if (!input)
			break ;
		tokenize(input, tokens);
		print_tokens(tokens);
		free(input);
	}
	return (0);
}
