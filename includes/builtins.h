/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
