
/******************************* EXECUTION ENTRY POINT *******************************
 * There are 3 flowpaths in execution:
 * CASE 1: single(no pipeline) command builtin (execute within parent)
 *	 rbsh$ echo "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2
 * CASE 2: single command (non-builtin) (execute within children)
 *	 rbsh$ ls "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2
 * CASE 3: multiple commands(payloads) separated by pipes (execute within children)
 *	 rbsh$ ls "arg1" >>EOF1 <in1 >out2 "arg2" >>EOF2 | echo "arg1" >>EOF2 <in1 >out2 "arg2" >>EOF1 | grep -i....
 */

/******* CASE 1: single command builtin (execute within parent) *******
 *
 * ---> Process all heredocs
 *		---> create buffer, overwrite it for each heredoc
 * ---> Apply all redirections in order
 *		---> If infile (<): open file, redirect stdin to it
 *		---> If outfile (>): create/truncate file, redirect stdout to it
 *		---> If append (>>): create/append file, redirect stdout to it
 *		---> If heredoc (<<): redirect stdin to heredoc buffer
 *		---> If any redirection fails (e.g., file not found), terminat exec and init exec_cleanup.
 * ---> build cmd argv
 * ---> run cmd
 * ---> Store exit status in last_status
 * ---> Restore original stdin, stdout, stderr
 * ---> Clean up (close files, free buffers)
 */

/******* CASE 2: single command (non-builtin) (execute within children) *******
 *
 * ---> Fork a child process
 * ---> Handle fork errors
 *
 * ---> In child process:
 *			---> Process all heredocs
 *					---> create buffer, overwrite it for each heredoc
 *			---> Apply all redirections
 *					---> For each redirection:
 *							---> If infile (<): open file, redirect stdin to it
 *							---> If outfile (>): create|truncate file, redirect stdout to it
 *							---> If append (>>): create|append file, redirect stdout to it
 *							---> If heredoc (<<): redirect stdin to heredoc content
 *		---> If any redirection fails (e.g., file not found), terminate execution and exit.
 *			---> Build full command path
 *					---> Check if argv[0] contains '/' (direct path)
 *					---> Otherwise search in PATH environment variable
 *			---> build argv
 *			---> init execve
 *			---> If execve fails, print error and exit with appropriate status
 *					---> Command not found: exit 127
 *					---> Permission denied: exit 126
 *					--> idk what other codes to handle yet
 *
 * ---> In parent process:
 *			---> Wait for child to finish
 *			---> Get exit status from child
 *					---> If normal exit: use cmd exit status
 *					---> If terminated by sigint(ctrl+c) :130
 *			---> Store in last_status
 */

/******* CASE 3 (pipeline case): *******
 * ---> establish pipeline:
 *	---> Count total commands(payloads) in pipeline
 *	---> Create necessary pipes (n commands need n-1 pipes)
 *			 ---> Allocate memory for pipe_fd[] arrays(do we use array of int arrays?)
 *			 ---> Create each pipe with pipe()
 *			 ---> Handle pipe creation errors
 *
 * ---> Loop through each command in pipeline
 *	---> catch fork errors
 *	---> Fork a new process
 *	(can this entire code block be replaced with the one from case2? need to double check)
 *	---> In child process:
 *		---> Configure pipe connections:
 *			---> If not first command, connect stdin to previous pipe's read end
 *			---> If not last command, connect stdout to next pipe's write end
 *		---> Close all unused pipe fds in child
 *		---> fill heredoc buffers
 *		---> Handle redirections for this command
 *			--> as previously mentioned
 *		---> Check if command is builtin
 *			---> Build command path and argv (also as previously mentioned,,case2)
 *				---> If builtin, execute and exit with its status
 *				---> If external:
 *					---> Execute with execve
 *						---> If execve fails, display error and exit(gracefully ofc)
 *
 *	---> In parent process:
 *		---> Store the most recent child's PID (wait)
 *
 *	---> After creating all processes, parent should:
 *		---> Close all pipe fds
 *		---> Wait for all child processes
 *		---> Record the exit status of the last command in pipeline
 *		---> Free all allocated resources
 *		---> Continuously t_shell last_status
 */