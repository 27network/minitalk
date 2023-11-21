/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:57 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 17:51:34 by kiroussa         ###   ########.fr       */
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

#  ifndef MT_DELAY
#   define MT_DELAY 500
#  endif // MT_DELAY

# endif // MT_CLIENT

# ifdef MT_SERVER
/* ************************************************************************** */
/*                                                                            */
/*                                   SERVER                                   */
/*                                                                            */
/* ************************************************************************** */

#  define MT_SERVER_BUFFERS 16
#  define MT_SERVER_BUFFER_SIZE 256

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
	uint8_t		*main_buffer;
	t_mt_buffer	subbuffers[MT_SERVER_BUFFERS];
	uint8_t		current_buffer;
	int8_t		uses_rle;
}	t_mt_server;

void		mt_setup_signals(int enabled);

# endif // MT_SERVER

/* ************************************************************************** */
/*                                                                            */
/*                                   COMMON                                   */
/*                                                                            */
/* ************************************************************************** */

int			mt_compress_data(char *data, char **output);
int			mt_decompress_data(char *data, char **output);

# ifdef MT_COMMON

bool		mt_should_rle(char *str, char **rle_string);
char		*mt_decode_rle(char *str);

# endif // MT_COMMON

#endif // MINITALK_H
