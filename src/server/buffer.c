/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:55:16 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 05:04:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_SERVER
#include "minitalk.h"

extern t_mt_server	g_server;

void	mt_reset_buffer(t_mt_buffer *buffer)
{
	ft_bzero(buffer->data, MT_SERVER_BUFFER_SIZE + 1);
	buffer->size = 0;
	buffer->ready = false;
}

void	mt_read_bit(int bit)
{
	t_mt_buffer	*buf;

	buf = &g_server.subbuffers[g_server.current_buffer];
	buf->data[buf->size / 8] |= (bit << (buf->size % 8));
	buf->size++;
	if (buf->size == MT_SERVER_BUFFER_SIZE * 8)
	{
		buf->ready = true;
		g_server.current_buffer = (g_server.current_buffer + 1) 
			% MT_SERVER_BUFFERS;
	}
	if (buf->size % 8 == 0 && buf->data[buf->size / 8 - 1] == '\0')
	{
		buf->ready = true;
	}
}
