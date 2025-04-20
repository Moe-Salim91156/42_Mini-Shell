/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/04/20 20:55:14 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_env_var(char *value, t_token *current)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && current->type != HEREDOC_DELIMITER)
		{
			if (value[i + 1] == '\0')
				return (-1);
			// Check for $? as a special case
			if (value[i + 1] == '?' || ft_isalnum(value[i + 1]) || value[i + 1] == '_')
				return (i);
			return (-1);
		}
		i++;
	}
	return (-1);
}

char	*extract_env_value_from_name(char *value, t_shell *shell)
{
	char	*result;
	char	*exit_status_str;

	// Handle $? - special case for last exit status
	if (ft_strcmp(value, "?") == 0)
	{
		exit_status_str = ft_itoa(shell->last_status);
		if (exit_status_str == NULL)
			return (ft_strdup(""));
		return (exit_status_str);
	}
	
	result = getenv(value);
	if (result == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(result));
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
	
	// Handle $? as a special case
	if (value[*env_index + 1] == '?')
	{
		*env_len = 1;
		return (ft_strdup("?"));
	}
	
	if (!ft_isalnum(value[*env_index + 1]) && value[*env_index + 1] != '_')
		return (ft_strdup(""));
	// return empty string so it won't be re-expanded
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

char	*expand_env_var(char *value, int *env_index, t_shell *shell)
{
	int		before;
	int		env_len;
	char	*before_str;
	char	*env_name;
	char	*env_value;
	char	*result;
	char	*final_result;
	char	*temp;
	int		next_index;
	int		has_trailing_dollar;

	before_str = get_before_str(value, &before);
	if (!before_str)
		return (NULL);
	env_name = get_env_name(value, env_index, &env_len);
	if (!env_name)
	{
		free(before_str);
		return (NULL);
	}
	env_value = extract_env_value_from_name(env_name, shell);
	if (!env_value)
		env_value = ft_strdup("");
	free(env_name);
	next_index = *env_index + 1 + env_len;
	has_trailing_dollar = (value[next_index] == '$');
	if (has_trailing_dollar)
	{
		temp = ft_strjoin(env_value, "$");
		free(env_value);
		env_value = temp;
		next_index++;
	}
	result = ft_strjoin(before_str, env_value);
	final_result = ft_strjoin(result, &value[next_index]);
	free(before_str);
	free(env_value);
	free(result);
	*env_index = next_index - 1;
	return (final_result);
}

char	*double_quote_mode(t_token *current, int *index, t_shell *shell)
{
	int		start;
	int		env_index;
	int		len;
	char	*temp;
	char	*last_result;
	char	*expanded_result;

	start = *index + 1;
	len = 0;
	while (current->value[start + len] && current->value[start + len] != '"')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, current->value + start, len);
	temp[len] = '\0';
	while ((env_index = has_env_var(temp, current)) != -1)
	{
		last_result = expand_env_var(temp, &env_index, shell);
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

char	*single_quote_mode(t_token *current, int *index)
{
	int		start;
	int		len;
	char	*temp;

	start = *index + 1;
	len = 0;
	while (current->value[start + len] && current->value[start + len] != '\'')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, current->value + start, len);
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

char	*normal_mode(t_token *current, int *index, t_shell *shell)
{
	int		start;
	int		len;
	char	*temp;
	char	*new_expanded;
	int		env_index;

	start = *index;
	len = 0;
	while (current->value[start + len] && current->value[start + len] != '\''
		&& current->value[start + len] != '\"')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, current->value + start, len);
	temp[len] = '\0';
	while ((env_index = has_env_var(temp, current)) != -1)
	{
		new_expanded = expand_env_var(temp, &env_index, shell);
		if (!new_expanded) // If expansion fails, default to empty string
			new_expanded = ft_strdup("");
		free(temp);
		temp = new_expanded;
	}
	*index = start + len;
	return (temp);
}

char	*handle_quotes_mode(t_token *current, t_shell *shell)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (current->value[i])
	{
		if (current->value[i] == '\'')
			temp = single_quote_mode(current, &i);
		else if (current->value[i] == '\"')
			temp = double_quote_mode(current, &i, shell);
		else
			temp = normal_mode(current, &i, shell);
		result = append_mode_result(result, temp);
	}
	return (result);
}

/* this will get called before expander for heredoc content expansion or not*/
/* just to set the flag for heredoc */
char	*expander_main(t_shell *shell)
{
	t_token	*current;
	char	*result;

	current = shell->token_list->head;
	while (current)
	{
		if (current->type == HEREDOC_DELIMITER)
		{
			if (ft_strchr(current->value, '\''))
				current->heredoc_quoted = 1;
			else if (ft_strchr(current->value, '\"'))
				current->heredoc_quoted = 1;
		}
		result = handle_quotes_mode(current, shell);
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
