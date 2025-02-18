/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:59 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/18 19:28:37 by yokitane         ###   ########.fr       */
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

*/