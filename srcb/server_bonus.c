/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:21:34 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/08 19:55:49 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft/libft.h"
#include "../libft/printf/ft_printf_bonus.h"
#include <signal.h>
#include <stdlib.h>

#define BUFFER_SIZE 100000

static void	process_character(unsigned char c, int client_pid)
{
	static unsigned char	*message = NULL;
	static int				char_index = 0;

	if (!message)
	{
		message = malloc(BUFFER_SIZE);
		if (!message)
		{
			ft_printf("Error: Memory allocation failed\n");
			exit(1);
		}
	}
	if (c == '\0')
	{
		message[char_index] = '\0';
		ft_printf("%s\n", message);
		free(message);
		message = NULL;
		char_index = 0;
		kill(client_pid, SIGUSR2);
	}
	else if (char_index < BUFFER_SIZE - 1)
		message[char_index++] = c;
}

void	action(int sig, siginfo_t *info, void *context)
{
	static unsigned char	bit_buffer = 0;
	static int				bit_index = 0;
	int						processing;

	processing = 0;
	(void)context;
	if (processing)
		return ;
	processing = 1;
	if (sig == SIGUSR1)
		bit_buffer = (bit_buffer << 1);
	else if (sig == SIGUSR2)
		bit_buffer = (bit_buffer << 1) | 1;
	else
		return ;
	bit_index++;
	if (bit_index == 8)
	{
		process_character(bit_buffer, info->si_pid);
		bit_buffer = 0;
		bit_index = 0;
	}
	kill(info->si_pid, SIGUSR1);
	processing = 0;
}

int	main(void)
{
	struct sigaction	sa_signal;
	pid_t				pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", (int)pid);
	sa_signal.sa_sigaction = action;
	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
	return (0);
}
