#!/bin/bash
valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all --suppressions=readline_curses.supp ./minishell
