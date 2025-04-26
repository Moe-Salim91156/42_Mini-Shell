/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:37:12 by msalim            #+#    #+#             */
/*   Updated: 2025/04/24 14:46:22 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* syntax check unit
 * unexpected tokens at end or beginning of input, |, >, >>, (< << -> its ok )
 * two operators in a row without valid command in between.
 * missing argument, < without a file >
 * */

/*
 * parse handled the following :
 *  1. >>>>>>> or <<<<<<<<< , left is setting up shell_status;
 *  2. unclosed and unmateched quotes;
 * */

/*
 * lexer should handle those;
 * 1. << << , missing argument, next should be a file.
 * 2. || <> , two operators in a row without a valid argument
 * */

int	valid_redirection(t_token *current)
{
	if ((current->type == REDIRECT_IN || current->type == REDIRECT_OUT
			|| current->type == APPEND))
	{
		if (!current->next || current->next->type != FILE_TOKEN)
		{
			ft_putendl_fd("rbsh: syntax error near unexpected token `newline`",
				2);
			return (0);
		}
	}
	return (1);
}

int	valid_heredoc(t_token *current)
{
	if (current->type == HEREDOC)
	{
		if (!current->next || current->next->type != HEREDOC_DELIMITER)
		{
			ft_putendl_fd("rbsh: syntax error near unexpected token `<<`", 2);
			return (0);
		}
	}
	return (1);
}

int	invalid_operator_sequence(t_token *curr)
{
	if (!curr->next)
		return (0);
	if ((curr->type == PIPE || curr->type == REDIRECT_OUT
			|| curr->type == REDIRECT_IN || curr->type == APPEND
			|| curr->type == HEREDOC) && (curr->next->type == PIPE
			|| curr->next->type == REDIRECT_OUT
			|| curr->next->type == REDIRECT_IN || curr->next->type == APPEND
			|| curr->next->type == HEREDOC))
	{
		ft_putstr_fd("rbsh: syntax error near unexpected token `", 2);
		ft_putstr_fd(curr->next->value, 2);
		ft_putendl_fd("`", 2);
		return (1);
	}
	return (0);
}

int	check_unexpected_token(t_shell *shell, t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		if ((current->type == PIPE && !current->next)
			|| list->head->type == PIPE)
		{
			ft_putendl_fd("rbsh: syntax error near unexpected token `newline`",
				2);
			shell->last_status = 127;
			return (0);
		}
		if (!valid_redirection(current) || !valid_heredoc(current)
			|| invalid_operator_sequence(current))
		{
			shell->last_status = 127;
			return (0);
		}
		current = current->next;
	}
	return (1);
}
