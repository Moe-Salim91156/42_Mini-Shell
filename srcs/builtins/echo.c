/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:30:18 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/06 06:39:04 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	echo:
		prints out what you give it.
		########
		behaviour:
		1-basic input parsing
			--> move through args, until you reach null or printable
				--> if you see a '-'
					-->validate option(purely preceeded by 'n')
			--> as soon as you reach a printable arg, exit parsing and start
				printing.
		2-print remaining args
		########
		return value:
		so far seems to always return 0
*/

static int is_flag(char *str)
{
	int	i;

	i = 1;
	if (*str == '-')
	{
		while(str[i] == 'n' || str[i] == 'e' || str[i] == 'E')// need to decide if we want
			i++;											// to handle the E and e
		if (!str[i])
			return (1);
	}
	return (0);
}

int	bltn_echo(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (!args[i])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (args[i] && (is_flag(args[i])))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (!n_flag)
		write(1,"\n",1);
	return (0);
}
