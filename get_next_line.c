/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/18 12:46:41 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_save_in_stash(const char *buf, char *stash)
{
	char	*res;

	if (!stash)
		return (ft_strdup(buf));
	res = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, stash, ft_strlen(stash) + ft_strlen(buf) + 1);
	ft_strlcat(res, buf, ft_strlen(stash) + ft_strlen(buf) + 1);
	free(stash);
	return (res);
}

static int	ft_stash_have_nl(const char *stash)
{
	int	i;

	i = 0;
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	//printf("nl is at index %d\n", i - 1);
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	j = 0;
	//printf("########\n");
	while (j <= i)
	{
		line[j] = stash[j];
		//printf("line[%d] : %c   ", j, line[j]);
		//if (line[j] == '\n')
		//	printf("line[%d] is a nl\n", j);
		j++;
	}
	//printf("########\n");
	line[j] = '\0';
	return (line);
}

static char	*ft_refresh_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - (i) + 1));
	if (!new_stash)
		return (0);
	j = 0;
	printf("########\n");
	while (stash[i + 1] != '\0')
	{
		printf("stash[%d] = %c  ", i, stash[i]);
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	new_stash[j] = '\0';
	printf("########\n");
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	int			ret;	//nb bytes lus par read
	char		buf[BUFFER_SIZE];
	static char	*stash;
	char		*line;
	
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 1)
		return (0);
	stash = ft_save_in_stash(buf, stash);
	printf("stash after read : %s\n", stash);
	if (ft_stash_have_nl(stash))
	{
		//printf("stash before : %s\n", stash);
		line = ft_extract_line(stash);
		//printf("line : %s\n", line);
		stash = ft_refresh_stash(stash);
		//printf("stash after : %s\n", stash);
		//printf("line : %s", line);
		return (line);
	}
	while (ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		stash = ft_save_in_stash(buf, stash);
		if (ft_stash_have_nl(stash))
		{
			//printf("stash before : %s\n", stash);
			line = ft_extract_line(stash);
			//printf("line : %s", line);
			stash = ft_refresh_stash(stash);
			printf("stash at the end : %s\n", stash);
			return (line);
			//printf("stash after : %s\n", stash);
		}
	}
	return (0);
}