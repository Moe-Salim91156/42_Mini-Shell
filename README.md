// execution flow : 

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

      : command execution;
        : determining the command;
        : command validation;
        : if built-ins;
          : flow1;
        : or externals (execve)
          : flow2;

