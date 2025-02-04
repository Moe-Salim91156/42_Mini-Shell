/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:45:51 by msalim            #+#    #+#             */
/*   Updated: 2024/09/01 12:36:20 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * line 18: edge case for MKO,
	we want to adjust the value of len to handle the out_of-bounds check,
	ex: s_len 10, 6,10
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (start + len > s_len)
		len = s_len - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
/*int	main(void)
{
	printf("%s\n",ft_substr("lorem ipsum", 0, 10));
}*/
/*int main(void)
{
	char *result = ft_substr("string", 0, 10);
	if (result != NULL) {
		printf("%s\n", result);
		free(result);
	}
	return (0);
}*/
