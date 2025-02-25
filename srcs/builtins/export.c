/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 20:51:18 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	export: takes arguments, then stores values in keys.
	behaviour cases:
		1- no arguments: print all envp (sorted. that last part will cause pain)
		2- :export with @arg(s):
		per @arg
		2.1: invalid key (doesnt begin with alpha or '_')
			--> skip @arg, print out error.
		2.2:@arg has key that already exists.
			2.2A-@arg is solely key (no=)
				--> do nothing to current key.
			2.2B-@arg contains'='
				--> replace current value with new value (anything post '=')
		2.3:@arg has new key.
			2.3A-@arg is solely key (no=)
				--> create new key(entire @arg) with NULL value
			2.3B-@arg contains'='
				--> create new key with value==(anything post =)
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
