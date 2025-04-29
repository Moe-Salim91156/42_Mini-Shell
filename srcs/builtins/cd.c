/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:10:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/21 19:18:10 by yokitane         ###   ########.fr       */
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
*/

/*
	argv[2]--> !NULL == invalid arguments.
*/
static int	invalid_argv(char **argv)
{
	if (argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

/*
	if OLDPWD doesnt exist, create it.
	update OLDPWD.
*/
static int	update_oldpwd(t_envp *list, char *oldpwd)
{
	if (!ft_getenv(list, "OLDPWD"))
	{
		if (append_env_node(list, "OLDPWD="))
			return (1);
	}
	if (mod_val(ft_getenv(list, "OLDPWD"), oldpwd))
		return (1);
	return (0);
}

/* no argv cd handler */
static int	take_me_home(t_envp *list, char *oldpwd)
{
	if (!ft_getenv(list, "HOME"))
	{
		ft_putstr_fd("cd: HOME not set", 2);
		return (1);
	}
	if (update_oldpwd(list, oldpwd))
		return (1);
	if (chdir(ft_getenv(list, "HOME")->value) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(ft_getenv(list, "HOME")->value);
		return (1);
	}
	return (0);
}

int	bltn_cd(char **argv, t_envp *list)
{
	char	oldpwd[1024];

	if (!getcwd(oldpwd, 1024))
	{
		perror("cd: getcwd:");
		return (-1);
	}
	if (!argv[1])
		return (take_me_home(list, oldpwd));
	if (invalid_argv(argv))
		return (1);
	if (update_oldpwd(list, oldpwd))
		return (1);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(argv[1]);
		return (1);
	}
	return (0);
}
/*
int	main(void)
{
	t_envp *list = init_envp(__environ);
	char *argv1[]= {"cd","..",NULL};
	char *argv2[]= {"cd","",NULL};
	char *argv3[]= {"cd",find_by_key(list, "OLDPWD")->value,NULL};
	bltn_pwd();
	bltn_cd(argv1, list);
	bltn_pwd();
	bltn_cd(argv1, list);
	bltn_pwd();
	bltn_cd(argv1, list);
	bltn_pwd();
} */