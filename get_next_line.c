/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/23 17:59:33 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*temp;
	char	*res;

	res = 0;
	if (!stash)
	{
		res = ft_strdup(buf);
		if (!res)
			return (ft_free_stash(&res));
		return (res);
	}
	temp = ft_strdup(stash);
	if (!temp)
	{
		return (ft_free_stash(&temp));
	}
	ft_free_stash(&stash);
	res = ft_strjoin(temp, buf);
	if (!res)
		ft_free_stash(&res);
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
		return (ft_free_stash(&stash));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!res)
		return (NULL);
	ft_free_stash(&stash);
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
		return (ft_free_stash(&stash));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret <= 0 && !stash) || ret == -1)
			return (ft_free_stash(&stash));
		buf[ret] = '\0';
		stash = ft_copy_to_stash(stash, buf);
		if (stash && ft_have_nl(stash))	//stash condition added for strict tests
		{
			line = ft_extract_line(stash);
			//printf("line : %s\n", line);
			stash = ft_recreate_stash(stash);
			//printf("stash : %s\n", stash);
			return (line);
		}
	}
	line = ft_strdup(stash);
	ft_free_stash(&stash);
	return (line);
}
