/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:47:33 by msalim            #+#    #+#             */
/*   Updated: 2025/04/10 19:54:27 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"

// takes the payload
// extracts the cmd and its args
// put it into payload->argv
int count_args(t_cmd *payload)
{
  int i; 
  int count;

  count = 0;
  i = 0;
  while (payload->payload_array[i])
  {
  if (payload->type[i] == ARGS || payload->type[i] == COMMAND || payload->type[i] == WORD)
      count++;
    i++;
  }
  return (count);
}

char  **malloc_argv(t_cmd *payload)
{
  char **argv;
  int args_num;

  args_num = count_args(payload);
  

}

void  fill_args_for_cmd(t_cmd *payload, int *i, int *j)
{
  while (payload->payload_array[*i])
  {
    if (payload->type[*i] == ARGS)
    {
      payload->argv[*j] = payload->payload_array[*i];
      j++;
    }
    i++;
  }
}

char  **build_cmd_argv(t_cmd_list *list)
{
  int i;
  int j;
  t_cmd *payload;

  payload = list->head;
  i = 0;
  j = 0;
  while (payload->payload_array[i])
  {
    if (payload->type[i] == COMMAND || payload->type[i] == WORD)
    {
      payload->argv[j] = payload->payload_array[i];
      j++;
      i++;
    }
    fill_args_for_cmd(payload, &i, &j);
  }
  return (payload->argv);
}
