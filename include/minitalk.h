/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:57 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 21:36:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <ft/mem.h>
# include <ft/print.h>
# include <ft/string/parse.h>
# include <ft/string.h>

# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef MT_CLIENT
/* ************************************************************************** */
/*                                                                            */
/*                                   CLIENT                                   */
/*                                                                            */
/* ************************************************************************** */

#  define MT_CLIENT_TIMEOUT 5000

typedef struct s_mt_client
{
	int		pid;
	uint8_t	ack_status;
}	t_mt_client;

# endif // MT_CLIENT

# ifdef MT_SERVER
/* ************************************************************************** */
/*                                                                            */
/*                                   SERVER                                   */
/*                                                                            */
/* ************************************************************************** */

#  define MT_SERVER_BUFFERS 32
#  define MT_SERVER_BUFFER_SIZE 2048

typedef struct s_mt_buffer
{
	uint8_t		data[MT_SERVER_BUFFER_SIZE + 1];
	uint16_t	size;
	bool		ready;
}	t_mt_buffer;

void		mt_reset_buffer(t_mt_buffer *buffer);
void		mt_read_bit(int bit);

typedef struct s_mt_server
{
	bool		running;
	pid_t		last_pid;
	t_mt_buffer	subbuffers[MT_SERVER_BUFFERS];
	size_t		current_buffer;
}	t_mt_server;

void		mt_setup_signals(bool enabled);

# endif // MT_SERVER

#endif // MINITALK_H
