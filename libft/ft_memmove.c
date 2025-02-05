/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:01:30 by msalim            #+#    #+#             */
/*   Updated: 2024/09/01 15:55:35 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*line 10 : handle overlapping by reading from the end*/
/*line 19 : copying normally if no overlaps are happening*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*des;
	const unsigned char	*sr;

	if (!dest && !src)
		return (dest);
	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (sr < des && des < sr + n)
	{
		sr += n;
		des += n;
		while (n--)
		{
			*(--des) = *(--sr);
		}
	}
	else
	{
		while (n--)
		{
			*des++ = *sr++;
		}
	}
	return (dest);
}
