/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:23:49 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/17 00:21:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_CLIENT
#include "minitalk.h"

#define MT_ACK_DELAY 10000

int	g_pid;

static void	mt_ack_sighandler(int signum)
{
	(void)signum;
	g_pid = 0;
}

static void	mt_send_bit(char bit)
{
	if (bit)
		kill(g_pid, SIGUSR1);
	else
		kill(g_pid, SIGUSR2);
	usleep(MT_DELAY);
}

static int	mt_send_message(char *message)
{
	if (g_pid < 0)
	{
		ft_putendl_fd(2, "Invalid PID.");
		return (0);
	}
	signal(SIGUSR1, mt_ack_sighandler);
	mt_write_str(&mt_send_bit, message);
	usleep(MT_DELAY);
	if (g_pid != 0)
		ft_putendl("Server is not responding.");
	else
		ft_putendl("Message sent successfully!");
	return (g_pid == 0);
}

static void	mt_handle_invalid_arg(char *self_name, char *pid_str)
{
	ft_putstr_fd(1, "Usage: ");
	ft_putstr_fd(1, self_name);
	ft_putstr_fd(1, " ");
	ft_putstr_fd(1, pid_str);
	ft_putendl_fd(1, " <message>");
}

int	main(int argc, char *argv[])
{
	char	*message;
	char	*pid_str;

	if (argc < 3)
	{
		pid_str = "<pid>";
		if (argc >= 2)
			pid_str = argv[1];
		mt_handle_invalid_arg(argv[0], pid_str);
		return (-1);
	}
	else if (argc > 3)
	{
		ft_putendl_fd(2, "Too many arguments.");
		return (-2);
	}
	else
	{
		g_pid = ft_atoi(argv[1]);
		message = argv[2];
		if (!mt_send_message(message))
			return (1);
		return (0);
	}
}
