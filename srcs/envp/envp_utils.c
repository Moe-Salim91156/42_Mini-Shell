/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:38:32 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/18 00:14:14 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	envp_count(t_envp *envp)
{
	int		count;
	t_envp	*traverse;

	count = 0;
	traverse = envp;
	while (traverse)
	{
		count++;
		traverse = traverse->next;
	}
	return (count);
}
/*allows quick lookup of variables.*/
char	*get_envp_value(t_envp *envp, char *key)
{
	t_envp *traverse;

	traverse = envp;
	while (traverse)
	{
		if (ft_strncmp(traverse->value, key, ft_strlen(key)) == 0)
			return (ft_strchr(traverse->value, '=') + 1);
		traverse = traverse->next;
	}
	return (NULL);
}
