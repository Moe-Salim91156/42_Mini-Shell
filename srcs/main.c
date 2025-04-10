/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/04/11 17:44:43 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	main(void)
{
	t_shell			shell;
	char			*input;

	shell_init(&shell, __environ);
	shell.token_list = init_list();
	shell.cmd_list = init_cmd_list();
	while (1)
	{
		input = readline("rbsh$ ");
		if (!input)
			break;
		if (input)
		{
			add_history(input);
			if (!tokenizer(input, shell.token_list))
				return (0);//wtf is a return doing here.
			lexing(shell.token_list);
			expander_main(shell.token_list);
			build_cmd(shell.token_list, shell.cmd_list);
			lexer_cmd_list(shell.cmd_list);
			print_tokens(shell.token_list);
			print_command((shell.cmd_list));
			// execution_entry(shell);//tbd
			free_tokens(shell.token_list);//this
			free_command_list(shell.cmd_list);//and this
			shell.token_list = NULL;// this too
			shell.token_list = init_list();//dont forget this
			shell.cmd_list = init_cmd_list();// and lastly this, need to put all that stuff in a seperate function (loop_clean or smth)
		}
	}
	//exit_handler
	free(input);
	return (0);
}
