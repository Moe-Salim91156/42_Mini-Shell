/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 19:43:26 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_single_quote_token(char *token)
{
	if (ft_strchr(token, '\''))
		return (1);
	else
		return (0);
}

int	check_quotes_even_odd(char *value, char quote)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == quote)
			count++;
		i++;
	}
	return (count % 2 == 0);
}

char	*extract_single_quotes(char *value, char quote)
{
	int		i;
	int		j;
	int		new_len;
	char	*result;

	i = 0;
	j = 0;
	new_len = 0;
	while (value[i])
	{
		if (value[i] != quote)
			new_len++;
		i++;
	}
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] != quote && value[i])
			result[j++] = value[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	is_double_quote_token(char *value)
{
	if (ft_strchr(value, '\"'))
		return (1);
	else
		return (0);
}

int	check_for_quotes_in_tokens(t_token_list *list)
{
	t_token	*current;
	char	*new_value;

	current = list->head;
	while (current)
	{
		if (is_single_quote_token(current->value))
		{
			// if (!check_validation_of_quotes(current->value, '\''))
			// return (0);
			new_value = extract_single_quotes(current->value, '\'');
			if (new_value)
			{
				free(current->value);
				current->value = new_value;
			}
		}
		current = current->next;
	}
	return (1);
}
