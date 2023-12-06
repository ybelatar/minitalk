/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 06:59:12 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/03 21:27:56 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin_to_char(char c)
{
	static char	*str = NULL;

	if (c)
		str = ft_strjoin(str, c);
	else
	{
		ft_putstr(str);
		ft_putstr("\n");
		free(str);
		str = NULL;
	}
}

void	sig_handler_server(int signum, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	cpt_bit = 0;

	if (signum == SIGUSR2)
		c = (c << 1) | 1;
	else if (signum == SIGUSR1)
		c = c << 1;
	if (cpt_bit < 7)
	{
		cpt_bit++;
	}
	else
	{
		bin_to_char(c);
		cpt_bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR2);
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr("The server's PID : ");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
