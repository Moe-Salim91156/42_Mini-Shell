/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/26 18:14:15 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*shell entry point,*/
int	shell_init(t_shell *shell, char **envp)
{
	// shell->token_list = init_list();
	// shell->cmd_list = init_cmd_list();
	shell->envp_list = init_envp(envp);
	return (0);
}
/*
	flow of rbsh:
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
	t_shell	*shell;
	/* char			*input; */

	 char	**args;
	 args = malloc(6 * sizeof(args));
	 args[0] = ft_strdup("export");
	 args[1] = ft_strdup("arg2");
	 args[2] = ft_strdup("_arg2=shouldseeme");
	 args[3] = ft_strdup("3_arg2=");
	 args[4] = ft_strdup("arg1");
	 args[5] = NULL;
	if (argc != 1 || argv[1])
		return (1);
	shell = malloc(sizeof(t_shell));
	shell_init(shell, envp);
	bltn_export(args, shell->envp_list);
	bltn_env(shell);
	/*while (1)
	{
		input = readline("rbsh$");
		if (!input)
			break ;
		tokenize(input, shell.token_list);
		print_tokens(shell.token_list);
		build_cmd(shell.token_list, shell.cmd_list);
		print_command(shell.cmd_list);
		free(input);
	}*/
	free_env(shell->envp_list);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args[3]);
	free(args[4]);
	free(args[5]);
	free(args);
	free(shell);
	return (0);
}
