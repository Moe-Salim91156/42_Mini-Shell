/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/02/18 00:14:03 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "envp.h"
# include "builtins.h"
# include <unistd.h>
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
	char	*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_shell
{
	t_token_list	*token_list;
	t_cmd_list		*cmd_list;
	t_envp			*envp_list;
}					t_shell;

/*################# tokenizing #################*/
void				print_tokens(t_token_list *list);
void				print_command(t_cmd_list *cmd_list);
t_cmd_list			*init_cmd_list(void);
t_cmd				*build_cmd(t_token_list *list, t_cmd_list *cmd_list);
void				skip_beginning_spaces(char *str);
void				lexemes(t_token *token);
t_token				*init_token(void);
t_cmd				*init_command(void);
t_token_list		*init_list(void);
void				add_token(t_token_list *list, char *value);
void				tokenize(char *str, t_token_list *token);
/*################# enviroment handling #################*/
t_envp	*init_envp(char **envp);
int		envp_count(t_envp *envp);
int		envp_add(t_envp **envp, char *value);
int		envp_remove(t_envp **envp, char *key);
char	*get_envp_value(t_envp *envp, char *key);
char	**build_envp(t_shell *shell);
/*################# builtins #################*/
int	bltn_pwd(void);
int	bltn_cd(char *dst);
int	bltn_echo(char **args);
int	bltn_export(char **args);
int	bltn_unset(char **args);
int	bltn_env(void);
int bltn_exit(int status);
#endif
