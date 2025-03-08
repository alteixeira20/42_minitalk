/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:36:22 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/08 18:54:25 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft/libft.h"
#include "../libft/printf/ft_printf_bonus.h"
#include <signal.h>

static volatile int	g_ack_received = 0;

static void	wait_validation(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	terminate_client(int sig)
{
	(void)sig;
	exit(0);
}

static void	send_signal(int server_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while (!g_ack_received)
			pause();
		i--;
	}
}

static void	send_message(int server_pid, char *str)
{
	int					i;
	struct sigaction	sa_done;

	g_ack_received = 0;
	sa_done.sa_handler = terminate_client;
	sigemptyset(&sa_done.sa_mask);
	sa_done.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa_done, NULL);
	i = 0;
	while (str[i])
	{
		send_signal(server_pid, str[i]);
		i++;
	}
	send_signal(server_pid, '\0');
	while (!g_ack_received)
		pause();
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa_ack;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <server_pid> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1)
	{
		ft_printf("Error: Invalid server PID or server is not running.\n");
		return (1);
	}
	sa_ack.sa_handler = wait_validation;
	sigemptyset(&sa_ack.sa_mask);
	sa_ack.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_ack, NULL);
	send_message(server_pid, argv[2]);
	return (0);
}
