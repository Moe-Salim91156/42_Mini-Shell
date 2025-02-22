/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:34:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/22 14:24:36 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexing(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		lexemes(current);
		current = current->next;
	}
	current = list->head;
  while (current)
  {
    if (current->type == WORD)
    {
      current = current->next;
      while (current && current->type != REDIRECT_OUT)
      {
        current->type = ARGS;
        current = current->next;
      }
    }
    else
      current = current->next;
  }
}

void	lexemes(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIRECT_OUT;
	else if (!ft_strcmp(token->value, "<"))
		token->type = REDIRECT_IN;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = HEREDOC;
	else
		token->type = WORD;
}
