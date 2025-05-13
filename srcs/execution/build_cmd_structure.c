/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:47:33 by msalim            #+#    #+#             */
/*   Updated: 2025/05/13 19:12:01 by msalim           ###   ########.fr       */
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
	argv = malloc(sizeof(char *) * (args_num + 3));
	if (!argv)
		return (NULL);
	argv[args_num] = NULL;
	return (argv);
}

static int	nop_case(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->payload_array[i])
	{
		if (cmd->type[i] == COMMAND)
			return (0);
		i++;
	}
	return (1);
}

static int	fill_cmd_argv(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->payload_array[i])
	{
		if ((!i) && nop_case(cmd) && (cmd->type[1] == FILE_TOKEN
				|| cmd->type[1] == HEREDOC_DELIMITER))
			cmd->argv[j++] = ft_strdup("NOPXRBSH");
		else if (cmd->type[i] == COMMAND || cmd->type[i] == ARGS)
			cmd->argv[j++] = ft_strdup(cmd->payload_array[i]);
		if (!cmd->argv[j - 1])
			return (1);
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
		if (fill_cmd_argv(payload))
			return (NULL);
		payload = payload->next;
	}
	return (list->head->argv);
}
