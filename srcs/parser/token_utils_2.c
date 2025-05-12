/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:23:31 by msalim            #+#    #+#             */
/*   Updated: 2025/05/12 13:20:37 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	substr_and_add(char *input, int start, int i, t_token_list *tokens)
{
	char	*result;

	if (i > start)
	{
		result = ft_substr(input, start, i - start);//null check
		add_token(tokens, result);
		free(result);
	}
}

int	is_invalid_redirection(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

void	skip_beginning_spaces(char *str)
{
	while (*str == ' ')
		str++;
}
