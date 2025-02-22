/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/22 22:49:37 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>

/* 	export: takes arguments, then stores values in keys.
	things to handle:
	1- no arguments: print all envp (outlier, this is not
	 required, and you can handle this anyway, this is how I
	 chose to handle it.)
	-------------------------------------
	cases:
	key only (no '=' or empty value)
		--> assign key a value of ""
	invalid key (begining with anything other than alpha/'_')
		--> dont assign key, skip @arg, print invalid identifier err.
	valid key:
		--> key already exists, overwrite current value
		--> create key and value.
*/

static int invalid_arg(char *str)
{
	if (!ft_isalpha(str[0]) || str[0] != '_')
		return (1);
	return (0);
}
static char *extract_key(char *str)
{
	if (!ft_strchr(str, '='))
		return (NULL);
	
}

int	bltn_export(char **args, t_shell *shell)
{
	int		i;
	int		ret;

	ret = 1;
	if (!args[1])
	{
		bltn_env(shell);
		return (0);
	}
	i = -1;
	while (args[++i])
	{
		if (invalid_arg(args[i]))
			continue;
		ret = 0;
		if (find_by_key(shell->envp_list,extract_key(args[i])))
		{
			modify_value(find_by_key(shell->envp_list,
		extract_key(args[i])), ft_strchr(args[i],'+') + 1);
			continue;
		}
		if (append_env_node(shell->envp_list, args[i]))
			return (1);
	}
	return (ret);
}
