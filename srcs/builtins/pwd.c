/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:39:22 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/15 17:48:02 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltn_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("getcwd failed");
		return (1);
	}
}
// int main(void)
// {
// 	bltn_pwd();
// }