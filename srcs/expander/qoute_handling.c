/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/24 18:42:12 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	expander jobs:
	1- expand $, ~ not required tilde the (~)
	2- handle single quotes
		-nothing is expanded
	3- handle double quotes
		-$ and ~ are expanded
	5- word splitting
		-words are split by spaces
	6- remove quotes
	###############################
*/


// "hello_world" -> hello_world 
//
// 'hello_world' -> hello_world
// "hello $NAME" -> hello (value)
// ''hello $NAME'' -> hello $NAME
// "hello "a"" -> hello a 
// ""hello $NAME "" -> hello (value)
// unclosed > syntax error;
// $? should expand to the exit status 



// so for quotes it will trim all quotes
// for double quotes extra functionality which is env varibales
// for single doesnt matter just trim quotes and write
// for exit status , i think for each command executed , the exit status will be stored
// and the exit status should be expanded to the appropriate number if in d_quotes

/*
void  expand_double_quotes(t_token_list *list)
{
  char  *dollar_sign;
  t_token *current;

  current = list->head;
  dollar_sign = ft_strchr(current->value, '$');
  if (dollar_sign)
  {
    //look inside envrionemnt list for the variable
    //get its value
    // replace the $WHATEVER with the value;
    // remmove the quotes
  }
}*/
