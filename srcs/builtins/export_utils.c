/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:28:35 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/26 10:43:32 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	in this file should be:
	1- an exit handler.
	2- print_env_sorted.
	tbd
*/
int	export_err(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	return (1);
}
