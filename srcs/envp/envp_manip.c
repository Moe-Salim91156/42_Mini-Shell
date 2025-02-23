/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/23 15:36:59 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
 linked list is used to allow manipulating envp, it does
 not know god.will need to rewrite a safer version later.*/
t_envp *init_envp(char **envp)
{
	t_envp *envp_list;
	t_envp *new;
	t_envp *last;
	int 	i;

	envp_list = NULL;
	i = -1;
	while (envp[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
			return (NULL); // exit handler later
		new->key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=')
		+ 1 - envp[i]);
		new->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		new->next = NULL;
		if (!new->key || !new->value)
			return (NULL); // exit handler later
		if (!envp_list)
			envp_list = new;
		else
			last->next = new;
		last = new;
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
/* appends a node to list. just pass it the str. */
int	append_env_node(t_envp *list, char *str)
{
	t_envp	*visit;
	t_envp	*new;

	new = build_env_node(str);
	visit = list;
	while (visit->next)
		visit = visit->next;
	visit->next = new;
	if (!visit->next)
	{
		ft_putstr_fd("Appending to env failed!\n",2);
		return (1);
	}
	return (0);
}

t_envp *build_env_node(char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!ft_strchr(str, '='))
	{
		new->key = ft_strjoin(str, "=");
		if (!new->key)
			return (NULL);
		new->value = ft_strdup("");
		if (!new->value)
		{
			ft_putstr_fd("failed allocating env value", 2);
			return (NULL);
		}
		return (new);
	}
	new->key = ft_substr(str, 0,
		ft_strchr(str, '=') + 1 - str );
	if (!new->key)
		return (NULL);
	new->value =ft_strchr(str, '=') + 1;
	return (new);
}
