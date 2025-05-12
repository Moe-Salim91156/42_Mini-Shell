/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:59:26 by msalim            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * in parent :
 *  : sigint -> display a new prompt;
 *  : sigquit (\) -> ignore;
 *  : ctrl d -> exits the shell; | handled by default
 *
 * in child :
 *  : sigint -> exits the child;
 *  : sigquite -> same behavior in child;
 *  : ctrl d -> exits the shell | handled by default;
 *
 * in heredoc:
 *  sigint -> quits heredoc and closes fd;
 *      -> then display a new prompt;
 *  sigquit -> ignore;
 *  ctrl d -> exits the shell | handled by default; i think;
 *
 * */
void	par_sig_handler(int sig)
{
	if (sig)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = sig;
	}
}

void	child_sig_c(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_first(int sig)
{
	g_sig = sig;
}

void	handle_heredoc_sig(int sig)
{
  g_sig = sig;
  close (0);
	write(1, "\n", 1);
}

void	set_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, par_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, child_sig_c);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 3)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
	}
}
