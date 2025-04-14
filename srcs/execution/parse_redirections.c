/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/14 20:58:23 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	parse_redirs(t_shell *shell,char **payload)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while(payload[i])
	{
		if (ft_strcmp("<", payload[i]))
			ret = redir_in(shell,payload[++i]);
		if (ft_strcmp(">", payload[i]))
			ret = redir_out(shell,payload[++i]);
		if (ft_strcmp(">>", payload[i]))
			ret = redir_append(shell,payload[++i]);
		if (ft_strncmp("<<", payload[i], 2))
		{
			ret = redir_heredoc(shell, HEREDOC_PATH);
			i+=2;
		}
		if (ret)
			break;
		i++;
	}
	return (ret);
}
