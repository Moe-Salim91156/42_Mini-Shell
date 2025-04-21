/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/21 16:05:13 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_child(t_shell *shell, t_cmd *current_payload, int pipe[])
{
	char	**env;
	env = build_envp(shell);
	if (pipe)
	{
		printf("this is just to shut up a warning\n");
		/* handle_pipe(pipe); */
	}
	if (locate_heredoc(current_payload,shell) != -1)
		if (parse_redirs(current_payload, current_payload->payload_array) !=-1)
		{
			current_payload->cmd_path = search_command_in_path(current_payload->argv[0]
				, env, current_payload);
			if(env && current_payload->cmd_path)
				if (execve(current_payload->cmd_path, current_payload->argv, env) == -1)
				{
					perror("execve:");
					exit(1); //exit handler
				}
		}
	ft_putendl_fd("rbsh: command not found.", 2);
	//we only get here if shit goes	wrong
	free(env);
	exit(1);//exit handler
}
