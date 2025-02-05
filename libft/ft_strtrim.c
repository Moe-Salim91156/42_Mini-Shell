/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:58:56 by msalim            #+#    #+#             */
/*   Updated: 2024/09/01 15:55:30 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*printf("%ld\n",end);*/
/*printf("%ld\n",start);*/
/*line 13 : incrementing the start and checking each character using strchr*/
/*line 15 : and using the value of start to know where to stop*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	str_len;
	size_t	start;
	size_t	end;
	char	*m_s;

	str_len = ft_strlen(s1);
	start = 0;
	end = str_len;
	if (!s1 || !set)
		return (NULL);
	while (start <= str_len && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	m_s = ft_substr(s1, start, end - start);
	return (m_s);
}
/*int	main(void)
{
	printf("%s\n", ft_strtrim("\nlaaastrl","l\na"));
}*/
