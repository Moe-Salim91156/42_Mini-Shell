/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:36:24 by msalim            #+#    #+#             */
/*   Updated: 2025/04/17 11:49:21 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

// look for redirections

void	restore_io(t_cmd *current_payload)
{
	if (current_payload->in_fd != STDIN_FILENO)
		dup2(current_payload->in_fd,STDIN_FILENO);
	if (current_payload->out_fd != STDOUT_FILENO)
		dup2(current_payload->out_fd,STDOUT_FILENO);
}