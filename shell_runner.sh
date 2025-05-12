#!/bin/bash
valgrind  --track-fds=yes --trace-children=yes --suppressions=readline_curses.supp --leak-check=full --show-leak-kinds=all ./minishell
