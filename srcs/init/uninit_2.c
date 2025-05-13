/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:20:18 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 16:28:22 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"
void	clean_double_quote_context(t_double_quote_context *ctx)
{
	if (ctx->temp)
		free(ctx->temp);
	if (ctx->last_result && ctx->last_result != ctx->temp)
		free(ctx->last_result);
	if (ctx->expanded_result && ctx->expanded_result != ctx->temp 
		&& ctx->expanded_result != ctx->last_result)
		free(ctx->expanded_result);
}

void	clean_normal_mode_context(t_normal_mode_context *ctx)
{
	if (ctx->temp)
		free(ctx->temp);
	if (ctx->new_expanded && ctx->new_expanded != ctx->temp)
		free(ctx->new_expanded);
}

void	clean_expand_env_context(t_expand_env_context *ctx)
{
	if (ctx->before_str)
		free(ctx->before_str);
	if (ctx->env_name)
		free(ctx->env_name);
	if (ctx->env_value)
		free(ctx->env_value);
	if (ctx->result)
		free(ctx->result);
	if (ctx->final_result)
		free(ctx->final_result);
}
int cleanup_expander_contexts(t_expand_env_context *env_ctx, t_normal_mode_context *normal_ctx, t_double_quote_context *double_context)
{
  if (double_context)
    clean_double_quote_context(double_context);
  if (normal_ctx)
    clean_normal_mode_context(normal_ctx);
  if (env_ctx)
    clean_expand_env_context(env_ctx);
  return (-1);
}
