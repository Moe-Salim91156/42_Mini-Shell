/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/17 17:15:22 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	what do we need with envp?
	1-init/building
	2-expanding(export)
	3-removing(unset)
	4-construct execve-compatible envp(2d array)
*/

// goes through the envp and creates a linked list of envp
// linked list is used to allow manipulating envp
t_envp	*init_envp(char **envp)
{
	t_envp *head;
	t_envp *traverse;
	int i;

	head = malloc(sizeof(t_envp));
	if (!head)
		return (NULL);//need exit handler.
	i = 0;
	traverse = head;
	while (envp[i])
	{
		traverse->content = ft_strdup(envp[i]);
		if (!traverse->content)
			return (NULL);//need exit handler.
		traverse->next = malloc(sizeof(t_envp));
		if (!traverse->next)
			return (NULL);//need exit handler.
		traverse = traverse->next;
		i++;
	}
	traverse->next = NULL;

}