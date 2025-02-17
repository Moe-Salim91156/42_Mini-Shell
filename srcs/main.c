/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 00:14:53 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*shell entry point,*/
int	main(void)
{
	t_shell			shell;
	char			*input;
	/*the following should go into shell init*/
	shell.token_list = init_list();
	shell.cmd_list = init_cmd_list();
	shell.envp_list = init_envp(__environ);
	while (1)
	{
		input = readline("rbsh$ ");
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
