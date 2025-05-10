/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:15:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/07 14:03:49 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Creates a pipe for heredoc and returns the read end of the pipe
** The child process fills the pipe with the heredoc content
** The parent process waits for the child to complete and returns the read fd
--this whole FILE is entierly vibe coded--
	needs a proper refactor.
*/
void	heredoc_read_loop(t_cmd *p, char **envp, int write_fd)
{
	char	*in;

	while (1)
	{
		in = readline("> ");
		if (!in || !ft_strcmp(in, p->heredoc_delimiter))
		{
			free(in);
			break ;
		}
		if (!p->heredoc_quoted)
			in = expand_heredoc_line(in, envp);
		write(write_fd, in, ft_strlen(in));
		write(write_fd, "\n", 1);
		free(in);
	}
}

void	process_heredoc_helper(t_cmd *cmd, t_shell *shell, int *i, char **envp)
{
	cmd->has_heredoc = 1;
	if (cmd->payload_array[*i + 1] && cmd->type[*i + 1] == HEREDOC_DELIMITER)
		cmd->heredoc_delimiter = ft_strdup(cmd->payload_array[*i + 1]);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = run_heredoc(cmd, shell, envp);
}

static int	handle_heredoc(t_cmd *cmd, t_shell *shell, int *i, char **envp)
{
	process_heredoc_helper(cmd, shell, i, envp);
	if (cmd->heredoc_fd < 0)
	{
		free_split(envp);
		return (-1);
	}
	return (0);
}

int	process_heredocs(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		heredoc_count;
	char	**envp;

	envp = build_envp(shell);
	if (!envp)
		return (-1);
	heredoc_count = 0;
	i = 0;
	while (cmd->payload_array[i])
	{
		if (!ft_strcmp(cmd->payload_array[i], "<<"))
		{
			if (handle_heredoc(cmd, shell, &i, envp) < 0)
				return (-1);
			heredoc_count++;
			i += 2;
		}
		else
			i++;
	}
	free_split(envp);
	return (heredoc_count);
}

int	process_all_heredocs(t_shell *shell)
{
	t_cmd	*current;
	int		total_heredocs;
	int		result;

	see_heredoc_if_quoted(shell);
	total_heredocs = 0;
	current = shell->cmd_list->head;
	while (current)
	{
		result = process_heredocs(current, shell);
		if (result < 0)
			return (-1);
		total_heredocs += result;
		current = current->next;
	}
	return (total_heredocs);
}
