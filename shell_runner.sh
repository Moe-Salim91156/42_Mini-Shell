#!/bin/bash
valgrind --leak-check=full --track-fds=yes --trace-children=yes --suppressions=/home/yokitane/Code/C/Minishell/readline_curses.supp ./minishell
