/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:55:50 by fde-alme          #+#    #+#             */
/*   Updated: 2025/05/02 16:55:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline(char *buffer, ssize_t read_bytes)
{
	ssize_t	i;

	i = 0;
	while (i < read_bytes)
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	store_buffer(t_list **stash, char *buffer, ssize_t read_bytes)
{
	t_list	*node;
	char	*content;
	ssize_t	i;

	i = 0;
	while (i < read_bytes)
	{
		content = (char *) malloc(sizeof(char));
		if (!content)
		{
			ft_lstclear(stash, free);
			return (-1);
		}
		*content = buffer[i];
		node = ft_lstnew(content);
		if (!node)
			return (free(content), -1);
		ft_lstadd_back(stash, node);
		i++;
	}
	return (1);
}

size_t	count_until_nextline(t_list **stash)
{
	t_list	*cursor;
	size_t	size;

	size = 0;
	cursor = *stash;
	while (cursor)
	{
		size++;
		if (*(char *)cursor->content == '\n')
			cursor = NULL;
		else
			cursor = cursor->next;
	}
	return (size);
}

char	*extract_line(t_list **stash)
{
	char	*line;
	t_list	*temp;
	size_t	size;
	size_t	i;

	size = count_until_nextline(stash);
	if (size > 0)
	{
		line = (char *) malloc(size + 1);
		if (!line)
			return (NULL);
		i = 0;
		while (i < size)
		{
			line[i] = *(char *)(*stash)->content;
			temp = *stash;
			*stash = (*stash)->next;
			ft_lstdelone(temp, free);
			i++;
		}
		line[i] = '\0';
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*stash[MAX_FD];
	ssize_t			read_bytes;
	char			*buffer;
	int				result;
	int				found_newline;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	found_newline = 0;
	while (read_bytes > 0 && !found_newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		result = store_buffer(&stash[fd], buffer, read_bytes);
		if (read_bytes == -1 || result == -1)
		{
			ft_lstclear(&stash[fd], free);
			free(buffer);
			return (NULL);
		}
		found_newline = find_newline(buffer, read_bytes);
	}
	free(buffer);
	return (extract_line(&stash[fd]));
}
