/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:36:24 by msalim            #+#    #+#             */
/*   Updated: 2025/05/10 20:24:56 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// look for redirections

/*
	closeses file discriptors per @cmd
	resets @cmd's process to STDIN/STDOUT
*/
void	restore_io(t_cmd *cmd)
{
	if (cmd->in_fd != STDIN_FILENO)
	{
		close(cmd->in_fd);
		cmd->in_fd = STDIN_FILENO;
	}
	if (cmd->out_fd != STDOUT_FILENO)
	{
		close(cmd->out_fd);
		cmd->out_fd = STDOUT_FILENO;
	}
	if (cmd->backup_in_fd != -1)
	{
		dup2(cmd->backup_in_fd, STDIN_FILENO);
		close(cmd->backup_in_fd);
		cmd->backup_in_fd = -1;
	}
	if (cmd->backup_out_fd != -1)
	{
		dup2(cmd->backup_out_fd, STDOUT_FILENO);
		close(cmd->backup_out_fd);
		cmd->backup_out_fd = -1;
	}
}

void	apply_redirs(t_cmd *current_payload)
{
	if (current_payload->in_fd != STDIN_FILENO)
	{
		if (!current_payload->is_fork)
		{
			if (current_payload->backup_in_fd < 0)
				current_payload->backup_in_fd = dup(STDIN_FILENO);
			if (current_payload->backup_out_fd < 0)
				current_payload->backup_out_fd = dup(STDOUT_FILENO);
		}
		dup2(current_payload->in_fd, STDIN_FILENO);
		close(current_payload->in_fd);
	}
	if (current_payload->out_fd != STDOUT_FILENO)
	{
		if (!current_payload->is_fork)
		{
			if (current_payload->backup_in_fd < 0)
				current_payload->backup_in_fd = dup(STDIN_FILENO);
			if (current_payload->backup_out_fd < 0)
				current_payload->backup_out_fd = dup(STDOUT_FILENO);
		}
		dup2(current_payload->out_fd, STDOUT_FILENO);
		close(current_payload->out_fd);
	}
}
