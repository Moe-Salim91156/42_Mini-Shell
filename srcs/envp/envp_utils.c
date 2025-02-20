/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:38:32 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/18 19:23:19 by yokitane         ###   ########.fr       */
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
	free(node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (1);
	return (0);
}

int	free_envp_list(t_envp *list)
{
	t_envp *traverse;
	t_envp *temp;

	traverse = list;
	while (traverse)
	{
		temp = traverse;
		traverse = traverse->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	return (0);
}