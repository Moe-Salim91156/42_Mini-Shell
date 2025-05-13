/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:06:20 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 18:26:20 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_redirection_token(char *input, int *i, t_token_list *tokens)
{
	char	*result;

	if (input[*i] == '>' && input[*i + 1] == '>' && input[*i + 2] != '>')
	{
		if (!add_token(tokens, ">>"))
			return (-1);
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<' && input[*i + 2] != '<')
	{
		if (!add_token(tokens, "<<"))
			return (-1);
		*i += 2;
	}
	else
	{
		result = handle_redirect_helper(input, i, tokens);
		if (!result)
			return (-1);
		(*i)++;
	}
	return (1);
}

int	handle_redirect(char *input, int *i, int *start, t_token_list *tokens)
{
	if (!is_invalid_redirection(input, *i))
		return (0);
	if (!substr_and_add(input, *start, *i, tokens))
		return (-1);
	if (add_redirection_token(input, i, tokens) == -1)
		return (-1);
	*start = *i;
	return (1);
}

static int	handle_redirect_token(t_tokenizer_ctx *ctx)
{
	int	ret;

	ret = handle_redirect(ctx->input, &ctx->i, &ctx->start, ctx->tokens);
	if (ret == -1)
		return (-1);
	if (ret == 0)
		return (0);
	return (1);
}

static int	handle_tokenizer_logic(t_tokenizer_ctx *ctx)
{
	int	ret;

	if (is_seperator_token(ctx->input[ctx->i]))
		handle_separator(ctx->input, &ctx->i, &ctx->start, ctx->tokens);
	else if (is_redirect(ctx->input[ctx->i]))
	{
		ret = handle_redirect_token(ctx);
		if (ret != 1)
			return (ret);
	}
	else if (is_quotes(ctx->input[ctx->i]))
	{
		if (!handle_quotes(ctx->input, &ctx->i, ctx->shell))
			return (0);
	}
	else
		ctx->i++;
	return (1);
}

int	tokenizer(char *input, t_token_list *tokens, t_shell *shell)
{
	t_tokenizer_ctx	ctx;
	int				ret;

	ctx.input = input;
	ctx.i = 0;
	ctx.start = 0;
	ctx.tokens = tokens;
	ctx.shell = shell;
	while (ctx.input[ctx.i])
	{
		ret = handle_tokenizer_logic(&ctx);
		if (ret != 1)
			return (ret);
	}
	if (!add_last_token(ctx.input, ctx.start, ctx.i, ctx.tokens))
		return (-1);
	return (1);
}
