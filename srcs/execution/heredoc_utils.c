/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:14:53 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/05 22:38:45 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"



/*
** Cleans up heredoc resources for a command
** Closes any open heredoc file descriptors
*/
void	cleanup_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_fd > 0)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (cmd->heredoc_delimiter)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
	}
	cmd->has_heredoc = 0;
}

/*
** Cleans up all heredoc resources for all commands in the shell
*/
void	cleanup_all_heredocs(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd_list->head;
	while (current)
	{
		cleanup_heredoc(current);
		current = current->next;
	}
}
