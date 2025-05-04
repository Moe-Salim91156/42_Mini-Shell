/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/03 19:45:14 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_redir(t_cmd *cmd, char **payload, int *i, int *last)
{
	int	ret;

  ret = 0;
	if (!ft_strcmp(payload[*i], "<") && payload[*i + 1])
	{
		ret = redir_in(cmd, payload[++(*i)]);
		if (ret >= 0)
			*last = 1;
	}
	else if (!ft_strcmp(payload[*i], ">") && payload[*i + 1])
		ret = redir_out(cmd, payload[++(*i)]);
	else if (!ft_strcmp(payload[*i], ">>") && payload[*i + 1])
		ret = redir_append(cmd, payload[++(*i)]);
	else if (!ft_strcmp(payload[*i], "<<") && payload[*i + 1])
	{
		(*i)++;
		*last = 2;
	}
	return (ret);
}

int	parse_redirs(t_cmd *cmd, char **payload)
{
	int	i;
	int	ret;
	int	last;

	i = 0;
	ret = 0;
	last = 0;
	while (payload[i])
	{
		ret = process_redir(cmd, payload, &i, &last);
		if (ret == -1)
			return (-1);
		i++;
	}
	if (last == 2 && cmd->heredoc_fd != -1)
		cmd->in_fd = cmd->heredoc_fd;
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
