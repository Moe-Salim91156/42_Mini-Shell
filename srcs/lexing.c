/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:34:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/11 15:57:21 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

void  lexemes(t_token *token)
{
  if (!ft_strcmp(token->value,"|"))
    token->type = PIPE;
  else if (!ft_strcmp(token->value,">"))
    token->type = REDIRECT_OUT;
  else if (!ft_strcmp(token->value, "<"))
    token->type = REDIRECT_IN;
  else if (ft_strchr(token->value, '-'))
    token->type = ARGS;
  else
    token->type = WORD;
}

