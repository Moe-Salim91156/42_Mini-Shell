/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/15 10:48:05 by yokitane         ###   ########.fr       */
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
		if (ret == -1)
			break;
		i++;
	}
	return (ret);
}

int	redir_in(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	shell->
}
