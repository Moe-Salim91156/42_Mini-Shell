/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:59:26 by msalim            #+#    #+#             */
/*   Updated: 2025/04/26 16:06:58 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"


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

void    sigint_handler_main(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    sigint_handler_heredoc(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    exit(130); // exit immediately from heredoc
}

void    setup_signals_heredoc(void)
{
    signal(SIGINT, sigint_handler_heredoc);
    signal(SIGQUIT, SIG_IGN);
}

void    setup_signals_main(void)
{
    signal(SIGINT, sigint_handler_main);
    signal(SIGQUIT, SIG_IGN);
}
