/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/01 17:52:30 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	parse_redirs(t_cmd *cmd, char **payload_array)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (payload_array[i] != NULL)
	{
		if (!ft_strcmp("<", payload_array[i]))
			ret = redir_in(cmd, payload_array[++i]);
		if (!ft_strcmp(">", payload_array[i]))
			ret = redir_out(cmd, payload_array[++i]);
		if (!ft_strcmp(">>", payload_array[i]))
			ret = redir_append(cmd, payload_array[++i]);
		if (!ft_strcmp("<<", payload_array[i]))
		{
			i++;
		}
		if (ret == 1)
			break ;
		i++;
	}
  if (cmd->has_heredoc && cmd->heredoc_fd > 0)
	{
		if (cmd->in_fd != STDIN_FILENO)
			close(cmd->in_fd);
		cmd->in_fd = cmd->heredoc_fd;
	}
	return (ret);
}

int	redir_in(t_cmd *current_payload, char *file)
{
	int	fd;

	if (current_payload->in_fd != STDIN_FILENO)
		close(current_payload->in_fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		current_payload->exit_status = 1;
		return (1);
	}
	current_payload->in_fd = fd;
	return (0);
}

int	redir_out(t_cmd *current_payload, char *file)
{
	int	fd;

	if (current_payload->out_fd != STDOUT_FILENO)
		close(current_payload->out_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		current_payload->exit_status = 1;
		return (1);
	}
	current_payload->out_fd = fd;
	return (0);
}

int	redir_append(t_cmd *current_payload, char *file)
{
	int	fd;

	if (current_payload->out_fd != STDOUT_FILENO)
		close(current_payload->out_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		current_payload->exit_status = 1;
		return (1);
	}
	current_payload->out_fd = fd;
	return (0);
}

int	redir_heredoc(t_cmd *current_payload)
{

	if (current_payload->in_fd != STDIN_FILENO)
		close(current_payload->in_fd);
	if (current_payload->has_heredoc && current_payload->heredoc_fd > 0)
	{
		current_payload->in_fd = current_payload->heredoc_fd;
		return (0);
	}
	if (current_payload->has_heredoc)
	{
		current_payload->exit_status = 1;
		return (1);
	}
	return (0);
}
