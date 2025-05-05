/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/05/05 22:33:34 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
#	 include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
extern volatile sig_atomic_t g_sig;
/*################# structs ############################*/
typedef enum e_token_type
{
	WORD,
	FILE_TOKEN,
	COMMAND,
	DQUOTE,
	SQUOTE,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ARGS,
	NLINE,
	HEREDOC,
	HEREDOC_DELIMITER,
	APPEND
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				heredoc_quoted;
	struct s_token	*next;
}					t_token;

typedef struct s_token_list
{
	int				size;
	t_token			*head;
}					t_token_list;

typedef struct s_double_quote_context
{
	int				start;
	int				len;
	int				env_index;
	char			*temp;
	char			*last_result;
	char			*expanded_result;
}					t_double_quote_context;

typedef struct s_normal_mode_context
{
	int				start;
	int				len;
	int				env_index;
	char			*temp;
	char			*new_expanded;
}					t_normal_mode_context;

typedef struct s_expand_env_context
{
	int				before;
	int				env_len;
	int				next_index;
	char			*before_str;
	char			*env_name;
	char			*env_value;
	char			*result;
	char			*final_result;
}					t_expand_env_context;

typedef struct s_cmd
{
	char			**payload_array;
	t_token_type	*type;
	char **argv; // execve compaitable array
	char			*cmd_path;
	int				heredoc_fd;
	// a way to communicate or call it when parsing redirection in;
	int				has_heredoc; // flag
	char			*heredoc_delimiter;
	int				heredoc_quoted; // for expansion or not
	int				here_doc_counts;
	int				exit_status;
	int				backup_in_fd;
	int				backup_out_fd;
	int				out_fd;
	int				in_fd;
	int				is_fork;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_list
{
	int				payload_count;
	int				count;
	int				total_heredocs;
	t_cmd			*head;
}					t_cmd_list;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_shell
{
	t_token_list	*token_list;
	t_cmd_list		*cmd_list;
	t_envp			*envp_list;
	int				last_status;
}					t_shell;

typedef struct s_pipes
{
	int				**pipes;
	int				pipe_index;
}				t_pipe;
/*################# init(🇬🇧) (and exit) #################*/
int					shell_init(t_shell *shell, char **envp);
t_token				*init_token(void);
t_cmd				*init_command(void);
t_token_list		*init_list(void);
t_cmd_list			*init_cmd_list(void);
t_envp				*init_envp(char **envp);
void				*free_env(t_envp *list);
void				free_command_list(t_cmd_list *cmd_list);
void				free_tokens(t_token_list *list);
// ft_exit is the ultimate exit handler. termination is always done through it.
void				ft_exit(t_shell *shell);
/*################## Signals #####################*/
void				setup_signals_main(void);
/*################# Tokenization #################*/
int					check_unexpected_token(t_shell *shell, t_token_list *list);
int					is_invalid_redirection(char *input, int i);
int					is_redirect_1(char *str);
void				substr_and_add(char *input, int start, int i,
						t_token_list *tokens);
void				lexer_cmd_list(t_cmd_list *list);
int				lexing(t_shell *shell, t_token_list *list);
char				**allocate_cmd_argv(int count);
int					is_seperator(int type);
int					is_seperator_token(char c);
int					is_quotes(char c);
int					is_redirect(char c);
void				add_last_token(char *input, int start, int i,
						t_token_list *tokens);
int					tokenizer(char *input, t_token_list *tokens, t_shell *shell);
t_cmd				*build_payloads(t_token_list *list, t_cmd_list *cmd_list);
void				skip_beginning_spaces(char *str);
int				lexemes(t_token *token);
void				add_token(t_token_list *list, char *value);
/*################# Expander ###########################*/
char				*append_mode_result(char *result, char *mode_result);
void				ozha_function(t_normal_mode_context *context,
						t_shell *shell);
void				gezha_function(t_double_quote_context *context,
						t_shell *shell);
int					has_env_var(char *value, t_token *current);
char				*expand_env_var(char *value, int *env_index,
						t_shell *shell);
int					check_for_quotes_in_tokens(t_token_list *list);
char				*expander_main(t_shell *shell);
// char				*handle_quotes_mode(t_token *current);
/*################# Enviroment #################*/
int					envp_count(t_envp *list);
int					mod_val(t_envp *node, char *new_value);
int					append_env_node(t_envp *list, char *str);
int					del_env_node(t_envp *node);
int					print_env_sorted(t_envp *list);
int					envp_count_all(t_envp *list);
char				**build_envp(t_shell *shell);
t_envp				*ft_getenv(t_envp *list, char *str);
t_envp				*find_by_key(t_envp *list, char *key);
t_envp				*find_str(t_envp *list, char *str);
t_envp				*build_env_node(char *str);
/*################# Built-ins #################*/
int					bltn_env(t_shell *shell);
int					bltn_pwd(void);
int					bltn_export(char **argv, t_envp *list);
int					bltn_unset(char **argv, t_envp **list);
int					bltn_cd(char **argv, t_envp *list);
int					bltn_echo(char **argv);
int					bltn_exit(char **argv, t_shell *shell);
/*################# Execution #################*/
int					execution_entry(t_shell *shell);
					/* HEREDOC HANDLING */
int					process_heredocs(t_cmd *cmd, t_shell *shell);
int					process_all_heredocs(t_shell *shell);
char				*expand_heredoc_line(char *line, char **envp);
void				cleanup_heredoc(t_cmd *cmd);
void				cleanup_all_heredocs(t_shell *shell);
					/*	BUILT-INS		*/
int					bltn_execbe(char **argv, t_shell *shell);
int					is_bltn(char **argv);
int					manage_bltn(t_shell *shell,t_cmd *current_paylaod);
					/*	FORK OPERATIONS	*/
void				manage_child(t_shell *shell, t_cmd *current_payload);
void				wait_for_children(t_shell *shell, int cmd_count, pid_t *pids);
void				fork_error(t_pipe *tpipe, int cmd_count, t_shell *shell);
					/*	REDIRECTIONS	*/
int					parse_redirs(t_cmd *current_paylaod,char **payload_array);
void				restore_io(t_cmd *current_payload);
void				restore_all_io(t_cmd *head);
int					redir_in(t_cmd *current_payload, char *file);
int					redir_out(t_cmd *current_payload, char *file);
int					redir_append(t_cmd *current_payload, char *file);
int					redir_heredoc(t_cmd *current_payload);
void				apply_redirs(t_cmd *current_payload);
int					see_heredoc_if_quoted(t_shell *shell);
char				*expand_heredoc_line(char *line, char **envp);
					/*	PIPELINE	*/
void				manage_pipeline(t_shell *shell, t_cmd *list_head, int cmd_count);
void				close_pipes(int **pipes, int cmd_count);
t_pipe				*lay_pipeline(int cmd_count, t_pipe *tpipe);
void				end_pipeline(t_shell *shell, int cmd_count , int *pids, t_pipe *pipe);
void				pipe_error(t_shell *shell, t_pipe *tpipe);
					/* EXIT STATUS		*/
int					set_exit_status(char *cmd_path);
void				child_perror(int status, char **env);
					/* PATH STUFF */
char				**build_cmd_argv(t_cmd_list *payload);
char				*search_command_in_path(char *cmd, char **envp,
						t_cmd *payload);
/*################# general utils #################*/
void				free_split(char **e);
void				print_command(t_cmd_list *cmd_list);
void				print_tokens(t_token_list *list);
void				debug_build_cmd_argv(t_cmd_list *list);
void				print_argv(t_cmd *payload);

/*################# signal  #################*/
void set_signal(int mode);
#endif
