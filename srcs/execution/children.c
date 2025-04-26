/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/23 16:09:24 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	no child lives past this.
	death by ft_exit or execve.
*/
static void child_perror(int exit_status)
{
	if (exit_status == 127)
		ft_putendl_fd("rbsh: command not found.", 2);
	else if (exit_status == 126)
		ft_putendl_fd("rbsh: permission denied.", 2);
	else if (exit_status == 1)
		ft_putendl_fd("rbsh: invalid redirection.", 2);
	else
		perror("execve");
}

int set_exit_status(char *cmd_path)
{
	if (cmd_path == NULL || !*cmd_path)
	{
		return (127);
	}
	if (access(cmd_path, F_OK) == -1)
	{
		return (127);
	}
	else if (access(cmd_path, X_OK | R_OK) == -1)
	{
		return (126);
	}
	return (0);
}
int	manage_child(t_shell *shell, t_cmd *current_payload, int pipe[],int payload_loc)
{
	char	**env;

	env = build_envp(shell);
	if (!env)
	{
		perror("envp");
		exit(1);
	}
	if (pipe)
		(void)pipe,(void)payload_loc;//handle_pipe(pipe,payload_loc,payload_count);
	locate_heredoc(current_payload,shell);
	current_payload->exit_status = parse_redirs(current_payload,current_payload->payload_array);
	if (current_payload->exit_status)
	{
		free(env);
		child_perror(current_payload->exit_status);//
		exit(current_payload->exit_status); //exit handler
	}
	current_payload->cmd_path = search_command_in_path(current_payload->argv[0],env, current_payload);
	current_payload->exit_status = set_exit_status(current_payload->cmd_path);
	if(!current_payload->exit_status)
		execve(current_payload->cmd_path, current_payload->argv, env);
	child_perror(current_payload->exit_status);
	free(env);
	exit(current_payload->exit_status);//exit handler
}
