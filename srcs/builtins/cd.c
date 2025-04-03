/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:10:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/24 10:44:36 by yokitane         ###   ########.fr       */
/*   Updated: 2025/03/06 04:26:26 by yokitane         ###   ########.fr       */
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
	args[2]--> !NULL == invalid arguments.
*/
static int invalid_args(char **args)
{
	if (args[2])
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
static int update_oldpwd(t_envp *list, char *oldpwd)
{
	if (!ft_getenv(list, "OLDPWD"))
	{
		if(append_env_node(list, "OLDPWD="))
			return (1);
	}
	if(mod_val(ft_getenv(list, "OLDPWD"), oldpwd))
		return(1);
	return (0);
}

/* no args cd handler */
static int take_me_home(t_envp *list, char *oldpwd)
{
	if (!ft_getenv(list,"HOME"))
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
		ft_putstr_fd(": ", 2);
		return (1);
	}
	return (0);
}

int	bltn_cd(char **args, t_envp *list)
{
	char	oldpwd[1024];

	if (!getcwd(oldpwd, 1024))
	{
		perror("cd: getcwd:");
		return (-1);
	}
	if (!args[1])
		return (take_me_home(list, oldpwd));
	if (invalid_args(args))
		return (1);
	if (update_oldpwd(list, oldpwd))
		return (1);
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(args[1]);
		ft_putstr_fd(": ", 2);
		return (1);
	}
	return (0);
}
/*
int main(void)
{
	t_envp *list = init_envp(__environ);
	char *args1[]= {"cd","..",NULL};
	char *args2[]= {"cd","",NULL};
	char *args3[]= {"cd",find_by_key(list, "OLDPWD")->value,NULL};
	bltn_pwd();
	bltn_cd(args1, list);
	bltn_pwd();
	bltn_cd(args1, list);
	bltn_pwd();
	bltn_cd(args1, list);
	bltn_pwd();
} */