/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/15 19:39:56 by msalim           ###   ########.fr       */
=======
/*   Updated: 2025/02/15 18:17:40 by yokitane         ###   ########.fr       */
>>>>>>> a0e31c1aa5eb9b05aeaf9bcbccceae65b4c97c1b
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
# define COLOR_MAGENTA "\033[1;37m"
# define COLOR_RESET "\033[0m"

typedef enum e_token_type
{
	WORD,
	COMMAND,
	DQUOTE,
	SQUOTE,
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

void	handle_pipe(char **str,t_token_list *token);
void  handle_single_quote(char **str, t_token_list *tokens);
void handle_word(char **str, t_token_list *tokens) ;
t_cmd_list			*init_cmd_list(void);
t_cmd				*build_cmd(t_token_list *list, t_cmd_list *cmd_list);
void				skip_beginning_spaces(char *str);
void				lexemes(t_token *token);
t_token				*init_token(void);
t_cmd				*init_command(void);
t_token_list		*init_list(void);
void				add_token(t_token_list *list, char *value);
void				tokenize(char *str, t_token_list *token);
#endif
