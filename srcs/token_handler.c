/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:49:10 by msalim            #+#    #+#             */
/*   Updated: 2025/02/15 20:03:08 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(char **str,t_token_list *token)
{
  add_token(token, "|");
  (*str)++;
}

void  handle_single_quote(char **str, t_token_list *tokens)
{
  char  *result;
  char  *start;
  char  *end;
  int length;

  start = *str + 1;
  while (*start == '\'')
    start++;
  end = ft_strchr(start, '\'');
  if (!end)
  {
    //
    return;
  }
  length = (end - start);
  result = malloc(length + 1);
  if (!result)
  {
    //
    return;
  }
  ft_strncpy(result, start, length);
  result[length] = '\0';
  add_token(tokens, result);
  *str = end + 1;
}
