/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:05 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 00:09:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_SERVER
#include "minitalk.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>

t_mt_server	g_server;

static void	mt_sighandler(int signum, siginfo_t *siginfo, void *ucontext)
{
	uint8_t			index;
	struct timespec	ts;
	long			nano1;

	clock_gettime(CLOCK_REALTIME, &ts);
	nano1 = ts.tv_nsec;
	(void) ucontext;
	if (signum == SIGINT)
	{
		mt_setup_signals(0);
		ft_putendl("\r[*] Shutting down gracefully...");
		g_server.running = 0;
		return ;
	}
	if (g_server.last_pid != siginfo->si_pid)
	{
		ft_printf("\r[*] Client connected: %d\n", siginfo->si_pid);
		g_server.last_pid = siginfo->si_pid;
		g_server.current_buffer = 0;
		index = 0;
		while (index < MT_SERVER_BUFFERS)
			mt_reset_buffer(&g_server.buffers[index++]);
	}
	clock_gettime(CLOCK_REALTIME, &ts);
	printf("\r[*] bit processed in %ld ns\n", ts.tv_nsec - nano1);
}

void	mt_setup_signals(int enabled)
{
	struct sigaction	sa;

	if (!enabled)
		sa.sa_handler = SIG_DFL;
	else
	{
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		sa.sa_sigaction = &mt_sighandler;
	}
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

static void	mt_handle_buffers(void)
{
	uint8_t		index;
	t_mt_buffer	*buf;

	index = 0;
	while (index < MT_SERVER_BUFFERS)
	{
		buf = &g_server.buffers[index];
		if (buf->ready)
		{
			if (buf->data[buf->size / 8 - 1] == '\0')
			{
				write(1, buf->data, buf->size / 8 - 1);
				write(1, "\n", 1);
			}
			else
				write(1, buf->data, buf->size / 8);
			mt_reset_buffer(buf);
		}
		index++;
	}
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	ft_printf("[*] Server PID: %d\n", getpid());
	mt_setup_signals(1);
	g_server.running = 1;
	g_server.last_pid = 0;
	ft_printf("[*] Waiting for clients...\n");
	while (g_server.running)
	{
		mt_handle_buffers();
		usleep(10);
	}
	ft_printf("[*] Server stopped.\n");
	return (0);
}
