/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/23 15:42:34 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 	export: takes arguments, then stores values in keys.
	things to handle:
	1- no arguments: print all envp (sorted. this will cause great suffering)
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
	if (!ft_isalpha(*str) && *str != '_')
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(":Invalid Identefier!", 2);
		return (1);
	}
	return (0);
}

static char *extract_key(char *str)
{
	if (!ft_strchr(str, '='))
		return (NULL);
	return (ft_substr(str, 0, ft_strchr(str, '=') - str + 1));
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
	i = 0;
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
