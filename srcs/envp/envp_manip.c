/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/18 18:29:00 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	what do we need with envp?
	1-init
	2-adding(export)
	3-removing(unset)
	4-easy key value lookup(expandning)
	5-construct execve-compatible envp(2d array)
	----------------------------------------------
*/

/*goes through the envp and creates a linked list of envp
 linked list is used to allow manipulating envp*/
t_envp *init_envp(char **envp)
{
	t_envp *envp_list = NULL;
	t_envp *new, *last = NULL;
	int i = 0;

	while (envp[i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
			return (NULL); // exit handler later
		new->key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		new->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		new->next = NULL;
		if (!new->key || !new->value)
			return (NULL); // exit handler later
		if (!envp_list)
			envp_list = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (envp_list);
}


/*returns an execve compatible 2d array of envp*/
char **build_envp(t_shell *shell)
{
	t_envp	*traverse;
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (envp_count(shell->envp_list) + 1));
	if (!envp)
		return (NULL);//exit handler later
	traverse = shell->envp_list;
	while (traverse)
	{
		envp[i] = ft_strjoin(traverse->key, traverse->value);
		if (!envp[i])
			return (NULL);//exit handler later
		traverse = traverse->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
/* removes *remove from *list */
int	remove_envp_node(t_envp *list, t_envp *remove)
{
	t_envp	*traverse;

	traverse = list;
	if (traverse == remove)
	{
		list = list->next;
		free(traverse->key);
		free(traverse->value);
		free(traverse);
		return (0);
	}
	while (traverse->next)
	{
		if (traverse->next == remove)
		{
			traverse->next = remove->next;
			free(remove->key);
			free(remove->value);
			free(remove);
			return (0);
		}
		traverse = traverse->next;
	}
	return (1);
}
/* appends a new node with key value to list */
int	append_envp_node(t_envp *list, char *key, char *value)
{
	t_envp	*new;
	t_envp	*visit;

	visit = list;
	new = malloc(sizeof(t_envp));
	if (!new)
		return (1);//exit handler later
	while (visit->next)
		visit = visit->next;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
		return (1);//exit handler later
	new->next = NULL;
	visit->next = new;
	return (0);
}
