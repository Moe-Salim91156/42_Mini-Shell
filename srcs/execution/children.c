/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/12 17:03:42 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_perror(int exit_status, char **env)
{
	if (env)
		free_split(env);
	if (exit_status == 127)
		ft_putendl_fd("rbsh: command not found.", 2);
	else if (exit_status == 126)
		ft_putendl_fd("rbsh: command not executable.", 2);
	else if (exit_status == 1)
		ft_putendl_fd("rbsh: No such file or directory!", 2);
}

int	set_exit_status(char *cmd_path)
{
	struct stat	sb;

	if (cmd_path == NULL || !*cmd_path)
		return (127);
	if (stat(cmd_path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (126);
	}
	if (access(cmd_path, F_OK) == -1)
		return (127);
	else if (access(cmd_path, X_OK | R_OK) == -1)
		return (126);
	return (0);
}

/*
	child process command entry point,
		structured to ensure termination at end of function.
	- handles redirections
	- sets argv[0] (cmd_path)
	- sets cmd exit status //only on redir fail
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
	current_payload->exit_status = parse_redirs(current_payload,
			current_payload->payload_array);
	if (current_payload->exit_status)
		return (free_split(env));
	apply_redirs(current_payload);
	cleanup_all_heredocs(shell);
	current_payload->cmd_path = search_command_in_path(
			current_payload->argv[0], env, current_payload);
	current_payload->exit_status = set_exit_status(current_payload->cmd_path);
	if (!current_payload->exit_status)
		execve(current_payload->cmd_path, current_payload->argv, env);
	free_split(env);
	restore_io(current_payload);
	shell->last_status = current_payload->exit_status;
}

void	wait_for_children(t_shell *shell, int cmd_count, pid_t *pids)
{
	int		i;
	pid_t	wpid;
	int		last_status;

	i = 0;
	last_status = 0;
	while (i < cmd_count)
	{
		wpid = waitpid(-1, &last_status, 0);
		if (wpid == -1)
			break ;
		if (WIFEXITED(last_status))
			last_status = WEXITSTATUS(last_status);
		else if (WIFSIGNALED(last_status))
			last_status = WTERMSIG(last_status) + 128;
		if (last_status)
			child_perror(last_status, NULL);
		if (wpid == pids[cmd_count - 1])
			shell->last_status = last_status;
		i++;
	}
}
