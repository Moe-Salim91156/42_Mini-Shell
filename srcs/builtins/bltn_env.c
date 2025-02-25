/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/25 19:08:54 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltn_env(t_shell *shell)
{
	t_envp	*visit;

	if (!shell->envp_list)
		return (1);
	visit = shell->envp_list;
	while (visit)
	{
		if (visit->key)
			if (printf("%s", visit->key) == -1)
				return (1);
		if (visit->value)
			if (printf("%s\n", visit->value) == -1)
				return (1);
		visit = visit->next;
	}
	return (0);
}
