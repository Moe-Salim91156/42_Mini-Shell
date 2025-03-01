/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:27:19 by msalim            #+#    #+#             */
/*   Updated: 2025/03/01 13:27:33 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"


char	*double_quote_mode(char *value, int *index)
{
	int		start;
  int   env_index;
	int		len;
	char	*temp;
	char	*expanded_value;

	start = *index + 1;
	len = 0;
	while (value[start + len] && value[start + len] != '\"')
		len++;
	temp = malloc(len + 1);
	ft_strncpy(temp, value + start, len);
	temp[len] = '\0';
  env_index = has_env_var(temp);
	if (env_index != -1)
	{
		expanded_value = expand_env_var(temp, &env_index);
		return (expanded_value);
	}
	else
	{
		*index = start + len + 1;
		return (temp);
	}
}


