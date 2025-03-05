/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:51:35 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 20:10:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"

static void	add_null(int server_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(842);
		i++;
	}
}

static void	send_signal(int server_pid, int *bits)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (bits[i] == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(842);
		i++;
	}
}

static void	send_message(int server_pid, char *str)
{
	int	i;
	int	bits[8];

	i = 0;
	while (str[i])
	{
		ft_char_to_bits(str[i], bits);
		send_signal(server_pid, bits);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		server_pid;

	if (argc < 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	send_message(server_pid, argv[2]);
	add_null(server_pid);
	return (0);
}
