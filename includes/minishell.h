/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/02/26 17:49:11 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

/*################# structs ############################*/

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ARGS
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_token_list
{
	int		size;
	t_token	*head;
}					t_token_list;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_list
{
	int		count;
	t_cmd	*head;
}					t_cmd_list;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_shell
{
	t_token_list	*token_list;
	t_cmd_list		*cmd_list;
	t_envp			*envp_list;
}					t_shell;

/*################# init(🇬🇧) #################*/
int				shell_init(t_shell *shell, char **envp);
/*################# tokenization #################*/
t_cmd			*build_cmd(t_token_list *list, t_cmd_list *cmd_list);
t_cmd			*init_command(void);
t_cmd_list		*init_cmd_list(void);
t_token			*init_token(void);
t_token_list	*init_list(void);
void			print_tokens(t_token_list *list);
void			print_command(t_cmd_list *cmd_list);
void			lexemes(t_token *token);
void			skip_beginning_spaces(char *str);
void			add_token(t_token_list *list, char *value);
void			tokenize(char *str, t_token_list *token);
/*################# enviroment #################*/
int				envp_count(t_envp *list);
int				mod_val(t_envp *node, char *new_value);
int				append_env_node(t_envp *list, char *str);
int				del_env_node(t_envp	*node);
int				print_env_sorted(t_envp *list);
char			**build_envp(t_shell *shell);
t_envp			*init_envp(char **envp);
t_envp			*find_by_key(t_envp *list, char *key);
t_envp			*find_str(t_envp *list,char *str);
t_envp			*build_env_node(char *str);
void			*free_env(t_envp *list);
/*################# built-ins #################*/
int				bltn_env(t_shell *shell);
int				bltn_export(char **args,t_envp *list);
int				bltn_pwd(void);
int				bltn_cd(char *dst);
int				bltn_echo(char **args);
int				bltn_unset(char **args);
int 			bltn_exit(int status);
/*################# general utils #################*/
void			*free_str_arr(char **argv);
#endif
