/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:54:11 by msalim            #+#    #+#             */
/*   Updated: 2024/08/28 13:53:48 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include	<stdio.h>
#include "libft.h"
#include <ctype.h>*/
#include <unistd.h>

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*int main(void)
{
	printf("%d\n", ft_isalpha(72));
}*/
