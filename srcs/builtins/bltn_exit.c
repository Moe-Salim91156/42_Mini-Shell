/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 03:13:13 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/03 19:38:05 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	exit(unsigned long	status, t_shell shell):
	passed an argument, gracefully terminates shell.
	--> if no args, exit with last_status.
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
	a thought I had in mind: should  make exit prompt a
*/

