/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:30:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/24 20:06:02 by msalim           ###   ########.fr       */
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



// what we got from the research is we can do this solution 
//      tokenzier
//      take the token list
//      give to expander 
//      will replace the values
//      replace env variables
//      if there is a command in the env varibales
//            bash behavior -> take first word as command -> rest is argument (if single quote replace env, if single when export do nothing)
//            and then we will tokenize again, so the token list will be ready for the build command and its gonna have the last look of the input
//            after expanding and solving the puzzle
//            cmd_list will go to the execution with the data it needs
//    else
//      tokenize again after expanding, (removing quotes and expand if needed)
//      and then build command will build its structure based on the token list
//      cmd_list will go for the execution phase
