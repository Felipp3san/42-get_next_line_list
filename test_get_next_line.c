/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:01:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/27 00:24:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*filename;
	char	*filename2;
	char	*line;
	int		fd;
	int		fd2;

	if (argc >= 2)
	{
		filename = argv[1];
		filename2 = argv[2];
		fd = open(filename, O_RDONLY);
		fd2 = open(filename2, O_RDONLY);
		if (fd != -1 && fd2 != -1)
		{
			line = get_next_line(fd);
			printf("%s", line);
			line = get_next_line(fd2);
			printf("%s", line);
			free(line);
			close(fd);
			close(fd2);
		}
	}
	return (0);
}
