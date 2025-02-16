/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/15 18:12:08 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			write(1, &envp[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	bltn_env(void)
{
	char	**envp;

	envp = __environ;
	print_env(envp);
}

// int	main(void)
// {
// 	bltn_env();
// 	return (0);
// }
