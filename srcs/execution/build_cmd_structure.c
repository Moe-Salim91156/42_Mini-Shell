/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:47:33 by msalim            #+#    #+#             */
/*   Updated: 2025/05/10 16:43:04 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_cmd *payload)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (payload->payload_array[i])
	{
		if (payload->type[i] == ARGS || payload->type[i] == COMMAND)
			count++;
		i++;
	}
	return (count);
}

char	**malloc_cmd_argv(t_cmd *payload)
{
	char	**argv;
	int		args_num;

	args_num = count_args(payload);
	argv = malloc(sizeof(char *) * (args_num + 1));
	if (!argv)
		return (NULL);
	argv[args_num] = NULL;
	return (argv);
}
/*
 * malloc a 2d array argv
 * argv = [path, cmd_and_its_arguments, envp];
 * path will be found using pipex functions;
 * argv building;
 *  // malloc 3 arguments for the whole array;
 *  // cmd_and argument gonna have a sepearte 2d array for them cmd_argv
 *
 *
 */

static int	fill_cmd_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*arg;

	i = 0;
	j = 0;
	while (cmd->payload_array[i])
	{
		if (cmd->type[i] == COMMAND || cmd->type[i] == ARGS)
		{
			arg = ft_strdup(cmd->payload_array[i]);
			if (arg)
				cmd->argv[j++] = arg;
		}
		i++;
	}
	cmd->argv[j] = NULL;
	return (0);
}

char	**build_cmd_argv(t_cmd_list *list)
{
	t_cmd	*payload;

	payload = list->head;
	while (payload)
	{
		payload->argv = malloc_cmd_argv(payload);
		if (!payload->argv)
			return (NULL);
		fill_cmd_argv(payload);
		payload = payload->next;
	}
	return (list->head->argv);
}

/*
char	**build_payload_argv(t_cmd *payload)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	payload->argv = malloc_cmd_argv(payload);
	if (!payload->argv)
		return (NULL);
	while (payload->payload_array[i])
	{
		if (payload->type[i] == COMMAND && ft_strcmp(payload->payload_array[i],
				" "))
		{
			payload->argv[0] = ft_strdup(payload->payload_array[i]);
			break ;
		}
		i++;
	}
	while (payload->payload_array[i])
	{
		if (payload->type[i] == ARGS)
		{
			payload->argv[j] = ft_strdup(payload->payload_array[i]);
			j++;
		}
		i++;
	}
	payload->argv[j] = NULL;
	return (payload->argv);
}*/
