/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_read_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:27:36 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/17 00:20:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_SERVER
#include "minitalk.h"

extern t_mt_server	g_server;

static t_list	*mt_find_node(pid_t pid)
{
	t_mt_reader	*reader;
	t_list		*node;

	node = g_server.readers;
	while (node)
	{
		reader = (t_mt_reader *)node->content;
		if (reader->pid == pid)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_mt_reader	*mt_get_reader(pid_t pid)
{
	t_mt_reader	*reader;
	t_list		*node;

	node = mt_find_node(pid);
	if (node)
		return ((t_mt_reader *)node->content);
	reader = ft_calloc(1, sizeof(t_mt_reader));
	if (!reader)
		return (NULL);
	reader->pid = pid;
	reader->buffer = ft_calloc(1, sizeof(size_t));
	reader->bits = 0;
	reader->init = 0;
	ft_lstadd_front(&g_server.readers, ft_lstnew(reader));
	return (reader);
}

static size_t	mt_read_size(t_mt_reader *reader, size_t offset)
{
	size_t	size;

	if (offset == sizeof(size_t) * 8)
		return (0);
	size = mt_read_size(reader, offset + 1);
	return (size | ((reader->buffer[offset / 8] >> (7 - offset % 8)) & 1)
		<< (sizeof(size_t) * 8 - offset - 1));
}

static void	mt_acknowledge(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	mt_read_bit(t_mt_reader *reader, char bit)
{
	if (!reader->buffer)
		return ;
	if (reader->bits == sizeof(size_t) * 8)
	{
		reader->size = mt_read_size(reader, 0);
		free(reader->buffer);
		reader->buffer = malloc(sizeof(size_t)
				+ (reader->size + 1 * sizeof(char)));
		if (!reader->buffer)
			return ;
		ft_bzero(reader->buffer, sizeof(size_t)
			+ (reader->size + 1 * sizeof(char)));
		reader->init = 1;
	}
	reader->buffer[reader->bits / 8] |= bit << (7 - reader->bits % 8);
	reader->bits++;
	if (reader->init && reader->bits == sizeof(size_t) * 8
		+ reader->size * 8 * sizeof(char))
	{
		write(1, reader->buffer + sizeof(size_t), reader->size);
		write(1, "\n", 1);
		free(reader->buffer);
		mt_acknowledge(reader->pid);
		ft_lstremove(&g_server.readers, mt_find_node(reader->pid), &free);
	}
}
