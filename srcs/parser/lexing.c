/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:34:06 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 14:38:09 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexemes(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIRECT_OUT;
	else if (!ft_strcmp(token->value, "<"))
		token->type = REDIRECT_IN;
	else if (ft_strchr(token->value, '-'))
		token->type = ARGS;
	else if (!ft_strcmp(token->value, "\n"))
		token->type = NLINE;
  else if (!ft_strcmp(token->value , ">>"))
    token->type = APPEND;
  else if (!ft_strcmp(token->value, "<<"))
    token->type = HEREDOC;
	else
		token->type = WORD;
}
