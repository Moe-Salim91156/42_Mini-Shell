/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/02/27 20:05:17 by msalim           ###   ########.fr       */
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
char	*expand_env_var(const char *str)
{
	char	*result;
	char	*user_value;
	char	*pos;

	user_value = "msalim";
	int len_before, total_len;
	// Check if $USER exists in the string
	pos = strstr(str, "$USER");
	if (!pos)
		return (strdup(str)); // No expansion needed
	// Calculate length before "$USER"
	len_before = pos - str;
	total_len = len_before + strlen(user_value) + strlen(pos + 5) + 1;
	// Allocate memory for the new string
	result = (char *)malloc(total_len);
	if (!result)
		return (NULL);
	// Build the expanded string
	strncpy(result, str, len_before);
	result[len_before] = '\0';
	strcat(result, user_value);
	strcat(result, pos + 5); // Skip "$USER"
	return (result);
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
	ft_strncpy(temp, value + start, len);
	// remove first and last quote
	// all quotes inside remain unotched
	// expand env_vars
	// reset flag
	temp[len] = '\0';
	*index = start + len;
	return (temp);
}
char	*double_quote_mode(char *value, int *index)
{
	int		start;
	int		len;
	char	*temp;
	char	*expanded;

	start = *index + 1;
	len = 0;
	while (value[start + len] && value[start + len] != '"')
		len++;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	strncpy(temp, value + start, len);
	temp[len] = '\0';
	// Expand $USER inside double quotes
	expanded = expand_env_var(temp);
	free(temp);
	*index = start + len; // Move index past closing double-quote
	return (expanded);
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

char	*handle_env_var_expansion(char *value, int *index)
{
	int		start;
	int		len;
	char	*var_name;
	char	*expanded_value;

	start = *index + 1;
	len = 0;
	while (value[start + len] && (isalnum(value[start + len]) || value[start
			+ len] == '_'))
		len++;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	strncpy(var_name, value + start, len);
	var_name[len] = '\0';
	expanded_value = getenv(var_name);
	free(var_name); // Free the variable name string
	if (expanded_value)
	{
		*index = start + len;            
			// Move the index to the end of the variable
		return (ft_strdup(expanded_value)); // Return the expanded value
	}
	else
	{
		*index = start + len; // Move the index past the variable
		return (ft_strdup(""));
			// Return an empty string if the variable isn't found
	}
}

char	*handle_quotes_mode(char *value)
{
	int		i;
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			temp = single_quote_mode(value, &i);
		else if (value[i] == '"')
			temp = double_quote_mode(value, &i);
		else
		{
			i++;
			continue ;
		}
		result = append_mode_result(result, temp);
	}
	return (result);
}
char	*ft_strjoin_char(char *str, char c)
{
	int len = ft_strlen(str);        // Get the current length of the string
	char *new_str = malloc(len + 2); // +1 for the new character and
	if (!new_str)
		return (NULL); // Return NULL if memory allocation fails
	ft_strncpy(new_str, str, len);
	new_str[len] = c;        // Add the new character
	new_str[len + 1] = '\0'; // Null-terminate the new string
	free(str);      // Free the original string
	return (new_str); // Return the new string
}
void	expander_main(t_token_list *list)
{
	t_token	*current;
	char	*result;
	int		i;
	char	*temp;

	current = list->head;
	while (current)
	{
		result = ft_strdup(""); // Start with an empty string
		if (ft_strchr(current->value, '\'') || ft_strchr(current->value, '"'))
		{
			result = handle_quotes_mode(current->value); // Handle quotes mode
		}
		else // Normal mode (no quotes)
		{
			i = 0;
			while (current->value[i] != '\0')
			{
				if (current->value[i] == '$') // If we encounter a '$',
				{
					temp = handle_env_var_expansion(current->value, &i);
					if (temp)
					{
						result = ft_strjoin(result, temp);
						free(temp);                       
					}
				}
				else
				{
					result = ft_strjoin_char(result, current->value[i]);
					i++;
				}
			}
		}
		if (result)
		{
			free(current->value);                    // Free the original value
			current->value = result;                
		}
		current = current->next; // Move to the next token
	}
}
