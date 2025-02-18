/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 17:48:46 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*shell entry point,*/
int	shell_init(t_shell *shell, char **envp)
{
	shell->token_list = init_list();
	shell->cmd_list = init_cmd_list();
	shell->envp_list = init_envp(envp);
	return (0);
}
/* flow of rbsh:
	1-read input
	2-tokenize into words and ops
	3-parse/lex words into commands and args
	4-expand $,~,handle ""and''
	5-redirections (if needed)
	6- execute and collect exit status.
	----------------------------------------------
	signal handling and simple builtins are also implemented.
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell			shell;
	char			*input;

	if (argc != 1 || argv[1])
		return (1);
	shell_init(&shell, envp);
	char **test = build_envp(&shell);
	bltn_env(&shell);
	int i = 0;
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
	while (1)
	{
		input = readline("rbsh$");
		if (!input)
			break ;
		tokenize(input, shell.token_list);
		print_tokens(shell.token_list);
		build_cmd(shell.token_list, shell.cmd_list);
		print_command(shell.cmd_list);
		free(input);
	}
	return (0);
}
