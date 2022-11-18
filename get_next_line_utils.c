/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:36:53 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/18 12:37:35 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	k;
	size_t	len_src;

	if (dstsize == 0)
		return (ft_strlen(src));
	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize < len_dest)
		return (dstsize + len_src);
	else
		len_src += len_dest;
	k = 0;
	while (src[k] != '\0' && (len_dest + k) < dstsize - 1)
	{
		dst[len_dest + k] = src[k];
		k++;
	}
	dst[len_dest + k] = '\0';
	return (len_src);
}

char	*ft_strdup(const char *s1)
{
	char			*res;
	unsigned int	i;

	res = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (res);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if ((!dst && !src) || dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
