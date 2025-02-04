/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:27:01 by msalim            #+#    #+#             */
/*   Updated: 2024/08/27 13:49:45 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
/*
#include <ctype.h>
#include <stdio.h>
*/
#include "libft.h"

int	ft_isdigit(int c)
{
	int	output;

	output = 1;
	if (c < '0' || c > '9')
		output = 0;
	return (output);
}
/*int	main(void)
{
	printf("%d",isdigit(49));
}*/
