/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:05:47 by msalim            #+#    #+#             */
/*   Updated: 2025/05/12 13:17:29 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_command_in_directories(char *cmd, char **dir)
{
	int		j;
	char	*full_cmd;
	char	*new_cm;

	j = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	while (dir[j])
	{
		if (!dir[j])
			return (NULL);
		full_cmd = ft_strjoin(dir[j], "/"); // null check
		if (!full_cmd)
			return (NULL);
		new_cm = ft_strjoin(full_cmd, cmd); // null check
		free(full_cmd);
		if (!new_cm)
			return (NULL);
		if (access(new_cm, F_OK) == 0)
			return (new_cm);
		free(new_cm);
		j++;
	}
	return (NULL);
}

static char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
/*
	RETURNS CMD ON MATCH
	NULL ELSE
*/
char	*search_command_in_path(char *cmd, char **envp, t_cmd *payload)
{
	char	*path;
	char	**dir;
	char	*result;

	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
	{
		payload->cmd_path = cmd;
		return (cmd);
	}
	if (ft_strchr(cmd, '/'))
	{
		payload->cmd_path = cmd;
		return (cmd);
	}
	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);
	result = find_command_in_directories(cmd, dir);
	if (!result)
	{
		free_split(dir);
		return (NULL);
	}
	free_split(dir);
	return (result);
}
