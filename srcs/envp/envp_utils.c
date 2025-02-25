/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:38:32 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 18:17:01 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* counts how many keys are there */
int	envp_count(t_envp *list)
{
	int		count;
	t_envp	*traverse;

	count = 0;
	traverse = list;
	while (traverse)
	{
		count++;
		traverse = traverse->next;
	}
	return (count);
}
/* returns node with matching key */
t_envp	*find_by_key(t_envp *envp, char *key)
{
	t_envp	*traverse;

	if (!key || !envp)
		return (NULL);
	traverse = envp;
	while (traverse)
	{
		if (!ft_strcmp(traverse->key, key))
			return (traverse);
		traverse = traverse->next;
	}
	return (NULL);
}

int	modify_value(t_envp *node, char *new_value)
{
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (1);
	return (0);
}

int	del_env_node(t_envp	*node)
{
	if (node)
	{
		if(node->key)
			free (node-> key);
		if (node->value)
			free(node->value);
		free (node);
		return (0);
	}
	return (1);
}
