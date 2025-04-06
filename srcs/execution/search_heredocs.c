/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/04/06 15:30:38 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"


/*
 * lookup payloads array of args for (<<)
 * if found execute the heredoc function
 *  ::: heredoc function: 
 *      1. iterate through each payload args; 
 *      2. look for (<<) for heredoc;
 *      3. fill the buffer for heredoc for each payload, to be read by anything afterwards;
 *      4. thats it;
 *
 * */

int search_in_args(t_cmd *payload)
{
  int i;
  int here_doc_counts;

  i = 0;
  here_doc_counts = 0;
  while (payload->argv[i])
  {
    if (!ft_strcmp(payload->argv[i],"<<"))
    {
      printf("here doc found in argv of %d\n",i);
      here_doc_counts++;
    }
    i++;
  }
  if (here_doc_counts > 0)
    return (1);
  return (0);
}

int locate_heredoc(t_cmd_list *cmd_list)
{
  t_cmd *payload;

  payload = cmd_list->head;
  while (payload != NULL)
  {
    search_in_args(payload);
    payload = payload->next;
  }
  return (0);
}
