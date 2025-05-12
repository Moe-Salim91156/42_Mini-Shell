/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/05/12 13:22:48 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;

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

void	free_and_loop(t_shell *shell, char *input)
{
	if (input)
		free(input);
	input = NULL;
	if (shell->token_list && shell->cmd_list)
	{
		free_tokens(shell->token_list);
		free_command_list(shell->cmd_list);
		shell->token_list = NULL;
		shell->token_list = init_list();
		shell->cmd_list = init_cmd_list();
  }
}

int	happy_parser_path(char *input, t_shell *shell)
{
	if (!input)
		return (0);
	if (input[0])
		add_history(input);
	if (!tokenizer(input, shell->token_list, shell))
		return (0);
	if (!lexing(shell, shell->token_list))
		return (0);
	if (!check_unexpected_token(shell, shell->token_list))
		return (0);
	return (1);
}

char *handle_input(char *input)
{
	char *trimmed;

	if (!input)
		return (NULL);

	trimmed = input;
	while (*trimmed == ' ')
		trimmed++;

	if (*trimmed == '\0')
	{
		free(input);
		return (NULL);
	}

	return (input);
}
int main(void)
{
	t_shell shell;
	char *input;

	shell_init(&shell, __environ);
	while (1)
	{
		set_signal(0);
		input = readline("rbsh$ ");
		if (!input)
			break;
		input = handle_input(input);
		if (!input)
			continue;
		if (happy_parser_path(input, &shell))
		{
			expander_main(&shell);
			build_payloads(shell.token_list, shell.cmd_list);
			lexer_cmd_list(shell.cmd_list);
			build_cmd_argv(shell.cmd_list);
			shell.cmd_list->payload_count = count_payloads(shell.cmd_list);
			execution_entry(&shell);
		}
		free_and_loop(&shell, input);
	}
	return (0);
}
