/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/03/01 15:24:33 by msalim           ###   ########.fr       */
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
char  *extract_env_value_from_name(char *value)
{
  char  *result;


  result = getenv(value);
  printf(" result in getenv %s\n", result);
  if (result == NULL)
    return (ft_strdup(""));
  else
    return (result);
}

char  *expand_env_var(char *value, int *env_index)
{
  int before;
  char  *before_str;
  char  *after_str;
  char *last_after;
  char *last_result;

  before = 0;
  while (value[before] && value[before] != '$')
    before++;
  before_str = malloc(before + 1);
  ft_strncpy(before_str, value, before);
  after_str = &value[*env_index + 1];
  last_after = extract_env_value_from_name(after_str);
  last_result = ft_strjoin(before_str,last_after);
  return (last_result);
}

char	*double_quote_mode(char *value, int *index)
{
	int		start;
  int env_index;
	int		len;
	char	*temp;
  char *last_result;

	start = *index + 1;
	len = 0;
	while (value[start + len] && value[start + len] != '\"')
		len++;
	temp = malloc(len + 1);
  ft_strncpy(temp, value + start, len);
  env_index = has_env_var(temp);
  printf("env_INdex %d\n",env_index);
  if (env_index != -1)
  {
    last_result = expand_env_var(temp, &env_index);
    *index = ft_strlen(last_result) + 1;
    return (last_result);
  }
  else
  {
	ft_strncpy(temp, value + start, len);
  temp[len] = '\0';
  *index = start + len + 1;
  return (temp);
  }
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
