/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/04/16 14:27:55 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	t_shell shell; // please add this
	shell_init(&shell, __environ);
	shell.token_list = init_list();
	shell.cmd_list = init_cmd_list();
	while (1)
	{
		input = readline("rbsh$ ");
		if (!input)
			break ;
		if (input)
		{
			add_history(input);
			if (!tokenizer(input, shell.token_list))
				return (0); // wtf is a return doing here.
			lexing(shell.token_list);
			expander_main(&shell);
			build_payloads(shell.token_list, shell.cmd_list);
			see_heredoc_if_quoted(&shell);
			lexer_cmd_list(shell.cmd_list);
			print_tokens(shell.token_list);
			print_command((shell.cmd_list));
			build_cmd_argv(shell.cmd_list);
			locate_heredoc(shell.cmd_list, &shell);
			debug_build_cmd_argv(shell.cmd_list);
			free_tokens(shell.token_list);     // this
			free_command_list(shell.cmd_list); // and this
			shell.token_list = NULL;           // this too
			shell.token_list = init_list();    // dont forget this
			shell.cmd_list = init_cmd_list();  // and lastly this,
												// need to put all that stuff in a seperate function(loop_clean or smth)
		}
	}
	// exit_handler
	free(input);
	return (0);
}
