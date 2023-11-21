/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:35:36 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/17 03:35:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	8192
# endif

/**
 * @brief Get the next line from a file descriptor.
 *
 * @param fd		File descriptor to read from.
 *
 * @return char*	The line that has been read.
 * @return NULL		If an error occurs.
 */
char	*get_next_line(int fd);

#endif // IO_H
