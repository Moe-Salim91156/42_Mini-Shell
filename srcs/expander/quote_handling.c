/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/26 14:05:30 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_single_quote_token(char *token)
{
	if (ft_strchr(token, '\''))
		return (1);
	else
		return (0);
}

char	*extract_single_quotes(char *value, char quote)
{
}
