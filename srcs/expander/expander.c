/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:18:01 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 16:38:56 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*double_quote_mode(t_token *current, int *index, t_shell *shell)
{
	t_double_quote_context	context;
	char					*expanded_result;

	context.start = *index + 1;
	context.len = 0;
	while (current->value[context.start + context.len]
		&& current->value[context.start + context.len] != '"')
		context.len++;
	context.temp = malloc(context.len + 1);
	if (!context.temp)
		return (NULL);
	ft_strncpy(context.temp, current->value + context.start, context.len);
	context.temp[context.len] = '\0';
	context.env_index = has_env_var(context.temp, current);
	while (context.env_index != -1)
	{
		gezha_function(&context, shell);
		context.env_index = has_env_var(context.temp, current);
	}
	expanded_result = context.temp;
	*index = context.start + context.len + 1;
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

char	*normal_mode(t_token *current, int *index, t_shell *shell)
{
	t_normal_mode_context	context;

	context.start = *index;
	context.len = 0;
	while (current->value[context.start + context.len]
		&& current->value[context.start + context.len] != '\''
		&& current->value[context.start + context.len] != '\"')
		context.len++;
	context.temp = malloc(context.len + 1);
	if (!context.temp)
		return (NULL);
	ft_strncpy(context.temp, current->value + context.start, context.len);
	context.temp[context.len] = '\0';
	context.env_index = has_env_var(context.temp, current);
	while (context.env_index != -1)
	{
		ozha_function(&context, shell);
		context.env_index = has_env_var(context.temp, current);
	}
	*index = context.start + context.len;
	return (context.temp);
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
		if (!temp)
			return (NULL);
		result = append_mode_result(result, temp);
		if (!result)
			return (NULL);
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
