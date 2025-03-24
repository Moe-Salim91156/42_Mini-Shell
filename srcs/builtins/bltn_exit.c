/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/builtins/bltn_exit.c
/*   Created: 2025/03/04 03:13:13 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/05 16:33:13 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	exit:
		need to have an exit handler
		and an exit status collecter.
*/
========
/*   Created: 2025/02/15 16:25:05 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/16 17:33:44 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	bltn_pwd(void);
int	bltn_cd(char *dst);
int	bltn_echo(char **args);
int	bltn_export(char **args);
int	bltn_unset(char **args);
int	bltn_env(void);
int	bltn_exit(int status);
#endif
>>>>>>>> 34478fe743ccd63e686e70361c3027f5a308a221:includes/builtins.h
