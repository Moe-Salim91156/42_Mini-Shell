/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:20 by msalim            #+#    #+#             */
/*   Updated: 2025/02/16 19:53:06 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"
void  handle_pipe_token(t_token_list *tokens)
{
  add_token(tokens,"|");
}
void  tokenizer(char *input, t_token_list *tokens)
{
  int i;

  i = 0;
 skip_beginning_spaces(input); 
 while (input[i])
 {
   
 }
}


