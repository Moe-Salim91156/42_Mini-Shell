/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 15:50:10 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handle heredocs
// handle redirections
/*
int is_builtin(char *cmd)
{

  // will check if the command is a builtin inside shell or not
  // if yes will return 1;
  // no , maybe external or doesnt exist (
}*/
/*
char	*locate_cmd(char **argv, t_envp *envp_list)
{
  char  *cmd_name;

  cmd_name = argv[0];
  // if cm_n
  cmd_name = search_command_in_path(cmd_name, envp_list);

  if (!cmd_name)
    return (NULL);
  // search for cmd_name in PATH
  // check validation , if its wrong typed, or doesnt exit (validatio);
  // if its valid all good , return its name
  // payload->cmd_name or cmd_name var;
  return (cmd_name);
}
*/

int	execution_entry(t_shell *shell)
{
  t_cmd *payload;

  payload = shell->cmd_list->head;
  //parse heredoc
  // parse_redirection
  //      in_fd ; out_fd;
  //      in_fd; error out, outfile gonna be created;
  // locate_cmd : return cmd_name | assigns payload->cmd_name;
  // execute_cases:
  // 
  /*
	if (shell->cmd_list->count == 1)
	{
		if (is_builtin(locate_cmd(shell->cmd_list->head->argv)))
		{
			ft_execbe();
		}
    else
    {
      //case 2 -> non_builtin one command no pipes
      execute_in_child();
    }
  }
    else
    {
      //case 3 -> one pipe and more
      build_pipeline();//fork for each child
                       //build pipes --> pipe()
    }
	}*/
char *cmd_name  = shell->cmd_list->head->argv[0];
char **envp = build_envp(shell);
cmd_name = search_command_in_path(cmd_name,envp, payload);
if (!ft_strcmp(cmd_name, "set_path"))
payload->cmd_path = cmd_name;
printf("cmd ) name %s\n",cmd_name);
printf("cmd_path to send to execve %s\n",payload->cmd_path);
	return (0);
}
