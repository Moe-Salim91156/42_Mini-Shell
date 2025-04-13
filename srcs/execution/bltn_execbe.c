/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_execbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:23:07 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/12 17:17:46 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 passed cmdname, executes it as a bltn (i.e without forking)
 treated as execve, only it doesnt overwrite parent process image
*/
int	bltn_execbe(char *cmdname, char **argv, char **envp, t_shell *shell)
{
	if (ft_strcmp("env", cmdname))
		return (bltn_env(shell));
	else if (ft_strcmp("pwd", cmdname))
		return (bltn_pwd());
	else if (ft_strcmp("export", cmdname))
		return (bltn_export(argv, shell->envp_list));
	else if (ft_strcmp("unset", cmdname))
		return (bltn_unset(argv, shell->envp_list));
	else if (ft_strcmp("cd", cmdname))
		return (bltn_cd(argv, shell->envp_list));
	else if (ft_strcmp("echo", cmdname))
		return (bltn_echo(argv));
	else if (ft_strcmp("exit", cmdname))
		return (bltn_exit(argv, shell));
	else
		return (-1);
}
