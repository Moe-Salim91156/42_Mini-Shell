#!/bin/bash
valgrind  --track-fds=yes --trace-children=yes --suppressions=readline_curses.supp ./minishell
