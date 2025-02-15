/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:25:05 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/15 17:02:01 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltn_pwd(void);
int	bltn_cd(char *dst);
int	bltn_echo(char **args);
int	bltn_export(char **args);
int	bltn_unset(char **args);
int	bltn_env(void);
int bltn_exit(int status);
