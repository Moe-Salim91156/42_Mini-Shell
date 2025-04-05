/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 03:13:13 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/05 17:22:30 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



static int is_numeric(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static unsigned long ft_atoul(char *str)
{
	unsigned long ret;

	ret = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

/*
	exit(unsigned long	status, t_shell shell):
	passed an argument, gracefully terminates shell.
	--> if no argv, exit with last_status.
	--> else ensure 1 arg and numeric.
		--> if non numeric, exit with status = 2.
	--> if numeric
		--> ensure argc == 1.
		--> else dont exit, return 1.
	else, exit with (@status%256) status.
	###
	it should be noted that bash always collects the exit status
	of the most recently executed command, and if at anypoint
	------
	tbd: an exit handler to free heap and close open fds.
	-----
	notes: as in with every builtin(I prolly forgot
	to implement it this way in many of them)
	-->argv[0] == exit
	the argv[0] is the name of the command, to conform to execve behaviour.
*/

int	bltn_exit(char **argv, t_shell *shell)
{
	if (argv[1] && argv[2])
		return (1);
	if (!argv[1])
}
