/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 15:06:34 by msalim           ###   ########.fr       */
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
	int	i;
	int	start_quote;
	int	end_quote;

	i = 0;
	start_quote = 0;
	end_quote = ft_strlen(value) - 1;
	while (value[i] == quote)
	{
		start_quote++;
		i++;
	}
	if ((start_quote + end_quote) % 2 == 0)
		return (0);
	else
		return (1);
}

char	*extract_quotes(char *value, char quote)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(value) + 1);
	if (!result || !check_quotes_even_odd(value, quote))
		return (NULL);
	while (value[i])
	{
		if (value[i] != quote)
		{
			ft_strncpy(&result[j], &value[i], 1);
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	check_for_quotes_in_tokens(t_token_list *list)
{
	t_token	*current;
	char	*new_value;

	current = list->head;
	while (current)
	{
		if (is_single_quote_token(current->value))
		{
			new_value = extract_quotes(current->value, '\'');
			if (new_value)
			{
				free(current->value);
				current->value = new_value;
			}
		}
		current = current->next;
	}
}
