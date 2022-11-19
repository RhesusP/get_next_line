/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/19 18:18:03 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_stash(char *stash, const char *buf)
{
	char	*temp;

	if (!stash)
		return (ft_strdup(buf));
	temp = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, stash, ft_strlen(stash) + ft_strlen(buf) + 1);
	ft_strlcat(temp, buf, ft_strlen(stash) + ft_strlen(buf) + 1);
	stash = ft_strdup(temp);
	return (stash);	
}

static int	ft_have_nl(const char *stash, const char *buf)
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
	int		i;
	char	*line;

	i = 0;
	while (stash[i] != '\n')
		i++;
	//printf("nl qt index %d\n", i);
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (0);
	ft_strncpy(line, stash, i);
	//printf("new strdup stash = %s\n", stash);
	return (line);
}

static char	*ft_refresh_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\n')
		i++;
	i++;
	temp = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!temp)
		return (0);
	j = 0;
	while (stash[i] != '\0')
	{
		temp[j] = stash[i];
		i++;
		j++;
	}
	free(stash);
	stash = ft_strdup(temp);
	free(temp);
	return (stash);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];	// prend les bytes lus par read
	char			*line;				// ligne avec \n retournee
	static char*	stash;				// est concaten avec la valeur de buf a chaque iteration
	int				ret;				// valeur de retour de read (nb bytes lus)

	ret = -2;
	//printf("stash in new iteration : %s\n", stash);
	while (ret > 0 || ret == -2)
	{
		//printf("I'm in the loop !\n");
		ret = read(fd, buf, BUFFER_SIZE);
		//printf("ret : %d\n", ret);
		if (ret == -1 || ret == 0)
			return (0);
		buf[ret] = '\0';
		//printf("buf : %s\n", buf);
		stash = ft_copy_to_stash(stash, buf);
		//printf("stash concat with buf : %s\n", stash);	//TODO remove
		if (ft_have_nl(stash, buf))
		{
			//printf("----> NL DETECTED IN '%s'\n", stash);
			line = ft_extract_line(stash);
			stash = ft_refresh_stash(stash);
			//printf("new stash : %s\n", stash);
			return(line);
		}
	}
	//line = ft_strdup(stash);
	//printf("line in strdup : %s\n", line);
	//stash = NULL;
	return (stash);
}