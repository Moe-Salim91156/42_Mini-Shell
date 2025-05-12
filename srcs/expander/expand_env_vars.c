/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:27:51 by msalim            #+#    #+#             */
/*   Updated: 2025/05/12 13:18:39 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_env_value_from_name(char *value, t_shell *shell)
{
	char	*result;
	char	*exit_status_str;
	t_envp	*node;

	if (ft_strcmp(value, "?") == 0)
	{
		exit_status_str = ft_itoa(shell->last_status);
		if (exit_status_str == NULL)
			return (ft_strdup(""));
		return (exit_status_str);
	}
	node = ft_getenv(shell->envp_list, value);
	if (!node)
		return (ft_strdup(""));
	result = ft_strdup(node->value);
	if (!result)
		return (NULL);
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
	if (value[*env_index + 1] == '?')
	{
		*env_len = 1;
		return (ft_strdup("?"));
	}
	if (!ft_isalnum(value[*env_index + 1]) && value[*env_index + 1] != '_')
		return (ft_strdup(""));
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

char	*expand_env_var_concat(t_expand_env_context *ctx, char *value,
		int *next_index)
{
	char	*temp;

	//validate ctx 
	if (value[*next_index] == '$')
	{
		temp = ft_strjoin(ctx->env_value, "$");//null check
		free(ctx->env_value);
		ctx->env_value = temp;
		(*next_index)++;
	}
	ctx->result = ft_strjoin(ctx->before_str, ctx->env_value);
	return (ft_strjoin(ctx->result, &value[*next_index]));
}

char	*expand_env_var(char *value, int *env_index, t_shell *shell)
{
	t_expand_env_context	ctx;

	ctx.before_str = get_before_str(value, &ctx.before);
	if (!ctx.before_str)
		return (NULL);
	ctx.env_name = get_env_name(value, env_index, &ctx.env_len);
	if (!ctx.env_name)
	{
		free(ctx.before_str);
		return (NULL);
	}
	ctx.env_value = extract_env_value_from_name(ctx.env_name, shell);
	if (!ctx.env_value)
		ctx.env_value = ft_strdup("");
	free(ctx.env_name);
	ctx.next_index = *env_index + 1 + ctx.env_len;
	ctx.final_result = expand_env_var_concat(&ctx, value, &ctx.next_index);
	free(ctx.before_str);
	free(ctx.env_value);
	free(ctx.result);
	*env_index = ctx.next_index - 1;
	return (ctx.final_result);
}
