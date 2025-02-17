/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:20 by msalim            #+#    #+#             */
/*   Updated: 2025/02/17 18:43:21 by msalim           ###   ########.fr       */
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

void	handle_redirect(char *input, int *i, int *start, t_token_list *tokens)
{
  char  *result;

  substr_and_add(input, *start, *i, tokens);
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
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
}
void	handle_quotes(char *input, int *start, int *i, t_token_list *tokens)
{
  char  *result;
  char  quote;

  quote = input[*i] + 1;
  while (input[*i] && input[*i] != quote)
    (*i)++;
  result = ft_substr(input, *start, *i);
  add_token(tokens,result);
  free(result);
  *start = *i;
}

void	tokenizer(char *input, t_token_list *tokens)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	skip_beginning_spaces(input);
	while (input[i])
	{
		if (is_seperator_token(input[i]))
			handle_separator(input, &i, &start, tokens);
		else if (is_redirect(input[i]))
			handle_redirect(input, &i, &start, tokens);
		else if (is_quotes(input[i]))
		{
			handle_quotes(input, &start, &i, tokens);
		}
		else
			i++;
	}
	add_last_token(input, start, i, tokens);
}
