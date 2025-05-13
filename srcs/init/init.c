/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:23:21 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/13 13:45:16 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	shell_init(t_shell *shell, char **envp)
{
	shell->token_list = init_list();
	shell->cmd_list = init_cmd_list();
	shell->envp_list = init_envp(envp);
	shell->last_status = 0;
	if (!shell->token_list || !shell->cmd_list || !shell->envp_list)
		ft_exit(shell, -1);
	return (0);
}
