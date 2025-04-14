/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/04/14 18:00:40 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "../../includes/minishell.h"
#define HEREDOC_FILE "/tmp/.heredoc_tmp"
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
			if (ft_strchr(current->value, '\''))
				payload->heredoc_quoted = 1;
			else if (ft_strchr(current->value, '\"'))
				payload->heredoc_quoted = 1;
		}
		current = current->next;
	}
	printf("qouted ? %d\n", payload->heredoc_quoted);
	return (payload->heredoc_quoted);
}

void	redirect_stdin_to_heredoc(const char *heredoc_filename,
		int *original_stdin)
{
	int	heredoc_fd;

	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin < 0)
	{
		perror("Error saving original stdin");
		return ;
	}
	heredoc_fd = open(heredoc_filename, O_RDONLY);
	if (heredoc_fd < 0)
	{
		perror("Error opening heredoc file");
		return ;
	}
	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("Error redirecting stdin");
		close(heredoc_fd);
		return ;
	}
	close(heredoc_fd);
}

void	restore_stdin(int original_stdin)
{
	if (dup2(original_stdin, STDIN_FILENO) < 0)
	{
		perror("Error restoring stdin");
		return ;
	}
	close(original_stdin);
}

void	run_heredoc(char *delimiter)
{
	int		heredoc_fd;
	char	*input;
	int		original_stdin;

	heredoc_fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
	{
		perror("heredoc file");
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
		write(heredoc_fd, input, ft_strlen(input));
		write(heredoc_fd, "\n", 1);
		free(input);
	}
	close(heredoc_fd);
	redirect_stdin_to_heredoc(HEREDOC_FILE, &original_stdin);
	heredoc_fd = open(HEREDOC_FILE, O_RDONLY);
	if (heredoc_fd < 0)
	{
		perror("heredoc file reopen");
		return ;
	}
  printf("%s\n",get_next_line(heredoc_fd));
	close(heredoc_fd);
	restore_stdin(original_stdin);
}

int	search_in_args(t_cmd *payload)
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
			run_heredoc(payload->heredoc_delimiter);
		}
		i++;
	}
	return (payload->has_heredoc);
}

int	locate_heredoc(t_cmd_list *cmd_list)
{
	t_cmd	*payload;

	payload = cmd_list->head;
	while (payload != NULL)
	{
		search_in_args(payload);
		payload = payload->next;
	}
	printf("total heredocs in all payloads %d\n", cmd_list->total_heredocs);
	return (0);
}

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
