/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:27:51 by msalim            #+#    #+#             */
/*   Updated: 2025/03/01 13:28:07 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_env_var(char *value, int *env_index)
{
	int		len;
	int		start;
	char	*look_up;

	len = 0;
	start = *env_index + 1;
	// take the index of the env_var
	while (value[start + len] != ' ')
		len++;
	look_up = malloc(len + 1);
	ft_strncpy(look_up, value + start, len);
	printf("value of env_Var to look %s\n", look_up);
	look_up = getenv(look_up);
	// identify the env_var
	// until you find a quote, seperator, anything
	// and then look for this env var in the env_variables;
	// if found return it
	// if not return (strdup(""));
	return (look_up);
}
