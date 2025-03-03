/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:38:32 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/04 02:56:32 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	counts current nodes literal values.
*/
int	envp_count(t_envp *list)
{
	int		count;
	t_envp	*traverse;

	count = 0;
	traverse = list;
	while (traverse)
	{
		if (traverse->value)
			count++;
		traverse = traverse->next;
	}
	return (count);
}
/*
	returns node with @key from @list
	NULL if no match.
 */
t_envp	*find_by_key(t_envp *list, char *key)
{
	t_envp	*traverse;

	if (!key || !list)
		return (NULL);
	traverse = list;
	while (traverse)
	{
		if (!ft_strcmp(traverse->key, key))
			return (traverse);
		traverse = traverse->next;
	}
	return (NULL);
}

int	mod_val(t_envp *node, char *new_value)
{
	if (!new_value || !node)
		return (1);
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (1);
	return (0);
}

/*
	this deletes a node. does not edit
	list pointers at all. use only to
	delete indiviual nodes.
*/
int	del_env_node(t_envp *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
		return (0);
	}
	return (1);
}

t_envp	*find_str(t_envp *list,char *str)
{
	char	*key;
	t_envp	*find;

	find = NULL;
	key = ft_substr(str, 0, (ft_strchr(str, '=') + 1 - str));
	if (!key)
		return (NULL);
	find = find_by_key(list, key);
	free (key);
	return(find);
}
