/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:36:24 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 17:55:54 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

// look for redirections

void	restore_io(t_cmd *payload)
{
	if (payload->in_fd)
		dup2(payload->in_fd,STDIN_FILENO);
	if (payload->out_fd)
		dup2(payload->out_fd,STDOUT_FILENO);
}