/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/18 00:06:32 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	what do we need with envp?
	1-init
	2-adding(export)
	3-removing(unset)
	4-quick look up key(expandning)
	5-construct execve-compatible envp(2d array)
	----------------------------------------------
*/

/*goes through the envp and creates a linked list of envp
 linked list is used to allow manipulating envp*/
t_envp	*init_envp(char **envp)
{
	t_envp *head;
	t_envp *traverse;
	int i;

	i = 0;
	head = malloc(sizeof(t_envp));
	if (!head)
		return (NULL);//replace with  exit_handler.
	traverse = head;
	while (envp[i])
	{
		traverse->value = ft_strdup(envp[i]);
		if (!traverse->value)
			return (NULL);//replace with  exit_handler.
		if (envp[i + 1])
		{
			traverse->next = malloc(sizeof(t_envp));
			if (!traverse->next)
				return (NULL);//replace with  exit_handler.
			traverse = traverse->next;
		}
		i++;
	}
	traverse->next = NULL;
	return (head);
}

char **build_envp(t_shell *shell)
{
	t_envp *traverse;
	char **envp;
	int i;

	i = 0;
	traverse = shell->envp_list;
	envp = malloc(sizeof(char *) * (envp_count(shell->envp_list) + 1));
	if (!envp)
		return (NULL);//replace with  exit_handler.
	while (traverse)
	{
		envp[i] = ft_strdup(traverse->value);
		if (!envp[i])
			return (NULL);//replace with  exit_handler.
		traverse = traverse->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	envp_add(t_envp **envp, char *value)
{
	t_envp *new;
	t_envp *traverse;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (1);//replace with  exit_handler.
	new->value = ft_strdup(value);
	if (!new->value)
		return (1);//replace with  exit_handler.
	new->next = NULL;
	if (!*envp)
	{
		*envp = new;
		return (0);
	}
	traverse = *envp;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new;
	return (0);
}

int	envp_remove(t_envp **envp, char *key)
{
	t_envp *traverse;
	t_envp *prev;

	traverse = *envp;
	prev = NULL;
	while (traverse)
	{
		if (!ft_strncmp(traverse->value, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = traverse->next;
			else
				*envp = traverse->next;
			free(traverse->value);
			free(traverse);
			return (0);
		}
		prev = traverse;
		traverse = traverse->next;
	}
	return (1);
}
