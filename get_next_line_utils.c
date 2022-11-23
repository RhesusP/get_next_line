/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:36:53 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/23 18:02:16 by cbernot          ###   ########.fr       */
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

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        char    *res;
        size_t  i;
        size_t  j;

        if (!s)
                return (0);
        if (len > ft_strlen(s))
                len = ft_strlen(s);
        res = malloc(sizeof(char) * (len + 1));
        if (!res || !s)
                return (0);
        i = start;
        j = 0;
        while (i < ft_strlen(s) && j < len)
        {
                res[j] = s[i];
                i++;
                j++;
        }
        res[j] = '\0';
        return (res);
}

void	*ft_free_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}