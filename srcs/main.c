/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/16 18:24:08 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   Updated: 2025/02/15 16:18:03 by yokitane         ###   ########.fr       */
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

void free_tokens(t_token_list *list)
{
    t_token *current;
    t_token *temp;

    current = list->head;
    while (current)
    {
        temp = current->next;  // Store next node before freeing current

        if (current->value) // Free token value if allocated
            free(current->value);

        free(current);  // Free the token node itself

        current = temp; // Move to the next token
    }

    free(list); // Free the token list struct itself
}
void free_command_list(t_cmd_list *cmd_list)
{
    t_cmd *current;
    t_cmd *temp;

    current = cmd_list->head;
    while (current)
    {
        temp = current->next;
        if (current->args)  // Free args array
        {
            int i = 0;
            while (current->args[i])
                free(current->args[i++]); // Free each argument
            free(current->args);
        }
        free(current); // Free the command node itself
        current = temp;
    }
    free(cmd_list); // Free the command list structure
}


void	print_command(t_cmd_list *cmd_list)
{
	t_cmd	*cmd;
	int		i;
	int		index;

	i = 0;
	index = 0;
	cmd = cmd_list->head;
	while (cmd)
	{
		printf("command %d\n", index);
		i = 0;
		while (cmd->args[i])
		{
			printf("args[%d] : %s\n", i, cmd->args[i]);
			i++;
		}
		printf("args[%d] : NULL\n", i);
		cmd = cmd->next;
		index++;
	}
	printf("number of arguments in total allocated %d\n", cmd_list->count);
}

int	main(void)
{
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	char			*input;

	tokens = init_list();
	cmd_list = init_cmd_list();
	while (1)
	{
		input = readline(COLOR_MAGENTA "rbsh$ " COLOR_RESET);
		if (!input)
			break;
    if (input)
    {
		tokenizer(input, tokens);
		print_tokens(tokens);
		build_cmd(tokens, cmd_list);
		print_command(cmd_list);
    cmd_list = NULL;
    tokens = NULL;
    tokens = init_list();
    cmd_list = init_cmd_list();
    }
	}
    free(input);
	return (0);
}
