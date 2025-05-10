/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:38:09 by msalim            #+#    #+#             */
/*   Updated: 2025/05/07 14:00:50 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value_from_envp(char *key, char **envp)
{
	int		i;
	char	*prefix;
	size_t	len;

	len = ft_strlen(key);
	prefix = ft_strjoin(key, "=");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], prefix, len + 1))
		{
			free(prefix);
			return (ft_strdup(envp[i] + len + 1));
		}
		i++;
	}
	free(prefix);
	return (NULL);
}

char	*expand_env_segment(char *line, int *i, char **envp)
{
	t_heredoc_context	h_ctx;

	h_ctx.before = ft_substr(line, 0, *i);
	(*i)++;
	h_ctx.start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	h_ctx.env_name = ft_substr(line, h_ctx.start, *i - h_ctx.start);
	h_ctx.env_value = get_env_value_from_envp(h_ctx.env_name, envp);
	if (!h_ctx.env_value)
		h_ctx.env_value = ft_strdup("");
	h_ctx.after = ft_strdup(&line[*i]);
	h_ctx.tmp = ft_strjoin(h_ctx.before, h_ctx.env_value);
	h_ctx.res = ft_strjoin(h_ctx.tmp, h_ctx.after);
	free(h_ctx.before);
	free(h_ctx.env_name);
	free(h_ctx.env_value);
	free(h_ctx.after);
	free(h_ctx.tmp);
	return (h_ctx.res);
}

char	*expand_heredoc_line(char *line, char **envp)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup(line);
	while (result[i])
	{
		if (result[i] == '$' && ft_isalpha(result[i + 1]))
		{
			tmp = expand_env_segment(result, &i, envp);
			free(result);
			result = tmp;
			i = -1;
		}
		i++;
	}
	return (result);
}
