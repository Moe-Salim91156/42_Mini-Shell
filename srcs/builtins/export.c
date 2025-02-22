/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/22 18:35:17 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 	export: takes arguments, then stores values in keys.
	things to handle:
	1- no arguments: print all envp
	2- arguments: store them in envp
		A- if key is invalid, print error.
		B- if key exists, update value
		C- if key doesn't exist, append new node.
	-------------------------------------
	cases:
	key only (no '=' or empty value)
		--> assign key=""
	invalid key (begining with anything other than alpha/'_')
		--> dont assign key, skip arg

*/

static int build_node(char *str)
{
	//construct t_envp node
}

static int validate_node(t_envp *node);

static int add_node(t_envp *envp_list, t_envp *node);

int	bltn_export(char **args, t_shell *shell)
{
	int		i;

	if (!args[1])
	{
		bltn_env(shell);
		return (0);
	}
	i = 0;
	while (args[i])
	{
		//construct t_envp node
		// check validty of node ()
		//add to envp_list
			// append if applicable
			//else replace key.
	}
}
