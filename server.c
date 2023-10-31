/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:05 by kiroussa          #+#    #+#             */
/*   Updated: 2023/10/25 20:33:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

void	handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("0", 1);
	else if (signum == SIGUSR2)
		ft_putstr_fd("1", 1);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	ft_putstr_fd("[*] Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n[*] Waiting...\n", 1);
	setup_signals();
	while (1)
	{
		sleep(1);
	}
	return (0);
}
