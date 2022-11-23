/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/22 20:26:57 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
static char	*ft_copy_to_stash(char *stash, const char *buf)
{
	char	*temp;

	printf("ft_copy_to_stash\n");
	if (!stash)
		return (ft_strdup(buf));
	if (ft_strlen(buf) == 0 & ft_strlen(stash) == 0)
		return (0);
	printf("stash : %s   |    taille : %zu\n", stash, ft_strlen(stash));
	printf("buf : %s   |    taille : %zu\n", buf, ft_strlen(buf));
	printf("I allocate : %zu\n", ft_strlen(stash) + ft_strlen(buf) + 1);
	temp = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, stash, ft_strlen(stash) + ft_strlen(buf) + 1);
	ft_strlcat(temp, buf, ft_strlen(stash) + ft_strlen(buf) + 1);
	stash = ft_strdup(temp);
	free(temp);
	return (stash);	
}
*/

static int	ft_have_nl(const char *stash)
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


/*
char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];	// prend les bytes lus par read
	char			*line;					// ligne avec \n retournee
	static char*	stash;					// est concaten avec la valeur de buf a chaque iteration
	int				ret;					// valeur de retour de read (nb bytes lus)

	line = 0;
	ret = -2;
	//printf("stash in new iteration : %s\n", stash);
	while (ret > 0 || ret == -2)
	{
		//printf("I'm in the loop !\n");
		ret = read(fd, buf, BUFFER_SIZE);
		printf("I READ %d BYTES\n", ret);
		if ((ret == -1 || ret == 0) && !stash)
			return (0);
		buf[ret] = '\0';
		printf("buf : %s\n", buf);
		stash = ft_copy_to_stash(stash, buf);
		if (!stash)
			return (0);
		//printf("stash concat with buf : %s\n", stash);	//TODO remove
		if (ft_have_nl(stash))
		{
			//printf("----> NL DETECTED IN '%s'\n", stash);
			line = ft_extract_line(stash);
			stash = ft_refresh_stash(stash);
			//printf("new stash : %s\n", stash);
			return(line);
		}
	}
	line = ft_strdup(stash);
	free(stash);
	stash = 0;
	return (line);
}
*/

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	*stash = "\0";
	char		*line;

	ret = BUFFER_SIZE;
	if (fd <= 0 || BUFFER_SIZE <= 0 || stash == 0)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		buf[ret] = '\0';
		//printf("%s\n", buf);
		stash = ft_strjoin(stash, buf);
		//printf("stash : %s\n", stash);
		if (ft_have_nl(stash))
		{
			line = ft_extract_line(stash);
			stash = ft_refresh_stash(stash);
			return (line);
		}
	}
	line = ft_strdup(stash);
	stash = 0;
	return (line);
}