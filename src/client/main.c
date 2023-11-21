/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:23:49 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/20 23:45:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_CLIENT
#include "minitalk.h"

int	g_pid;

static int	mt_send_bit(char bit)
{
	if (bit)
	{
		if (kill(g_pid, SIGUSR1) < 0)
			return (1);
	}
	else
	{
		if (kill(g_pid, SIGUSR2) < 0)
			return (1);
	}
	usleep(MT_DELAY);
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
		ft_putendl("\r[*] SIGINT received. Exiting...");
	mt_send_char(0);
	mt_send_char(0);
	g_pid = 0;
}

static int	mt_send_message(char *message)
{
	if (g_pid <= 0)
	{
		ft_putendl_fd(2, "Invalid PID.");
		return (-3);
	}
	if (kill(g_pid, 0) < 0)
	{
		ft_putendl_fd(2, "Unknown PID.");
		return (-4);
	}
	while (*message && g_pid)
	{
		if (mt_send_char(*message++))
		{
			ft_putendl_fd(2, "Error while sending message.");
			return (1);
		}
	}
	mt_send_char(0);
	g_pid = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*message;
	char	*pid;

	if (argc != 3)
	{
		if (argc > 3)
			ft_dprintf(2, "Too many arguments.\n");
		pid = "<pid>";
		if (argc > 1)
			pid = argv[1];
		ft_dprintf(2, "Usage: %s %5s <message>\n", argv[0], pid);
		if (argc > 3)
			return (-2);
		return (-1);
	}
	else
	{
		signal(SIGINT, &mt_signal_handler);
		signal(SIGUSR1, &mt_signal_handler);
		g_pid = ft_atoi(argv[1]);
		message = argv[2];
		return (mt_send_message(message));
	}
}
