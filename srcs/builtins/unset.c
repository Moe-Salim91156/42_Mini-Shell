/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:34:50 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/05 22:38:58 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	unset: remove each variable from envp list.
	###########
	return value:
	zero unless a variable may not be unset
	###########
	notes to self:
	unset is pretty simple, it takes @argv and looks for exact matches
	in @list. if found, it deletes them, edits list pointers accordingly.
	in our case its return value is pretty much always 0. as we dont
	incorporate enviroment variable permissons,
		so a variable may always be unset.
	#####
*/

/*
	I swear I've done this function before
	if you find it delete this shit
*/
t_envp	*ft_getenv(t_envp *list, char *str)
{
	char	*key;
	t_envp	*ret;

	key = ft_strjoin(str, "=");
	if (!key)
		return (NULL);
	ret = find_by_key(list, key);
	free(key);
	return (ret);
}

static int	unset_arg(char *arg, t_envp **list_ptr)
{
	t_envp	*current;
	t_envp	*prev;
	t_envp	*list;

	if (envp_count_all(*list_ptr) == 1)
		return (printf("cant unset...are you root?\n"));
	list = *list_ptr;
	current = ft_getenv(list, arg);
	if (!current)
		return (0);
	if (current == list)
	{
		*list_ptr = current->next;
		del_env_node(current);
		return (0);
	}
	prev = list;
	while (prev && prev->next != current)
		prev = prev->next;
	prev->next = current->next;
	del_env_node(current);
	return (0);
}

int	bltn_unset(char **argv, t_envp **list)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (argv[++i])
	{
		if (!ft_getenv(*list, argv[i]))
			continue ;
		if (unset_arg(argv[i], list))
			ret = 1;
	}
	return (ret);
}
