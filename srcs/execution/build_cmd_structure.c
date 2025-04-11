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

char  **malloc_cmd_argv(t_cmd *payload)
{
  char **argv;
  int args_num;

  args_num = count_args(payload);
  argv = malloc(sizeof(char *) * (args_num + 1));
  argv[args_num] = NULL;
  return (argv);
}
/*
 * malloc a 2d array argv
 * argv = [path, cmd_and_its_arguments, envp];
 * path will be found using pipex functions;
 * argv building;
 *  // malloc 3 arguments for the whole array;
 *  // cmd_and argument gonna have a sepearte 2d array for them cmd_argv
 *
 *
 */


char  **build_cmd_argv(t_cmd_list *list)
{
  int i;
  int j = 0;
  int args_num;
  t_cmd *payload;

  i = 0;
  payload = list->head;
  args_num = count_args(payload);
  payload->argv = malloc(sizeof(char *) * ( args_num + 1));
  if (!payload->argv)
    return (NULL);
  while (payload->payload_array[i])
  {
    if (payload->type[i] == COMMAND || payload->type[i] == WORD)
    {
      payload->argv[0] = ft_strdup(payload->payload_array[i]);
      break;
    }
    i++;
  }
  i = 0;
  j = 1;
  while (payload->payload_array[i])
  {
    if (payload->type[i] == ARGS)
      payload->argv[j] = ft_strdup(payload->payload_array[i]);
    i++;
    j++;
  }
  payload->argv[args_num] = NULL;
  return (payload->argv);
}
