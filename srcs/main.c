/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/11 19:51:58 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	skip_beginning_spaces(char *str)
{
	while (*str == ' ')
		str++;
}

void	print_tokens(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
    lexemes(current);
		printf("token: ([%s] :: type %d)\n", current->value, current->type);
		current = current->next;
	}
}
void  print_command(t_cmd *cmd)
{
 int i;

 i = 0;
 while (i < cmd->count)
 {
   printf("cmd %s\n",cmd->args[i]);
   i++;
 }
}

int	main(void)
{
	t_token_list	*tokens;
  t_cmd *cmd;
	char			*input;

	tokens = init_list();
  cmd = init_command();
	while (1)
	{
		input = readline(COLOR_MAGENTA "Ashen$ " COLOR_RESET);
		if (!input)
			break ;
		tokenize(input, tokens);
		print_tokens(tokens);
    build_cmd(tokens,cmd);
    print_command(cmd);
		free(input);
	}
	return (0);
}
