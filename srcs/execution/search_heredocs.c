/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/05/01 16:35:44 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
 * lookup payloads array of args for (<<)
 * if found execute the heredoc function
 *  ::: heredoc function:
 *      1. iterate through each payload args;
 *      2. look for (<<) for heredoc;
 *      3. fill the buffer for heredoc for each payload,
	to be read by anything afterwards;
 *      4. thats it;
 *
 * */
int	create_unique_heredoc_file(char *out_path, size_t size)
{
	static int	index = 0;
	char		path[256];
	int			fd;

	while (1)
	{
		snprintf(path, sizeof(path), "/tmp/.heredoc_tmp_%d", index++);
		fd = open(path, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
		{
			if (out_path)
				strncpy(out_path, path, size - 1);
			return (fd);
		}
		if (errno != EEXIST)
			break ;
	}
	return (-1);
}

void	run_single_heredoc(t_cmd *payload, char *delimiter, char **envp)
{
	char	*input;
	char	filename[256];

	payload->heredoc_fd = create_unique_heredoc_file(filename, sizeof(filename));
	if (payload->heredoc_fd < 0)
	{
		perror("heredoc file creation failed");
		return ;
	}
	payload->heredoc_filename = ft_strdup(filename);

	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		if (!payload->heredoc_quoted)
			input = expand_heredoc_line(input, envp);
		write(payload->heredoc_fd, input, ft_strlen(input));
		write(payload->heredoc_fd, "\n", 1);
		free(input);
	}
	close(payload->heredoc_fd);
	payload->heredoc_fd = open(payload->heredoc_filename, O_RDONLY);
	unlink(payload->heredoc_filename);
}

int	process_all_heredocs(t_shell *shell)
{
	t_cmd	*payload = shell->cmd_list->head;
	t_token	*current = shell->token_list->head;
	char	**envp = build_envp(shell);

	while (payload && current)
	{
		while (current && current->type != HEREDOC_DELIMITER)
			current = current->next;
		if (!current)
			break ;
		payload->has_heredoc = 1;
		payload->heredoc_quoted = current->heredoc_quoted;
		payload->heredoc_delimiter = ft_strdup(current->value);

		run_single_heredoc(payload, payload->heredoc_delimiter, envp);

		if (payload->heredoc_fd < 0)
		{
			free(envp);
			return (-1);
		}
		payload = payload->next;
		current = current->next;
	}
	free(envp);
	return (0);
}
/*
int	see_heredoc_if_quoted(t_shell *shell)
{
	t_token	*current;
	t_cmd	*payload;

	current = shell->token_list->head;
	payload = shell->cmd_list->head;
	while (current)
	{
		if (current->type == HEREDOC_DELIMITER)
		{
			payload->heredoc_quoted = current->heredoc_quoted;
		}
		current = current->next;
	}
	return (payload->heredoc_quoted);
}

void	run_heredoc(t_cmd *payload, char *delimiter, char **envp)
{
	char	*input;

	payload->heredoc_fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (payload->heredoc_fd < 0)
	{
		perror("heredoc file open error");
		return ;
	}
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		if (!payload->heredoc_quoted)
			input = expand_heredoc_line(input, envp);
		write(payload->heredoc_fd, input, ft_strlen(input));
		write(payload->heredoc_fd, "\n", 1);
		free(input);
	}
	close(payload->heredoc_fd);
}

int	search_in_args(t_cmd *payload, char **envp)
{
	int	i;

	i = 0;
	while (payload->payload_array[i])
	{
		if (!ft_strcmp(payload->payload_array[i], "<<"))
		{
			payload->has_heredoc = 1;
			payload->heredoc_delimiter = ft_strdup(payload->payload_array[i
					+ 1]);
			run_heredoc(payload, payload->heredoc_delimiter, envp);
			if (payload->heredoc_fd < 0)
			{
        return (-1);
			}
		}
		i++;
	}
	return (payload->has_heredoc);
}

int	locate_heredoc(t_cmd *payload, t_shell *shell)
{
	char	**envp;

	envp = build_envp(shell);
	if (search_in_args(payload, envp) == -1)
	{
		free(envp);
		return (-1); // error if we wanna return or exit handler
	}
	free(envp);
	return (payload->has_heredoc); // will be 0 or 1 for heredoc detection;
}
*/
/*
 * filling the heredoc in each payload last one wins
 * if has quotes, no expansion inside and quotes removed from delimiter
 * if no quotes	, expanding content but not the delimiter
 * see_if_heredoc_quoted will be executed before expander, good fix
 * a flag (quoted) will determine if we will expand content or nah
 * locate, fill, expand?, get executed if command
 *
 *
 *
 */
