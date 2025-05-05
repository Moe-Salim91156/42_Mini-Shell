/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/04 17:37:06 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	what do we need with envp?
	1-init (to have a list to manipulate as we wish)
	2-adding(export)
	3-removing(unset)
	4-easy key value lookup(expandning)
	5-construct execve-compatible envp(2d array)
	6- handle shlvl
	----------------------------------------------
*/

/*
	creates a linked list of key/values of envp.
	very helpful to manipulate it as we wish.
	returns NULL on failure.
*/
t_envp	*init_envp(char **envp)
{
	int		i;
	t_envp	*list;

	if (!envp || !envp[0])
	{
		list = build_env_node("foolmeonce=shameonyou");
		return (list);
	}
	list = NULL;
	i = 1;
	list = build_env_node(envp[0]);
	if (!list)
		return (list);
	while (envp[i])
	{
		if (append_env_node(list, envp[i]))
			return (free_env(list));
		i++;
	}
	return (list);
}

/*
	returns an execve compatible 2d array of envp
	i.e key=value
*/
char	**build_envp(t_shell *shell)
{
	t_envp	*traverse;
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (envp_count_all(shell->envp_list) + 1));
	if (!envp)
		return (NULL);
	traverse = shell->envp_list;
	while (traverse)
	{
		if (traverse->value)
			envp[i] = ft_strjoin(traverse->key, traverse->value);
		else
			envp[i] = ft_strdup(traverse->key);
		if (!envp[i])
			return (NULL);//exit handler
		traverse = traverse->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
/*
	frees the env list. should always be called at
	failure/exit to ensure gracefull termination.
 */
void	*free_env(t_envp *list)
{
	t_envp	*visit;
	t_envp	*next;

	visit = list;
	if (!visit)
		return (NULL);
	while (visit)
	{
		next = visit->next;
		if (visit)
			del_env_node(visit);
		visit = next;
	}
	return (NULL);
}

/*
	appends a node to list. just pass it the str.
	pretty much a wrapper for build_env_node.
*/
int	append_env_node(t_envp *list, char *str)
{
	t_envp	*visit;
	t_envp	*new;

	if (!list)
	{
		list = build_env_node(str);
		if (!list)
			return (1);
		return (0);
	}
	new = build_env_node(str);
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
	extracts key and value from @str, returns a new node containing them.
	it works on the assumption that no existing node with matching key
	already exists. this function should only be called when you want
	to construct and then append a new node.
	(atheist funcion)
	---------------------------------
	its actually pretty good now, I just found the original comment too
	funny and should serve as a warning to why you dont nest 13 conditions
	inside each other.
*/
t_envp	*build_env_node(char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->key = ft_substr(str, 0, ft_strchr(str, '=') + 1 - str);
	new->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!new->key || !new->value)
		return (NULL);
	return (new);
}
