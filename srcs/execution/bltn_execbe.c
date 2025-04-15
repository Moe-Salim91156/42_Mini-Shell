/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_execbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:23:07 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/15 10:11:42 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

/*
 passed cmdname, executes it as a bltn (i.e without forking)
 treated as execve, only it doesnt overwrite parent process image
*/

int	is_bltn(char **argv)
{
	if (ft_strcmp("env", argv[0]))
		return (1);
	else if (ft_strcmp("pwd", argv[0]))
		return (1);
	else if (ft_strcmp("export", argv[0]))
		return (1);
	else if (ft_strcmp("unset", argv[0]))
		return (1);
	else if (ft_strcmp("cd", argv[0]))
		return (1);
	else if (ft_strcmp("echo", argv[0]))
		return (1);
	else if (ft_strcmp("exit", argv[0]))
		return (1);
	else
		return (0);
}

int	bltn_execbe(char **argv, t_shell *shell)
{

	dup2(STDIN_FILENO, shell->cmd_list->head->in_fd);
	dup2(STDOUT_FILENO, shell->cmd_list->head->out_fd);
	if (ft_strcmp("env", argv[0]))
		return (bltn_env(shell));
	else if (ft_strcmp("pwd", argv[0]))
		return (bltn_pwd());
	else if (ft_strcmp("export", argv[0]))
		return (bltn_export(argv, shell->envp_list));
	else if (ft_strcmp("unset", argv[0]))
		return (bltn_unset(argv, shell->envp_list));
	else if (ft_strcmp("cd", argv[0]))
		return (bltn_cd(argv, shell->envp_list));
	else if (ft_strcmp("echo", argv[0]))
		return (bltn_echo(argv));
	else if (ft_strcmp("exit", argv[0]))
		return (bltn_exit(argv, shell));
	else
		return (-1);
}
int manage_bltn(t_shell *shell)
{
	int	ret;

	ret = 0;
	if(locate_heredoc(shell->cmd_list))
		if (parse_redirs(shell,shell->cmd_list->head->payload_array))
			ret = bltn_execbe(shell->cmd_list->head->argv, shell);
	restore_io(shell->cmd_list->head);
	// free heredoc
	return (ret);
}
