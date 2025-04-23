/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_general_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:32:32 by msalim            #+#    #+#             */
/*   Updated: 2025/04/22 14:13:16 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	gezha_function(t_double_quote_context *context, t_shell *shell)
{
	context->last_result = expand_env_var(context->temp, &context->env_index,
			shell);
	if (!context->last_result)
		context->last_result = ft_strdup("");
	free(context->temp);
	context->temp = context->last_result;
}

void	ozha_function(t_normal_mode_context *context, t_shell *shell)
{
	context->new_expanded = expand_env_var(context->temp, &context->env_index,
			shell);
	if (!context->new_expanded)
		context->new_expanded = ft_strdup("");
	free(context->temp);
	context->temp = context->new_expanded;
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
			if (value[i + 1] == '?' || ft_isalnum(value[i + 1]) || value[i
					+ 1] == '_')
				return (i);
			return (-1);
		}
		i++;
	}
	return (-1);
}
