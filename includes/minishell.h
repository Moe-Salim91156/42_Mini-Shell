/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/02/22 14:04:03 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define COLOR_MAGENTA "\033[1;37m"
# define COLOR_RESET "\033[0m"
/*################# structs ############################*/
typedef enum e_token_type
{
	WORD,
	COMMAND,
	DQUOTE,
	SQUOTE,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ARGS,
	NLINE,
	HEREDOC,
	APPEND
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_token_list
{
	int				size;
	t_token			*head;
}					t_token_list;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_list
{
	int				count;
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
}					t_shell;

/*################ General functions #######################*/
int					shell_init(t_shell *shell, char **envp);
/*################# tokenizing/build_cmd #########################*/
void				lexing(t_token_list *list);
char				**allocate_cmd_args(int count);
int					is_seperator(int type);
int					is_seperator_token(char c);
int					is_quotes(char c);
int					is_redirect(char c);
void				add_last_token(char *input, int start, int i,
						t_token_list *tokens);
void				tokenizer(char *input, t_token_list *tokens);
t_cmd_list			*init_cmd_list(void);
t_cmd				*build_cmd(t_token_list *list, t_cmd_list *cmd_list);
void				skip_beginning_spaces(char *str);
void				lexemes(t_token *token);
t_token				*init_token(void);
t_cmd				*init_command(void);
t_token_list		*init_list(void);
void				add_token(t_token_list *list, char *value);
void				print_command(t_cmd_list *cmd_list);
void				print_tokens(t_token_list *list);
/*################# enviroment handling ################*/
int					envp_count(t_envp *list);
int					remove_envp_node(t_envp *list, t_envp *remove);
int					modify_value(t_envp *node, char *new_value);
int					append_envp_node(t_envp *list, char *key, char *value);
int					free_envp_list(t_envp *list);
t_envp				*init_envp(char **envp);
t_envp				*find_by_key(t_envp *list, char *key);
char				**build_envp(t_shell *shell);
/*################# builtins ###########################*/
int					bltn_pwd(void);
void				bltn_env(t_shell *shell);
int					bltn_export(char **args, t_shell *shell);
int					bltn_cd(char *dst);
int					bltn_echo(char **args);
int					bltn_unset(char **args);
int					bltn_exit(int status);
#endif
