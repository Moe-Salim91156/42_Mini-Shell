/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_execbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:23:07 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/10 19:02:06 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 passed cmdname, executes it as a bltn (i.e without forking)
 treated as execve, only it doesnt overwrite parent process image
*/

int	is_bltn(char **argv)
{
	if (!ft_strcmp("env", argv[0]))
		return (1);
	else if (!ft_strcmp("pwd", argv[0]))
		return (1);
	else if (!ft_strcmp("export", argv[0]))
		return (1);
	else if (!ft_strcmp("unset", argv[0]))
		return (1);
	else if (!ft_strcmp("cd", argv[0]))
		return (1);
	else if (!ft_strcmp("echo", argv[0]))
		return (1);
	else if (!ft_strcmp("exit", argv[0]))
		return (1);
	else
		return (0);
}

int	bltn_execbe(char **argv, t_shell *shell)
{
	if (!ft_strcmp("env", argv[0]))
		return (bltn_env(shell));
	else if (!ft_strcmp("pwd", argv[0]))
		return (bltn_pwd());
	else if (!ft_strcmp("export", argv[0]))
		return (bltn_export(argv, shell->envp_list));
	else if (!ft_strcmp("unset", argv[0]))
		return (bltn_unset(argv, &shell->envp_list));
	else if (!ft_strcmp("cd", argv[0]))
		return (bltn_cd(argv, shell->envp_list));
	else if (!ft_strcmp("echo", argv[0]))
		return (bltn_echo(argv));
	else if (!ft_strcmp("exit", argv[0]))
		return (bltn_exit(argv, shell));
	else
		return (-1);
}

int	manage_bltn(t_shell *shell, t_cmd *current_payload, int fork_flag)
{
	int	err;

	current_payload->is_fork = fork_flag;
	err = 0;
	err = parse_redirs(current_payload, current_payload->payload_array);
	if (!err)
	{
		apply_redirs(current_payload);
		current_payload->exit_status = bltn_execbe(current_payload->argv,
				shell);
	}
	else
		ft_putendl_fd("rbsh: Invalid Redirection!", 2);
	current_payload->exit_status = err;
	restore_io(current_payload);
	return (current_payload->exit_status);
}
