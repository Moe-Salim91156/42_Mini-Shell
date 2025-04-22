/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/22 21:18:39 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	no child lives past this.
	death by ft_exit or execve.
*/
int	manage_child(t_shell *shell, t_cmd *current_payload, int pipe[],int payload_loc)
{
	char	**env;

	env = build_envp(shell);
	if (pipe)
		(void)pipe,(void)payload_loc;
		//handle_pipe(pipe,payload_loc,payload_count); //this should handle pipe redirections
	if (locate_heredoc(current_payload,shell) != -1)
		if (parse_redirs(current_payload, current_payload->payload_array) !=-1)
		{
			current_payload->cmd_path = search_command_in_path(current_payload->argv[0]
				,env, current_payload);
			if(env && current_payload->cmd_path)
				if (execve(current_payload->cmd_path, current_payload->argv, env) == -1)
				{
					perror("execve");
					exit(current_payload->exit_status); //exit handler
				}
		}
	//we only get here if shit goes	wrong
	ft_putendl_fd("rbsh: command not found.", 2);
	free(env);
	exit(current_payload->exit_status);//exit handler
}
