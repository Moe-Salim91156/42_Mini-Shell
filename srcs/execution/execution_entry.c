/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:55 by msalim            #+#    #+#             */
/*   Updated: 2025/04/09 17:12:20 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"

// handle heredocs
// handle redirections
// is_cmd
char  *locate_cmd()
{

}
int execution_entry(t_shell *shell)
{
  if (shell->cmd_list->count == 1)
  {
    if (is_builtin(locate_cmd()))
    {
      ft_execbe();
    }
  }
    return 0;
}

build_cmd_structure(t_token_list *list)
