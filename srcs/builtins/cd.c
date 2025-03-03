/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:10:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/04 02:57:55 by yokitane         ###   ########.fr       */
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
		handle too many arguments.
*/

int	bltnc_cd(char *path, t_envp *list)
{
	char oldpwd[1024];

	if (chdir(path) == -1)
	{
		perror("cd: ");
		return (1);
	}
	if (!getcwd(oldpwd, 1024))
	{
		perror("cd: getcwd:");
		return (-1);
	}
	if(mod_val(find_by_key(list, "OLDPWD="), oldpwd))
	{
		perror ("cd: mod_val: ");
		return (-1);
	}
	return (0);
}
