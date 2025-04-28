/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:38:09 by msalim            #+#    #+#             */
/*   Updated: 2025/04/28 21:45:58 by yokitane         ###   ########.fr       */
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
	int		start;
	char	*before;
	char	*env_name;
	char	*env_value;
	char	*after;
	char	*tmp;
	char	*res;

	before = ft_substr(line, 0, *i);
	(*i)++;
	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	env_name = ft_substr(line, start, *i - start);
	env_value = get_env_value_from_envp(env_name, envp);
	if (!env_value)
		env_value = ft_strdup("");
	after = ft_strdup(&line[*i]);
	tmp = ft_strjoin(before, env_value);
	res = ft_strjoin(tmp, after);
	free(before);
	free(env_name);
	free(env_value);
	free(after);
	free(tmp);
	return (res);
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
