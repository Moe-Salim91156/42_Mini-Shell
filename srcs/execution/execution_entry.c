/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 16:57:10 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//!!!!!!!!!!!!!!!!! if first command $U ls , should work, so locate cmd,
	should handle that,
//                               
	/// in the token list it should be correctly assigned
// handle heredocs
// handle redirections
/*
int	is_builtin(char *cmd)
{

  // will check if the command is a builtin inside shell or not
  // if yes will return (1);
  // no , maybe external or doesnt exist (
}*/
/*
int	execution_entry(t_shell *shell)
{
  t_cmd *payload;

  payload = shell->cmd_list->head;
  char *cmd_name = shell->cmd_list->head->argv[0];
  //parse heredoc
  // parse_redirection
  //      in_fd ; out_fd;
  //      in_fd; error out, outfile gonna be created;
  // locate_cmd : return (cmd_name | assigns payload->cmd_name);
  // execute_cases:
  //
	if (shell->cmd_list->count == 1)
	{
		if (bltn_execbe(cmd_name,payload->argv, shell) != -1)
		{
		printf("execution success\n");
		}
	else
	{
		//case 2 -> non_builtin one command no pipes
		//execute_in_child();
	}
  }
	else
	{
		//case 3 -> one pipe and more
		//build_pipeline();//fork for each child
						//build pipes --> pipe()
	}
	return (0);
	}
  */
