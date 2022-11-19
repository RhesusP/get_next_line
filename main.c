/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:17:51 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/19 18:17:49 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	int		fd;
	char	*returned_line;

	fd = open("./test", O_RDONLY);
	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	
	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);

	/*
	while(returned_line)
	{
		returned_line = get_next_line(fd);
		printf("line : %s\n", returned_line);
	}
	*/
}