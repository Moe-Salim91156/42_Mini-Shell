/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/04/16 14:26:57 by msalim           ###   ########.fr       */
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
      input = expand_heredoc_line(input,envp);
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
			run_heredoc(payload, payload->heredoc_delimiter,envp);
			if (payload->heredoc_fd < 0)
			{
				// error
				// exit;
				// or return (-1 for error);
				// 0 if no heredoc and 1 if there is heredoc
			}
		}
		i++;
	}
	return (payload->has_heredoc);
}

int	locate_heredoc(t_cmd_list *cmd_list, t_shell *shell)
{
	t_cmd	*payload;
  char **envp = build_envp(shell);
	payload = cmd_list->head;

	if (search_in_args(payload, envp) == -1)
		return (-1); // error if we wanna return or exit handler
	printf("payload has heredoc ? %d\n", payload->has_heredoc);
	printf("payload heredoc file fd %d\n", payload->heredoc_fd);
	printf("payload heredoc delim is quoted ? %d\n", payload->heredoc_quoted);
	return (payload->has_heredoc); // will be 0 or 1 for heredoc detection;
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
