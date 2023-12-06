/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 06:59:09 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/06 18:50:51 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_led;

void	char_to_bin(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_led = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit--;
		while (!g_led)
			pause();
	}
}

void	send_signal(int pid, char *str)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
		char_to_bin(pid, str[i++]);
}

void	sig_handler_client(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		g_led = 1;
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler_client;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac == 3)
	{
		if (!av[1][0] || !av[2][0])
		{
			ft_putstr("Argument error : empty argument\n");
			exit(1);
		}
		if (ft_atoi(av[1]) <= 0 || kill(ft_atoi(av[1]), 0))
		{
			ft_putstr("Argument error : Invalid PID\n");
			exit(1);
		}
		send_signal(ft_atoi(av[1]), av[2]);
	}
	else
		ft_putstr("Argument error : try ./client PID string_to_send\n");
	return (0);
}
