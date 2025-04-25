/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/04/25 17:47:40 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_payloads(t_cmd_list *list)
{
	t_cmd	*pay;

	pay = list->head;
	while (pay && pay->argv[0])
	{
		list->payload_count++;
		pay = pay->next;
	}
	return (list->payload_count);
}

void  free_and_loop(t_shell *shell, char *input)
{
      free(input);
      free_tokens(shell->token_list);     // this
			free_command_list(shell->cmd_list); // and this
			shell->token_list = NULL;           // this too
			shell->token_list = init_list();    // dont forget this
			shell->cmd_list = init_cmd_list();  // and lastly this,

}

int happy_parser_path(char *input, t_shell *shell)
{
	if (!input)
		return (0);
	add_history(input);
	if (!tokenizer(input, shell->token_list, shell))
		return (0);
	if (!lexing(shell, shell->token_list))
		return (0);
	if (!check_unexpected_token(shell, shell->token_list))
		return (0);
	return (1); // success
}

int	main(void)
{
	t_shell shell;
	char	*input;

	shell_init(&shell, __environ);
	while (1)
	{
		input = readline("rbsh$ ");
		if (!input)
			break ;

		if (happy_parser_path(input, &shell))
		{
			expander_main(&shell);
			build_payloads(shell.token_list, shell.cmd_list);
			see_heredoc_if_quoted(&shell);
			lexer_cmd_list(shell.cmd_list);
			build_cmd_argv(shell.cmd_list);
			shell.cmd_list->payload_count = count_payloads(shell.cmd_list);
			execution_entry(&shell);
		}
		free_and_loop(&shell, input);
	}
	printf("exit\n");
	return (0);
}

