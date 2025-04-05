/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_execbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:23:07 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/05 17:24:41 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

/*
 passed cmdname, executes it as a bltn (i.e without forking)
 treated as execve, only it doesnt overwrite parent process image
*/
int	bltn_execbe(char *cmdname, t_shell shell);
