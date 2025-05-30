/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 18:54:59 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;

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

char	*handle_input(char *input)
{
	char	*trimmed;

	if (!input)
		return (NULL);
	trimmed = input;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (*trimmed == '\0')
	{
		free(input);
		return (NULL);
	}
	return (input);
}

void	parse_and_execute(t_shell *shell, char *input)
{
	if (happy_parser_path(input, shell))
	{
		if (!expander_main(shell))
			ft_exit(shell, shell->last_status);
		build_payloads(shell->token_list, shell->cmd_list);
		lexer_cmd_list(shell->cmd_list);
		if (!build_cmd_argv(shell->cmd_list))
			ft_exit(shell, -1);
		shell->cmd_list->payload_count = count_payloads(shell->cmd_list);
		execution_entry(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc, (void)argv;
	shell_init(&shell, envp);
	while (1)
	{
		set_signal(0);
		input = readline("rbsh$ ");
		if (g_sig == SIGINT)
		{
			shell.last_status = 130;
			g_sig = 0;
		}
		if (!input)
			break ;
		input = handle_input(input);
		if (!input)
			continue ;
		parse_and_execute(&shell, input);
		free_and_loop(&shell, input);
	}
	ft_exit(&shell, shell.last_status);
	return (0);
}
