/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/24 10:44:59 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	export: takes arguments, then stores values in keys.
	behaviour cases:
		1- no arguments: print all envp list.
		2- :export with @arg(s):
		per @arg:
		2.1: invalid key (doesnt begin with alpha or '_')
			--> skip @arg, print out error.
		2.2:@arg contains '='
			2.2A-key already exists
				--> modify existing node
			2.2B-is key new
				--> create new node and append to list.
		2.3:@arg doesnt contain '='
			--> append '=' to current @arg
				--> reevaluate case 2.2B only.
					--> if true, append key with value = NULL.
		###########
		return value:
			The return status is zero unless an invalid @arg is supplied.
		########### TBD ###########
		nothing inshallah (=
*/

static int	invalid_arg(char *str,int *ret)
{
	if ((!ft_isalpha(*str) && *str != '_') || !*str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(":Invalid Identefier!\n", 2);
		*ret = 1;
		return (1);
	}
	return (0);
}
/*
	assigns value of NULL rather than a literal string.
*/
static t_envp	*build_env_node_null(char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->key = ft_strdup(str);
	new->value = NULL;
	if (!new->key)
		return (NULL);
	return (new);
}

/*
	Code reuse is a fundamental principle of software engineering that
	entails writing code that can be used in a variety of contexts and
	purposes. It's a practice that isn't just good for efficiency and
	productivity; it also opens organizations up to new levels of innovation. ,,
*/
static int	append_env_node_null(t_envp *list, char *str)
{
	t_envp	*visit;
	t_envp	*new;

	if (!list)
	{
		list = build_env_node_null(str);
		if (!list)
			return (1);
		return (0);
	}
	new = build_env_node_null(str);
	visit = list;
	while (visit->next)
		visit = visit->next;
	visit->next = new;
	if (!visit->next)
	{
		ft_putstr_fd("Appending to env failed!\n", 2);
		return (1);
	}
	return (0);
}

/*
	appends an equal sign into buffer @old_arg
	then appends it to list.
*/
static int	append_equal(t_envp *list,char **old_arg)
{
	char	*new_arg;

	new_arg = NULL;
	new_arg = ft_strjoin(*old_arg, "=");
	if (!new_arg)
		return (1);
	free(*old_arg);
	*old_arg = new_arg;
	if (find_str(list,new_arg))
		return (0);
	if(!append_env_node_null(list, new_arg))
		return (0);
	else
		return (1);
}

int	bltn_export(char **args, t_envp *list)
{
	int		i;
	int		ret;
	int		flag;

	i = 0;
	ret = 0;
	flag = 0;
	if (!args[1])
		return (print_env_sorted(list));
	while (args[++i])
	{
		if (invalid_arg(args[i],&ret))
			continue;
		if (!ft_strchr(args[i],'='))
			flag = append_equal(list,&args[i]);
		else if (find_str(list,args[i]))
			flag = mod_val(find_str(list,args[i]),
		(ft_strchr(args[i], '=') + 1));
		else
			flag = append_env_node(list, args[i]);
		if (flag)
			return(1);
	}
	return (ret);
}
