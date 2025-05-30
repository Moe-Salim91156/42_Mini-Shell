/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:05:32 by msalim            #+#    #+#             */
/*   Updated: 2025/04/23 16:04:58 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*lexer protal , give each token in the list a type using lexemes func*/
/*and then does the logic of identifying argv*/

static int	is_redirection(t_token *token)
{
	return (token->type == REDIRECT_OUT || token->type == REDIRECT_IN
		|| token->type == APPEND || token->type == HEREDOC);
}

static void	handle_word(t_token *token, int *next_is_cmd, int *saw_redirect)
{
	if (*saw_redirect)
	{
		token->type = FILE_TOKEN;
		*saw_redirect = 0;
	}
	else if (*next_is_cmd)
	{
		token->type = COMMAND;
		*next_is_cmd = 0;
	}
	else
		token->type = ARGS;
}

void	assign_command_and_argv(t_token_list *list)
{
	t_token	*current;
	int		next_is_command;
	int		just_saw_redirect;

	current = list->head;
	next_is_command = 1;
	just_saw_redirect = 0;
	while (current)
	{
		if (current->type == PIPE)
		{
			next_is_command = 1;
			just_saw_redirect = 0;
		}
		else if (is_redirection(current))
			just_saw_redirect = 1;
		else if (current->type == WORD)
			handle_word(current, &next_is_command, &just_saw_redirect);
		current = current->next;
	}
}

int	lexing(t_shell *shell, t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		if (!lexemes(current))
		{
			printf("syntax error near \"<<\" token\n");
			shell->last_status = 127;
			return (0);
		}
		current = current->next;
	}
	assign_command_and_argv(list);
	return (1);
}

/*responsible for lexing each node*/
int	lexemes(t_token *token)
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
	{
		token->type = HEREDOC;
		if (!token->next || !token->next->value || !*token->next->value
			|| !ft_strcmp(token->next->value, "<<"))
			return (0);
		else
			token->next->type = HEREDOC_DELIMITER;
	}
	else if (!ft_strcmp(token->value, "<<"))
	{
		token->type = HEREDOC;
		token->next->type = HEREDOC_DELIMITER;
	}
	else if (ft_strchr(token->value, '-'))
		token->type = ARGS;
	return (1);
}
