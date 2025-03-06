/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/03/06 04:21:25 by yokitane         ###   ########.fr       */
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

	if (argc != 1 || argv[1])
		return (1);
	shell = malloc(sizeof(t_shell));
	shell_init(shell, envp);
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
	char *args2[]= {"cd","..",0};
	char *args1[]= {"cd",0};
	char **args3 = malloc(sizeof(args3) * 3);
	args3[0] = ft_strdup("3");
	args3[2] = NULL;
	bltn_pwd();
	bltn_cd(args1, shell->envp_list);
	bltn_pwd();
	bltn_cd(args2, shell->envp_list);
	bltn_pwd();
	args3[1] = ft_strdup(ft_getenv(shell->envp_list, "OLDPWD")->value);
	bltn_cd(args3, shell->envp_list);
	bltn_pwd();
	free_env(shell->envp_list);
	free(shell);
	free(args3[0]);
	free(args3[1]);
	free(args3[2]);
	free(args3);
	return (0);
}
