/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/04/22 23:18:22 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# ifndef HEREDOC_FILE
#  define HEREDOC_FILE "/tmp/.heredoc_tmp"
# endif


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

typedef struct s_cmd
{
	char			**payload_array;
	t_token_type	*type;
	char **argv; // execve compaitable array
	char			*cmd_path;
	char			*heredoc_buffer;
	int				heredoc_fd;
	// a way to communicate or call it when parsing redirection in;
	int has_heredoc; // flag
	char			*heredoc_delimiter;
	int heredoc_quoted; // for expansion or not
	int				here_doc_counts;
	int				exit_status;
	int				in_fd;
  int       backup_in_fd;
  int       backup_out_fd;
	int				out_fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_list
{
  int payload_count;
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
	int	last_status;
}					t_shell;

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
void				ft_exit(t_shell *shell, unsigned long status);
/*################# tokenization #################*/
void				lexer_cmd_list(t_cmd_list *list);
void				lexing(t_token_list *list);
char				**allocate_cmd_argv(int count);
int					is_seperator(int type);
int					is_seperator_token(char c);
int					is_quotes(char c);
int					is_redirect(char c);
void				add_last_token(char *input, int start, int i,
						t_token_list *tokens);
int					tokenizer(char *input, t_token_list *tokens);
t_cmd				*build_payloads(t_token_list *list, t_cmd_list *cmd_list);
void				skip_beginning_spaces(char *str);
void				lexemes(t_token *token);
void				add_token(t_token_list *list, char *value);
/*################# expander ###########################*/
int					check_for_quotes_in_tokens(t_token_list *list);
char				*expander_main(t_shell *shell);
//char				*handle_quotes_mode(t_token *current);
/*################# enviroment #################*/
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
/*################# built-ins #################*/
int					bltn_env(t_shell *shell);
int					bltn_pwd(void);
int					bltn_export(char **argv, t_envp *list);
int					bltn_unset(char **argv, t_envp **list);
int					bltn_cd(char **argv, t_envp *list);
int					bltn_echo(char **argv);
int					bltn_exit(char **argv, t_shell *shell);
/*################# execution #################*/
int					execution_entry(t_shell *shell);
					/*	BUILT-INS		*/
int					bltn_execbe(char **argv, t_shell *shell);
int					is_bltn(char **argv);
int					manage_bltn(t_shell *shell,t_cmd *current_paylaod,
	int pipe[], int paylod_loc);
					/*	FORK OPERATIONS	*/
int					manage_child(t_shell *shell, t_cmd *current_payload,
	int pipe[], int paylod_loc);
					/*	REDIRECTIONS	*/
int					parse_redirs(t_cmd *current_paylaod,char **payload_array);
void				restore_io(t_cmd *current_payload);
int					redir_in(t_cmd *current_payload, char *file);
int					redir_out(t_cmd *current_payload, char *file);
int					redir_append(t_cmd *current_payload, char *file);
int					redir_heredoc(t_cmd *current_payload, char *file);
void				apply_redirs(t_cmd *current_payload);
int					see_heredoc_if_quoted(t_shell *shell);
int					locate_heredoc(t_cmd *current_payload, t_shell *shell);
char				*expand_heredoc_line(char *line, char **envp);
					/* PATH STUFF		*/
char				**build_cmd_argv(t_cmd_list *payload);
char				*search_command_in_path(char *cmd, char **envp,
	t_cmd *payload);
					/* EXIT STATUS		*/
int					set_exit_status(char *cmd_path);
/*################# general utils #################*/
void				free_split(char **e);
void				print_command(t_cmd_list *cmd_list);
void				print_tokens(t_token_list *list);
void				debug_build_cmd_argv(t_cmd_list *list);
void				print_argv(t_cmd *payload);
#endif
