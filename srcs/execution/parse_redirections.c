/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/17 18:30:19 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	parse_redirs(t_cmd *cmd,char **payload_array)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while(payload_array[i])
	{
		if (ft_strcmp("<", payload_array[i]))
			ret = redir_in(cmd,payload_array[++i]);
		if (ft_strcmp(">", payload_array[i]))
			ret = redir_out(cmd,payload_array[++i]);
		if (ft_strcmp(">>", payload_array[i]))
			ret = redir_append(cmd,payload_array[++i]);
		if (ft_strncmp("<<", payload_array[i], 2))
		{
			ret = redir_heredoc(cmd, HEREDOC_PATH);
			i+=2;
		}
		if (ret == -1)
			break;
		i++;
	}
	return (ret);
}

int	redir_in(t_cmd *current_payload, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		current_payload->exit_status = 1;
		return (-1);
	}
	current_payload->in_fd = fd;
}

int redir_out(t_cmd *current_payload, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		current_payload->exit_status = 1;
		return (-1);
	}
	current_payload->out_fd = fd;
	return (0);
}

int redir_append(t_cmd *current_payload, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		current_payload->exit_status = 1;
		return (-1);
	}
	current_payload->out_fd = fd;
	return (0);
}

int redir_heredoc(t_cmd *current_payload, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		current_payload->exit_status = 1;
		return (-1);
	}
	current_payload->in_fd = fd;
	return (0);
}
