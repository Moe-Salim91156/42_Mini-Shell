/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:17:16 by msalim            #+#    #+#             */
/*   Updated: 2024/09/01 13:10:56 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/*size_t	strlcat(char *dst, const char *src, size_t size);*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	j = 0;
	src_len = 0;
	dst_len = 0;
	while (dst[dst_len] != '\0')
		dst_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (size <= dst_len)
		return (src_len + size);
	i = dst_len;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
/*int main(void)
{
	char dst[20];
	char *src;
	size_t size;

	// Test case 1
	src = "Hello";
	size = 10;
	dst[0] = '\0'; // Ensure dst is empty
	printf("Result test 1: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 2
	src = "";
	size = 10;
	strcpy(dst, "Hello"); // Initialize dst with "Hello"
	printf("Result test 2 : %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 3
	src = "World";
	size = 11;
	strcpy(dst, "Hello"); // Initialize dst with "Hello"
	printf("Result test 3 : %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 4 failed
	src = "World";
	size = 6;
	strcpy(dst, "Hello"); // Initialize dst with "Hello"
	printf("Result - test case 4: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 5 failed
	src = "HelloWorld";
	size = 5;
	strcpy(dst, "Hi"); // Initialize dst with "Hi"
	printf("Result - test case 5: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 6
	src = "Hello";
	size = 7;
	strcpy(dst, "Hi"); // Initialize dst with "Hi"
	printf("Result test case 6: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 7
	src = "Hello";
	size = 20;
	strcpy(dst, "Hi"); // Initialize dst with "Hi"
	printf("Result test case 7: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	// Test case 8
	src = "World";
	size = 0;
	strcpy(dst, "Hello"); // Initialize dst with "Hello"
	printf("Result test case 8: %zu\n", ft_strlcat(dst, src, size));
	printf("dst: '%s'\n", dst);

	return (0);
}*/
