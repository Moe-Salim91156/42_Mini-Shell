/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:19:11 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 18:11:51 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * here we would put the NEWLINE enum new value
 * for seperating commands(payload);
 * */
int	is_seperator(int type)
{
	return (type == PIPE);
}

char	**allocate_cmd_args(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	args[count] = NULL;
	return (args);
}
