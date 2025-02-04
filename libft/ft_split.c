/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:56:26 by msalim            #+#    #+#             */
/*   Updated: 2024/09/02 19:47:27 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	ft_strlen1(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != '\0' && s[count] != c)
		count++;
	return (count);
}

static char	**ft_free(char **strs, int r)
{
	while (r >= 0)
	{
		free(strs[r]);
		r--;
	}
	free(strs);
	return (NULL);
}

static char	**ft_find_fill(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			strs[r] = malloc(ft_strlen1(&s[i], c) + 1);
			if (!strs[r])
				return (ft_free(strs, r - 1));
			while (s[i] && s[i] != c)
				strs[r][j++] = s[i++];
			strs[r][j] = '\0';
			r++;
		}
		else
			i++;
	}
	strs[r] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		word_count;

	word_count = words_count(s, c);
	strs = malloc((word_count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = ft_find_fill(strs, s, c);
	return (strs);
}
