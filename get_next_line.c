/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:57:28 by fde-alme          #+#    #+#             */
/*   Updated: 2025/04/27 01:25:28 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *buffer)
{
	size_t	i;

	i = 1;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i - 1] == '\n')
			return (i);
		i++;
	}
	return (0);
}

int	store_buffer(t_list **stash, char *buffer)
{
	t_list	*node;
	char	*content;
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\0')
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
		{
			free(content);
			ft_lstclear(stash, free);
			return (-1);
		}
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
	static t_list	*stash;
	char			buffer[BUFFER_SIZE];
	ssize_t			read_bytes;
	int				result;

	read_bytes = 1;
	while (read_bytes > 0 && !find_newline(buffer))
	{
		read_bytes = read(fd, buffer, sizeof(buffer));
		if (read_bytes > 0)
			result = store_buffer(&stash, buffer);
	}
	if (read_bytes == -1 || result == -1)
		return (NULL);
	return (extract_line(&stash));
}
