/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:05 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 21:36:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_SERVER
#include "minitalk.h"

t_mt_server	g_server;

static void	mt_sighandler(int signum, siginfo_t *siginfo, void *ucontext)
{
	uint8_t			index;

	(void) ucontext;
	if (signum == SIGINT)
	{
		mt_setup_signals(false);
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
			mt_reset_buffer(&g_server.subbuffers[index++]);
	}
	mt_read_bit(signum == SIGUSR1);
	kill(g_server.last_pid, SIGUSR1);
}

void	mt_setup_signals(bool enabled)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (!enabled)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_sigaction = &mt_sighandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

static void	mt_handle_subbuffers(void)
{
	uint8_t		index;
	t_mt_buffer	*buf;

	index = 0;
	while (index < MT_SERVER_BUFFERS)
	{
		buf = &g_server.subbuffers[index];
		if (buf->ready)
		{
			write(1, buf->data, ft_strlen((char *)buf->data));
			if (buf->data[buf->size / 8 - 1] == '\0')
				write(1, "\n", 1);
			mt_reset_buffer(buf);
		}
		index++;
	}
}

int	main(int argc, char *argv[])
{
	mt_setup_signals(true);
	(void) argc;
	(void) argv;
	ft_printf("[*] Server PID: %d\n", getpid());
	g_server.running = 1;
	g_server.last_pid = 0;
	ft_printf("[*] Waiting for clients...\n");
	while (g_server.running)
	{
		mt_handle_subbuffers();
		usleep(1);
	}
	ft_printf("[*] Server stopped.\n");
	return (0);
}
