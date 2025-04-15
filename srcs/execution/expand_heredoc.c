/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:38:09 by msalim            #+#    #+#             */
/*   Updated: 2025/04/15 17:41:14 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

