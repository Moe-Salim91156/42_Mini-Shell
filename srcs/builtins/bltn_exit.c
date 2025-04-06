/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 03:13:13 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/05 19:14:56 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns boolean convention value(1--> true, 0 -->false)
static int	is_numeric(const char *str)
{
	int	len;

	len = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) || len > 18)
			return (0);
		str++;
		len++;
	}
	return (1);
}

static unsigned long	ft_atoul(char *str)
{
	unsigned long	ret;

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
	--> else ensure @argv[1] numeric.
		--> if non numeric, exit with status = 2.
	--> if numeric
		--> ensure argc == 1.
		--> else dont exit, return 1.
	else, exit with (@status%256) status.
	###
	max num length to count as numeric: 19 digits
	------
	tbd: an exit handler to free heap and close open fds.
	-----
	note: as in with every builtin(I prolly forgot
	to implement it this way in many of them)
	-->argv[0] == exit
	the argv[0] is the name of the command, to conform to execve behaviour.
*/

int	bltn_exit(char **argv, t_shell *shell)
{
	if (!argv[1])
		ft_exit(shell, shell->last_status);
	if (!is_numeric(argv[1]))
	{
		ft_putendl_fd("rbsh: exit: numeric argument required.", 2);
		ft_exit(shell, 2);
	}
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("rbsh: exit: too many arguments.", 2);
		return (1);
	}
	ft_exit(shell, ft_atoul(argv[1]) % 256);
	return (1);
}
