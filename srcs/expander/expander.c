/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/02/28 19:13:40 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_first_quote(char *value)
{
	int		i;
	char	s_quote;
	char	d_quote;

	s_quote = '\'';
	d_quote = '\"';
	i = 0;
	while (value[i] && value[i] != s_quote && value[i] != d_quote)
		i++;
	if (value[i] == s_quote)
		return (1);
	if (value[i] == d_quote)
		return (2);
	else
		return (0);
}

int	has_env_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

char	*double_quote_mode(char *value, int *index)
{
	int		start;
	int		len;
	char	*temp;

	start = *index + 1;
	len = 0;
	while (value[start + len] && value[start + len] != '\"')
		len++;
	temp = malloc(len + 1);
	ft_strncpy(temp, value + start, len);
	temp[len] = '\0';
	*index = start + len + 1;
	return (temp);
}

char	*single_quote_mode(char *value, int *index)
{
	int		start;
	int		len;
	char	*temp;

	start = *index + 1;
	len = 0;
	while (value[start + len] && value[start + len] != '\'')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, value + start, len);
	temp[len] = '\0';
	*index = start + len + 1;
	return (temp);
}

char	*append_mode_result(char *result, char *mode_result)
{
	char	*new_result;

	if (!mode_result)
		return (result);
	new_result = ft_strjoin(result, mode_result);
	free(result);
	free(mode_result);
	return (new_result);
}

char	*normal_mode(char *value, int *index)
{
	int		start;
	int		len;
	char	*temp;

	start = *index;
	len = 0;
	while (value[start + len] && value[start + len] != '\'' && value[start
		+ len] != '\"')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, value + start, len);
	temp[len] = '\0';
	*index = start + len;
	return (temp);
}

char	*handle_quotes_mode(char *value)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '\'')
			temp = single_quote_mode(value, &i);
		else if (value[i] == '\"')
			temp = double_quote_mode(value, &i);
		else
			temp = normal_mode(value, &i);
		result = append_mode_result(result, temp);
	}
	return (result);
}

char	*expander_main(t_token_list *list)
{
	t_token	*current;
	char	*result;

	current = list->head;
	while (current)
	{
		if (ft_strchr(current->value, '\'') || ft_strchr(current->value, '\"'))
		{
			result = handle_quotes_mode(current->value);
			if (!result)
				return (NULL);
			if (result)
			{
				free(current->value);
				current->value = result;
			}
		}
		current = current->next;
	}
	return (result);
}
