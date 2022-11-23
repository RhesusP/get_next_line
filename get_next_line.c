/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/23 16:59:33 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*temp;
	char	*res;

	res = 0;
	if (!stash)
		return (ft_strdup(buf));
	temp = ft_strdup(stash);
	free(stash);
	stash = NULL;
	res = ft_strjoin(temp, buf);
	free(temp);
	return (res);
}

static int	ft_have_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_stash(char *stash)
{
	size_t	i;
	char	*res;
	
	i = 0;
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	free(stash);
	stash = NULL;
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	*stash = NULL;
	char		*line;

	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (0);
	}
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0 && !stash)
		{
			free(stash);
			stash = NULL;
			return (0);
		}
		if (ret == -1)
		{
			free(stash);
			stash = NULL;
			return (0);
		}
		buf[ret] = '\0';
		stash = ft_copy_to_stash(stash, buf);
		if (ft_have_nl(stash))
		{
			line = ft_extract_line(stash);
			stash = ft_recreate_stash(stash);
			return (line);
		}
	}
	line = ft_strdup(stash);
	free(stash);
	stash = NULL;
	return (line);
}
