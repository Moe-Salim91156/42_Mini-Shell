/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:12:28 by msalim            #+#    #+#             */
/*   Updated: 2025/02/10 16:51:42 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libft/libft.h"
typedef enum e_token_type
{ 
    WORD, PIPE, REDIRECT_IN, REDIRECT_OUT
} t_token_type;

typedef struct  s_token
{
  t_token_type type; //enum value;
  char *value; // actual text of it (value);
  struct s_token *next;//to the next node if applicable
} t_token;

typedef struct s_token_list
{
  int size;
  t_token *head;
}t_token_list;

typedef struct s_cmd
{
  char **args;
  struct s_cmd *next;
}t_cmd; 

#endif

void	skip_beginning_spaces(char *str);
void  lexemes(t_token *token);
t_token  *init_token();
t_cmd *init_cmd();
t_token_list	*init_list(void);
void	add_token(t_token_list *list, char *value);
void	tokenize(char *str, t_token_list *token);
