/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:10:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/05 18:09:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	bltn_cd: changes working directory.
		takes @path as an str,passes it to
		chdir, catches any chdir errors.
		handles OLDPWD.
	#######
	return value:
	0 if directory changed successfuly, >0 otherwise.
	######
	TBD:
		properly handle no args
		properly handle too many args
		(will have to see how executer
		passes args first)
*/

/* args[2]--> !NULL == invalid arguments. */
static int invalid_args(char **args)
{
	if (args[2])
	{
		write(2,"cd: too many argumentrs\n",25);
		return (1);
	}
	return (0);
}

int	bltnc_cd(char **args, t_envp *list)
{
	char	oldpwd[1024];
	char	*path;

	if (!getcwd(oldpwd, 1024))
	{
		perror("cd: getcwd:");
		return (-1);
	}
	if (invalid_args(args))
		return (1);

}
