/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/23 15:22:54 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bltn_env(t_shell *shell)
{
	t_envp *visit;

	visit = shell->envp_list;
	while (visit)
	{
		printf("%s%s\n", visit->key, visit->value);
		visit = visit->next;
	}
}
