/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:57:43 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/13 14:26:45 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, int status)
{
	if (status)
		shell->last_status = status;
	if (shell->cmd_list)
	{
		cleanup_all_heredocs(shell);
		free_command_list(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->token_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
	}
	if (shell->envp_list)
	{
		free_env(shell->envp_list);
		shell->envp_list = NULL;
	}
	exit(shell->last_status);
}
