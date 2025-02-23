/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/23 19:51:43 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>


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
	t_shell			*shell;
	/* char			*input; */
	char	**args;

	args = calloc(10,sizeof(args));
	args[0] =ft_strdup("export");
	args[1] =ft_strdup("_arg1=this");
	args[2] =ft_strdup("_arg1=yoyo");
	args[3] =ft_strdup("_2arg=b");
	args[4] =ft_strdup("1");
	if (argc != 1 || argv[1])
		return (1);
	shell = malloc (sizeof(t_shell));
	shell_init(shell, envp);
	/* bltn_env(shell); */
	bltn_export(args, shell);
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
	}
	return (0); */
}
