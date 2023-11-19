/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:57 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/19 02:12:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <ft/io.h>
# include <ft/list.h>
# include <ft/mem.h>
# include <ft/string/parse.h>
# include <ft/string.h>

# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

# ifdef MT_CLIENT
/* ************************************************************************** */
/*                                                                            */
/*                                   CLIENT                                   */
/*                                                                            */
/* ************************************************************************** */

#  ifndef MT_DELAY
#   define MT_DELAY 600
#  endif // MT_DELAY

typedef void	(*t_mt_printer)(char);

void		mt_write_str(t_mt_printer printer, char *str);

# endif // MT_CLIENT

# ifdef MT_SERVER
/* ************************************************************************** */
/*                                                                            */
/*                                   SERVER                                   */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_mt_server
{
	int		running;
	t_list	*readers;
}	t_mt_server;

typedef struct s_mt_reader
{
	pid_t		pid;
	uint8_t		*buffer;
	size_t		bits;
	size_t		size;
	uint8_t		init;
}	t_mt_reader;

t_mt_reader	*mt_get_reader(pid_t pid);
void		mt_read_bit(t_mt_reader *reader, char bit);

# endif // MT_SERVER

#endif // MINITALK_H
