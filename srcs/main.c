/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:11:48 by msalim            #+#    #+#             */
/*   Updated: 2025/02/04 14:42:53 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int main(void)
{
  char *input = readline("$> ");
  printf("input is : %s\n",input);
  return (0);
}

