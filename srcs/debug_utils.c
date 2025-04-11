/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:10 by msalim            #+#    #+#             */
/*   Updated: 2025/04/09 16:41:05 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void print_command(t_cmd_list *cmd_list)
{
    t_cmd *cmd;
    int    i;
    int    index;

    index = 0;
    cmd = cmd_list->head;
    while (cmd)
    {
        printf("=========== Command %d ===========\n", index);
        
        // Print the payload and corresponding token types in a more structured format
        i = 0;
        while (cmd->payload_array[i])
        {
            printf("argv[%d]: %-20s | Type[%d]: %-3d\n", i, cmd->payload_array[i], i, cmd->type[i]);
            i++;
        }
        printf("argv[%d]: %-20s | Type[%d]: %-3d\n", i, "NULL", i, 0);  // Mark the end of the array
        
        // Print a separator for readability between different commands
        printf("\n==============================\n\n");
        
        cmd = cmd->next;
        index++;
    }
    printf("Total commands in list: %d\n", cmd_list->count);
}
void print_payload(t_cmd *payload)
{
    int i = 0;

    // Print the payload_array and types for debugging
    printf("payload_array and types:\n");
    while (payload->payload_array[i])
    {
        printf("[%d] %s (type: %d)\n", i, payload->payload_array[i], payload->type[i]);
        i++;
    }
}

void debug_build_cmd_argv(t_cmd_list *list)
{
    t_cmd *payload = list->head;

    if (!payload)
    {
        printf("Payload is NULL\n");
        return;
    }
    print_argv(payload);
}
void print_argv(t_cmd *payload)
{
    int i = 0;

    // Print the entire argv array (for execve)
    printf("argv array:\n");
    while (payload->argv[i])
    {
        printf("[%d] %s\n", i, payload->argv[i]);
        i++;
    }
}

void	print_tokens(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		printf("token: ([%s] :: type %d)\n", current->value, current->type);
		current = current->next;
	}
}
