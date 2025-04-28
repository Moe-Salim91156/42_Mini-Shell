/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/28 20:32:08 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	no child lives past this.
	death by ft_exit or execve.
*/
static void child_perror(int exit_status, char **env)
{
	if (env)
		free_split(env);
	if (exit_status == 127)
		ft_putendl_fd("rbsh: command not found.", 2);
	else if (exit_status == 126)
		ft_putendl_fd("rbsh: permission denied.", 2);
	else if (exit_status == 1)//will become redundant after refactoring
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

/*
	child process command entry point, structured to ensure termination at end of function.
	- configs pipes
	- handles redirections
	- sets argv[0] (cmd_path)
	- sets exit status
	- executes command
	- cleanup in errnous behaviour
*/
void	manage_child(t_shell *shell, t_cmd *current_payload)
{
	char	**env;

	env = build_envp(shell);
	if (!env)
	{
		perror("envp");
		exit(1);
	}
	// locate_heredoc(current_payload,shell);//needs to be moved to pipeline
	current_payload->exit_status = parse_redirs(current_payload,current_payload->payload_array);//
	if (current_payload->exit_status)
	{
		child_perror(current_payload->exit_status,env);
		exit(current_payload->exit_status); //exit handler
	}
	apply_redirs(current_payload);
	current_payload->cmd_path = search_command_in_path(current_payload->argv[0],env, current_payload);
	current_payload->exit_status = set_exit_status(current_payload->cmd_path);
	if(!current_payload->exit_status)
		execve( current_payload->cmd_path, current_payload->argv, env);
	child_perror(current_payload->exit_status,env);
	exit(current_payload->exit_status);//exit handler
}
void	wait_for_children(t_shell *shell, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_status = WTERMSIG(status) + 128;
		}
		i++;
	}
}