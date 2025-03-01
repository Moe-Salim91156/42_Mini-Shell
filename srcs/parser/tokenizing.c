/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:20 by msalim            #+#    #+#             */
/*   Updated: 2025/02/25 19:27:05 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	substr_and_add(char *input, int start, int i, t_token_list *tokens)
{
	char	*result;

	if (i > start)
	{
		result = ft_substr(input, start, i - start);
		add_token(tokens, result);
		free(result);
	}
}

void	handle_separator(char *input, int *i, int *start, t_token_list *tokens)
{
	substr_and_add(input, *start, *i, tokens);
	if (input[*i] == '|')
		add_token(tokens, "|");
	(*i)++;
	*start = *i;
}

int	is_invalid_redirection(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
	{
		printf("syntax error\n");
		return (1); // Invalid redirection pattern
	}
	return (0);
}

int	handle_redirect(char *input, int *i, int *start, t_token_list *tokens)
{
	char	*result;

	if (is_invalid_redirection(input, *i))
		return (1);
	substr_and_add(input, *start, *i, tokens);
	if (input[*i] == '>' && input[*i + 1] == '>' && input[*i + 2] != '>')
	{
		add_token(tokens, ">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<' && input[*i + 2] != '<')
	{
		add_token(tokens, "<<");
		*i += 2;
	}
	else
	{
		result = ft_substr(input, *i, 1);
		add_token(tokens, result);
		free(result);
		(*i)++;
	}
	*start = *i;
	return (0);
}

int	handle_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		printf("Syntax error: unclosed quote\n");
		return (0);
	}
	(*i)++;
	return (1);
}

int	tokenizer(char *input, t_token_list *tokens)
{
	int	i;
	int	start;
	int	result;

	i = 0;
	start = 0;
	skip_beginning_spaces(input);
	while (input[i])
	{
		if (is_seperator_token(input[i]))
			handle_separator(input, &i, &start, tokens);
		else if (is_redirect(input[i]))
		{
			result = handle_redirect(input, &i, &start, tokens);
			if (result == 1)
				return (0);
		}
		else if (is_quotes(input[i]))
		{
			if (!handle_quotes(input, &i))
				return (0);
		}
		else
			i++;
	}
	add_last_token(input, start, i, tokens);
	return (1);
}
