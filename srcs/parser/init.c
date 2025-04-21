/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:20 by msalim            #+#    #+#             */
/*   Updated: 2025/04/20 19:14:49 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_list	*init_list(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->size = 0;
	return (token_list);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = 0;
	token->heredoc_quoted = 0;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

t_cmd_list	*init_cmd_list(void)
{
	t_cmd_list	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	cmd_list->count = 0;
	cmd_list->payload_count = 0;
	cmd_list->total_heredocs = 0;
	cmd_list->head = NULL;
	return (cmd_list);
}

t_cmd	*init_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->type = 0;
	cmd->payload_array = NULL;
	cmd->here_doc_counts = 0;
	cmd->heredoc_buffer = NULL;
	cmd->has_heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->heredoc_quoted = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->in_fd = STDIN_FILENO;
	cmd->backup_in_fd = dup(STDIN_FILENO);
	cmd->out_fd = STDOUT_FILENO;
	cmd->backup_out_fd = dup(STDOUT_FILENO);
	cmd->exit_status = 0;
	cmd->next = NULL;
	return (cmd);
}
