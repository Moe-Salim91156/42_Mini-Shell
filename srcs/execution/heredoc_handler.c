/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:15:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/28 23:44:19 by yokitane         ###   ########.fr       */
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
static int	run_heredoc_child(char *delimiter, int heredoc_quoted, char **envp)
{
	int		pipe_fds[2];
	pid_t	pid;
	char	*input;
	int		status;

	if (pipe(pipe_fds) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fds[0]);
		while (1)
		{
			input = readline("> ");
			if (!input || !ft_strcmp(input, delimiter))
			{
				free(input);
				/* Make sure to close pipe before exit */
				close(pipe_fds[1]);
				exit(EXIT_SUCCESS);
			}
			if (!heredoc_quoted)
				input = expand_heredoc_line(input, envp);
			/* Check write errors to prevent SIGPIPE */
			if (write(pipe_fds[1], input, ft_strlen(input)) < 0 ||
				write(pipe_fds[1], "\n", 1) < 0)
			{
				free(input);
				close(pipe_fds[1]);
				exit(EXIT_FAILURE);
			}
			free(input);
		}
	}
	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		close(pipe_fds[0]);
		return (-1);
	}
	return (pipe_fds[0]);
}

/*
** Searches for heredoc delimiters in command arguments and processes them
** Returns -1 on error, or the number of heredocs processed
*/
int	process_heredocs(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		heredoc_fd;
	int		heredoc_count;
	char	**envp;

	heredoc_count = 0;
	envp = build_envp(shell);
	if (!envp)
		return (-1);
	i = 0;
	while (cmd->payload_array[i])
	{
		if (!ft_strcmp(cmd->payload_array[i], "<<"))
		{
			cmd->has_heredoc = 1;
			cmd->heredoc_delimiter = ft_strdup(cmd->payload_array[i + 1]);
			heredoc_fd = run_heredoc_child(cmd->heredoc_delimiter,
					cmd->heredoc_quoted, envp);
			if (heredoc_fd < 0)
			{
				free_split(envp);
				return (-1);
			}
			cmd->heredoc_fd = heredoc_fd;
			heredoc_count++;
		}
		i++;
	}
	free_split(envp);
	return (heredoc_count);
}

/*
** Process all heredocs in all commands in the pipeline
** This should be called before any command execution
*/
int	process_all_heredocs(t_shell *shell)
{
	t_cmd	*current;
	int		total_heredocs;
	int		result;

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

/*
** Cleans up heredoc resources for a command
** Closes any open heredoc file descriptors
*/
void	cleanup_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_fd > 0)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (cmd->heredoc_delimiter)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
	}
	cmd->has_heredoc = 0;
}

/*
** Cleans up all heredoc resources for all commands in the shell
*/
void	cleanup_all_heredocs(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd_list->head;
	while (current)
	{
		cleanup_heredoc(current);
		current = current->next;
	}
}
