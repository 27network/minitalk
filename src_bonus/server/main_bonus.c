/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:05 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/17 01:07:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_SERVER
#include "minitalk.h"

t_mt_server	g_server;

static void	mt_sighandler(int signum, siginfo_t *siginfo, void *ucontext)
{
	t_mt_reader	*reader;

	(void) ucontext;
	if (signum == SIGINT)
	{
		ft_putendl("\n[*] Shutting down gracefully...");
		g_server.running = 0;
		return ;
	}
	reader = mt_get_reader(siginfo->si_pid);
	if (!reader)
		return ;
	mt_read_bit(reader, signum == SIGUSR1);
}

static void	mt_setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &mt_sighandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	ft_putstr("[*] Server PID: ");
	ft_putnbr(getpid());
	ft_putendl("\n[*] Waiting...");
	mt_setup_signals();
	g_server.running = 1;
	g_server.readers = NULL;
	while (g_server.running)
		sleep(1);
	ft_putendl("[*] Server stopped.");
	return (0);
}
