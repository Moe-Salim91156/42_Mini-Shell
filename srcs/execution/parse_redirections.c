/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/03 18:18:00 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

#########
create -- file(heredoc) --> then just read from it in last step.
###
per command iteration:
  : check for heredocs;
  : per elements iteration;
	check if element is redirection
	--> handle redirection
		--> determine type
		--> redirect accordingly
	--> catch any errors
	--> skip 2 args
	check if element == arg or cmd
		--> if cmd set cmd_index
		--> skip
  : handle_cmd
   build_args("echo","hi","skibidi",NULL);
   check if elements[cmd_index] is bltn
		: name of the command -> execute code.
	else
	: find_path
		try each path in $PATH
		if found
			--> execve
	: undo_redirection
		//execve(/bin/cat, [cat,-options,NULL],build_env(shell))
	if





*/
