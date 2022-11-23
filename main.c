/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:21:47 by cbernot           #+#    #+#             */
/*   Updated: 2022/11/23 14:27:44 by cbernot          ###   ########.fr       */
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
	free(returned_line);
	
	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	free(returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	free(returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	free(returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	free(returned_line);

	returned_line  = get_next_line(fd);
	printf("get_next_line : %s\n", returned_line);
	free(returned_line);
	
	return (0);
}