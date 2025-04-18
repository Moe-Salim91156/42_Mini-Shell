/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:59:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/17 19:09:34 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_child(t_shell *shell, t_cmd *current_payload, int pipe[])
{
	int	pid;
	int	status;
	char	**env;

	if (pipe)
	{
		printf("this is just to shut up a warning\n");
		/* handle_pipe(pipe); */
	}
		/* if (locate_heredoc(current_payload)) TBD*/
			if (parse_redirs(current_payload, current_payload->payload_array))
			{
				dup2(current_payload->in_fd, STDIN_FILENO);
				dup2(current_payload->out_fd, STDOUT_FILENO);
				env = build_envp(shell);
				if(env)
					if (execve(current_payload->cmd_path, current_payload->argv, env) == -1)
					{
						perror("execve");
						exit(1); //exit handler
					}
			}
		//we only get here if shit goes wrong
		free(env);
		exit(1);//exit handler
}
