/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/03 19:43:49 by yokitane         ###   ########.fr       */
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
		if (visit->key && visit->value)
			if (printf("%s%s\n", visit->key, visit->value) == -1)
				return (1);
		visit = visit->next;
	}
	return (0);
}
