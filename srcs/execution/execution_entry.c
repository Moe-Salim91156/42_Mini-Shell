/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 15:05:57 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handle heredocs
// handle redirections
int	bltn_execbe(char *cmdname, char **argv, char **envp, t_shell *shell)
{
	if (ft_strcmp("env", cmdname))
		return (bltn_env(shell));
	else if (ft_strcmp("pwd", cmdname))
		return (bltn_pwd());
	else if (ft_strcmp("export", cmdname))
		return (bltn_export(argv, shell->envp_list));
	else if (ft_strcmp("unset", cmdname))
		return (bltn_unset(argv, shell->envp_list));
	else if (ft_strcmp("cd", cmdname))
		return (bltn_cd(argv, shell->envp_list));
	else if (ft_strcmp("echo", cmdname))
		return (bltn_echo(argv));
	else if (ft_strcmp("exit", cmdname))
		return (bltn_exit(argv, shell));
	else
		return (-1);
}

int is_builtin(char *cmd)
{

  // will check if the command is a builtin inside shell or not
  // if yes will return 1;
  // no , maybe external or doesnt exist (
}
char	*locate_cmd(char **argv, t_envp *envp_list)
{
  char  *cmd_name;

  cmd_name = argv[0];
  cmd_name = search_command_in_path(cmd_name, envp_list);
  if (!cmd_name)
    return (NULL);
  
  // search for cmd_name in PATH
  // check validation , if its wrong typed, or doesnt exit (validatio);
  // if its valid all good , return its name
  // payload->cmd_name or cmd_name var;
  return (cmd_name);
}

int	execution_entry(t_shell *shell)
{
  //parse heredoc
  // parse_redirection
  //      in_fd ; out_fd;
  //      in_fd; error out, outfile gonna be created;
  // locate_cmd : return cmd_name | assigns payload->cmd_name;
  // execute_cases:
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
      if(pid==child)
        execute_in_child();
    }
	}
	return (0);
}
