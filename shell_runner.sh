#!/bin/bash
valgrind --leak-check=full --track-fds=yes --trace-children=yes --show-leak-kinds=all --suppressions=readline_curses.supp ./minishell
