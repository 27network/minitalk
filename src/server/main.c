/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:05 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 17:56:23 by kiroussa         ###   ########.fr       */
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
		g_server.uses_rle = -1;
		g_server.main_buffer = NULL;
		index = 0;
		while (index < MT_SERVER_BUFFERS)
			mt_reset_buffer(&g_server.subbuffers[index++]);
	}
	if (g_server.uses_rle == -1)
		g_server.uses_rle = signum == SIGUSR1;
	else
		mt_read_bit(signum == SIGUSR1);
}

void	mt_setup_signals(int enabled)
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

static void	mt_write(char *buf)
{
	bool	uses_rle;
	char	*str;

	uses_rle = g_server.uses_rle;
	str = buf;
	if (uses_rle)
	{
		ft_printf("writing from rle\n");
		mt_decompress_data(buf, &str);
	}
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (uses_rle)
		free(str);
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
			ft_printf("\r[*] Received %d bytes: %s\n", buf->size / 8, buf->data);
			ft_strappend((char **)&g_server.main_buffer, (char *)buf->data);
			if (buf->data[buf->size / 8 - 1] == '\0')
			{
				ft_printf("\r[*] Received full message from %d\n", g_server.last_pid);
				mt_write((char *)g_server.main_buffer);
				free(g_server.main_buffer);
				g_server.main_buffer = NULL;
			}
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
	g_server.uses_rle = -1;
	g_server.last_pid = 0;
	g_server.main_buffer = NULL;
	ft_printf("[*] Waiting for clients...\n");
	while (g_server.running)
	{
		mt_handle_subbuffers();
		usleep(10);
	}
	ft_printf("[*] Server stopped.\n");
	return (0);
}
