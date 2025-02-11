/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:21:51 by msalim            #+#    #+#             */
/*   Updated: 2025/02/11 19:57:07 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

int count_cmd_tokens(t_token_list *list)
{
  t_token *current;
  int arg_cmd;

  arg_cmd = 0;
  current = list->head;
  while (current)
  {
    if (current->type == WORD || current->type == ARGS)
      arg_cmd++;
    current = current->next;
  }
  return (arg_cmd);
}

t_cmd *build_cmd(t_token_list *list,t_cmd *cmd)
{
  t_token *current;
  int i;

  i = 0;
  current = list->head;
  cmd->count = count_cmd_tokens(list);
  cmd->args = malloc(sizeof(char *) * cmd->count + 1);
  while (i < cmd->count)
  {
    cmd->args[i] = malloc(ft_strlen(current->value) + 1);
    ft_strcpy(cmd->args[i],current->value);
    i++;
    current = current->next;
  }
  cmd->args[i] = NULL;
  return (cmd);
}
