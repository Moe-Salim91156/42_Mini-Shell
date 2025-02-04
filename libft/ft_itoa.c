/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:31:32 by msalim            #+#    #+#             */
/*   Updated: 2024/09/03 16:49:38 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

static int	num_length(long n)
{
	int	length;

	length = 1;
	if (n < 0)
	{
		length++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;
	long	num;

	num = n;
	length = num_length(num);
	str = malloc(length + 1);
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[--length] = (num % 10) + '0';
		num /= 10;
	}
	if (str[0] != '-' && length == 1)
		str[0] = '0';
	return (str);
}
