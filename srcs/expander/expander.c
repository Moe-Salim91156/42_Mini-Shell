/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/03/02 14:40:21 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_env_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
char	*extract_env_value_from_name(char *value)
{
	char	*result;

	result = getenv(value);
	if (result == NULL)
		return (ft_strdup(""));
	else
		return (result);
}

char	*get_before_str(char *value, int *before)
{
	char	*before_str;

	*before = 0;
	while (value[*before] && value[*before] != '$')
		(*before)++;
	before_str = malloc(*before + 1);
	if (!before_str)
		return (NULL);
	ft_strncpy(before_str, value, *before);
	before_str[*before] = '\0';
	return (before_str);
}

char	*get_env_name(char *value, int *env_index, int *env_len)
{
	char	*env_name;

	*env_len = 0;
	while (ft_isalnum(value[*env_index + 1 + *env_len]) || value[*env_index + 1
		+ *env_len] == '_')
		(*env_len)++;
	env_name = malloc(*env_len + 1);
	if (!env_name)
		return (NULL);
	ft_strncpy(env_name, &value[*env_index + 1], *env_len);
	env_name[*env_len] = '\0';
	return (env_name);
}

char *expand_env_var(char *value, int *env_index)
{
    int before;
    int env_len;
    char *before_str;
    char *env_name;
    char *env_value;
    char *result;
    char *final_result;

    before_str = get_before_str(value, &before);
    if (!before_str)
        return (NULL);
    env_name = get_env_name(value, env_index, &env_len);
    if (!env_name)
    {
        free(before_str);
        return (NULL);
    }
    env_value = extract_env_value_from_name(env_name);
    free(env_name);

    if (env_value == NULL)
        env_value = ft_strdup("");  // Return an empty string if not found
    result = ft_strjoin(before_str, env_value);
    final_result = ft_strjoin(result, &value[*env_index + 1 + env_len]);
    *env_index += env_len - 1;  // Adjust the index to skip the processed variable
    free(before_str);
    free(result);
    return (final_result);
}

char *double_quote_mode(char *value, int *index)
{
    int start;
    int env_index;
    int len;
    char *temp;
    char *last_result;
    char *expanded_result;

    start = *index + 1;
    len = 0;
    while (value[start + len] && value[start + len] != '"')
        len++;
    temp = malloc(len + 1);
    if (!temp)
        return (NULL);
    ft_strncpy(temp, value + start, len);
    temp[len] = '\0'; 
    while ((env_index = has_env_var(temp)) != -1)
    {
        last_result = expand_env_var(temp, &env_index);
        free(temp);
        if (!last_result)
            last_result = ft_strdup("");
        temp = last_result;
    }
    if (env_index == -1)
    {
        *index = start + len + 1;
        return (temp);
    }
    expanded_result = temp;
    *index = start + ft_strlen(expanded_result) + 1;
    return (expanded_result);
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
char *normal_mode(char *value, int *index)
{
    int   start;
    int   len;
    char  *temp;
    char  *new_expanded;
    int   env_index;

    start = *index;
    len = 0;
    while (value[start + len] && value[start + len] != '\'' && value[start + len] != '\"')
        len++;

    temp = malloc(len + 1);
    if (!temp)
        return (NULL);
    ft_strncpy(temp, value + start, len);
    temp[len] = '\0';
    while ((env_index = has_env_var(temp)) != -1)
    {
        new_expanded = expand_env_var(temp, &env_index);
        if (!new_expanded) // If expansion fails, default to empty string
            new_expanded = ft_strdup("");
        free(temp);
        temp = new_expanded;
    }
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
		result = handle_quotes_mode(current->value);
		if (!result)
			return (NULL);
		if (result)
		{
			free(current->value);
			current->value = result;
		}
		current = current->next;
	}
	return (result);
}
