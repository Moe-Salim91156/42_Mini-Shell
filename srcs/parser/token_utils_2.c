/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:23:31 by msalim            #+#    #+#             */
/*   Updated: 2025/05/14 11:06:47 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	substr_and_add(char *input, int start, int i, t_token_list *tokens)
{
	char	*result;

	if (i > start)
	{
		result = ft_substr(input, start, i - start);
		if (!result)
			return (0);
		if (!add_token(tokens, result))
			return (0);
		free(result);
	}
	return (1);
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

char	*handle_redirect_helper(char *input, int *i, t_token_list *tokens)
{
	char	*result;

	result = ft_substr(input, *i, 1);
	if (!result)
		return (NULL);
	add_token(tokens, result);
	free(result);
	return (input);
}

int	is_invalid_redirection(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
	{
		printf("syntax error\n");
		return (0);
	}
	return (1);
}

int	handle_separator(char *input, int *i, int *start, t_token_list *tokens)
{
	if (!substr_and_add(input, *start, *i, tokens))
		return (-1);
	if (input[*i] == '|')
		if (!add_token(tokens, "|"))
			return (-1);
	(*i)++;
	*start = *i;
	return (1);
}
