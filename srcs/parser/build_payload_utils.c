/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_payload_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:19:11 by msalim            #+#    #+#             */
/*   Updated: 2025/04/05 17:19:17 by yokitane         ###   ########.fr       */
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

char	**allocate_cmd_argv(int count)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	argv[count] = NULL;
	return (argv);
}
