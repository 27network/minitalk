/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:23:49 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 21:47:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_CLIENT
#include "minitalk.h"

t_mt_client	g_client;

static int	mt_send_bit(char bit)
{
	size_t	timeout;

	g_client.ack_status = 0;
	if (bit)
	{
		if (kill(g_client.pid, SIGUSR1) < 0)
			return (1);
	}
	else
	{
		if (kill(g_client.pid, SIGUSR2) < 0)
			return (1);
	}
	timeout = 0;
	while (g_client.ack_status != 1)
	{
		timeout++;
		usleep(1);
		if (timeout > MT_CLIENT_TIMEOUT || !g_client.pid)
			return (g_client.pid);
	}
	return (0);
}

static int	mt_send_char(char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (mt_send_bit(c & 1 << i))
			return (1);
		i++;
	}
	return (0);
}

static void	mt_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl("\r[*] SIGINT received. Exiting...");
		mt_send_char(0);
		mt_send_char(0);
		g_client.pid = 0;
	}
	else
		g_client.ack_status = (signum == SIGUSR1);
}

static int	mt_send_message(char *msg)
{
	int		i;

	i = 0;
	while (msg && msg[i] && g_client.pid)
	{
		if (mt_send_char(msg[i++]))
		{
			ft_putendl_fd(2, "Error while sending message. Server timeout?");
			return (1);
		}
	}
	mt_send_char(0);
	ft_putendl("Server acknowledged the entire message! :o");
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*pid;

	if (argc != 3)
	{
		if (argc > 3)
			ft_dprintf(2, "Too many arguments.\n");
		pid = "<pid>";
		if (argc > 1)
			pid = argv[1];
		ft_dprintf(2, "Usage: %s %s <message>\n", argv[0], pid);
		if (argc > 3)
			return (-2);
		return (-1);
	}
	else
	{
		signal(SIGINT, &mt_signal_handler);
		signal(SIGUSR1, &mt_signal_handler);
		g_client.pid = ft_atoi(argv[1]);
		if (g_client.pid <= 0 || kill(g_client.pid, 0) < 0)
			ft_putendl_fd(2, "Invalid PID.");
		if (g_client.pid <= 0 || kill(g_client.pid, 0) < 0)
			return (-3);
		return (mt_send_message(argv[2]));
	}
}
