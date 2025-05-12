/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:20 by msalim            #+#    #+#             */
/*   Updated: 2025/05/11 16:08:55 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_separator(char *input, int *i, int *start, t_token_list *tokens)
{
	substr_and_add(input, *start, *i, tokens);
	if (input[*i] == '|')
		add_token(tokens, "|");
	(*i)++;
	*start = *i;
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

int	handle_quotes(char *input, int *i, t_shell *shell)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		printf("Syntax error: unclosed quote\n");
		shell->last_status = 127;
		return (0);
	}
	(*i)++;
	return (1);
}

int	tokenizer(char *input, t_token_list *tokens, t_shell *shell)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i])
	{
		if (is_seperator_token(input[i]))
			handle_separator(input, &i, &start, tokens);
		else if (is_redirect(input[i]))
		{
			if (handle_redirect(input, &i, &start, tokens))
				return (0);
		}
		else if (is_quotes(input[i]))
		{
			if (!handle_quotes(input, &i, shell))
				return (0);
		}
		else
			i++;
	}
	add_last_token(input, start, i, tokens);
	return (1);
}
