/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:01:36 by yokitane          #+#    #+#             */
/*   Updated: 2025/04/06 17:47:46 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	EXECUTION ENTRY POINT:
	there are 3 flowpaths in execution,,
	CASE 1: single(no pipeline) command builtin (execute within parent)
	: rbsh$ echo "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2
	CASE 2: single command (non-builtin) (execute within cildren)
	: rbsh$ ls "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2
	CASE 3: multiple commands(payloads) seperated  by pipes (execute within cildren)
	: rbsh$ ls "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2 | echo "arg1" >>EOF2 <in1 >out2 "arg2" >>EOF1 | grep ....
	##########
	******* CASE 1:
	--->fill heredoc buffer (free,overwrite for each new heredoc)
	---> manage redirections (store later to undo)
	---> loop over them sequentially
		--> if outfile, create, link output to it
		--> if heredoc, link input to buffer
		--> if infile, validate,link input to infile,
			-> if unable to open, terminate execution.(implies giving back prompt, freeing heap and undoing redirctions)
	---> run builtin command.
	--->terminate execution
	******* CASE 2:
	******* CASE 3:
  : priority is for heredocs (filling the buffers first)
  : then continuing the priority flow;
  : priority flow :
      : heredocs buffers;
        : iterate through each payload args;
        : look for (<<) for heredoc;
        : fill the buffer for heredoc for each payload, to be read by what afterwards;
      : redirections;
        : in std;
          : determine the most recent input type;
          : line by line checking and validation such that if any infile got error
          the program stops and return error number;
        : out std;
          : determine the most recent output type;
          : all outfiles will be created and truncated whatever the case was, error or not;
          : if correct flow, the output should be redirected to the most recent outfile;
          others will be just created;
          : if error nothing will be wrote, and the files will be created;
	##########
      : command execution;
        : determining the command;
        : command validation;
        : if built-ins;
          : flow1;
        : or externals (execve)
          : flow2;
*/
