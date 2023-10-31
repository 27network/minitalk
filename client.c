/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:23:49 by kiroussa          #+#    #+#             */
/*   Updated: 2023/10/25 18:58:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

#define DELAY 100

void	write_bytes(int pid, char *bytes)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (bytes[i])
	{
		c = bytes[i];
		j = 0;
		while (j < 8)
		{
			if (c & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c >>= 1;
			usleep(DELAY);
			j++;
		}
		i++;
	}
}

void	send_message(int pid, char *message)
{
	size_t	len;

	len = ft_strlen(message);
	(void) pid;
	(void) len;
	// write 32bit message length
	// write message
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*message;
	char	*pid_str;

	if (argc != 3)
	{
		pid_str = "<pid>";
		if (argc == 2)
			pid_str = argv[1];
		ft_putstr_fd("Usage: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(pid_str, 1);
		ft_putstr_fd(" <message>\n", 1);
		return (1);
	}
	else
	{
		pid = ft_atoi(argv[1]);
		message = argv[2];
		send_message(pid, message);
		return (0);
	}
}
