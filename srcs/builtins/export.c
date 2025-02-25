/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 19:24:26 by yokitane         ###   ########.fr       */
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

static int	invalid_arg(char *str)
{
	if ((!ft_isalpha(*str) && *str != '_') || !*str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(":Invalid Identefier!\n", 2);
		return (1);
	}
	return (0);
}
/* looks for valid key in @str, fills it into buffer @key this
is useful for handling no '=' and updating already existing keys. */
static int	extract_key(char *str, char **key)
{
	if (!str)
		return (1);
	if (!ft_strchr(str, '='))
	{
		*key = ft_strjoin(str, "=");
		if (!key)
			return (1);
		return (0);
	}
	*key = ft_substr(str, 0, ft_strchr(str, '=') + 1 - str);
	if (!key)
		return (1);
	return (0);
}

/* updates an already existing node.*/
static int	update_node(t_shell *shell, char *str, char *key)
{
	modify_value(find_by_key(shell->envp_list, key), (ft_strchr(str, '=') + 1));
	return (0);
}

int	bltn_export(char **args, t_shell *shell)
{
	int		i;
	int		ret;
	char	*key;

	ret = 1;
	if (!args[1])
		return (bltn_env(shell));
	i = 0;
	while (args[++i])
	{
		if (invalid_arg(args[i]))
			continue ;
		ret = 0;
		key = NULL;
		extract_key(args[i], &key);
		if (find_by_key(shell->envp_list, key))
			update_node(shell, args[i], key);
		else if (append_env_node(shell->envp_list, args[i]))
			return (1);
	}
	return (ret);
}
