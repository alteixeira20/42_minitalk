/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:36:34 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 20:10:55 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	main(void)
{
	struct sigaction	sa_signal;
	pid_t				pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", (int)pid);
	sa_signal.sa_handler = handler;
	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = 0;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
}

void	handler(int sig)
{
	static t_bit	*bit_list;
	static t_char	*char_list;
	int				bit;
	char			c;

	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	else
		return ;
	ft_append_bit(&bit_list, bit);
	if (ft_count_bits(bit_list) == 8)
	{
		c = ft_bits_to_char(&bit_list);
		if (c == '\0')
		{
			ft_print_chars(char_list);
			char_list = NULL;
			bit_list = NULL;
			return ;
		}
		ft_append_char(&char_list, c);
	}
}
