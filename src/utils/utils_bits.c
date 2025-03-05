/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:37:02 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 17:02:41 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_count_bits(t_bit *bit_list)
{
	int	count;

	count = 0;
	while (bit_list)
	{
		count++;
		bit_list = bit_list->next;
	}
	return (count);
}

char	ft_bits_to_char(t_bit **bit_list)
{
	char	c;
	t_bit	*temp;
	int		i;
	int		bit_value;
	int		shifted_bit;

	c = 0;
	i = 0;
	while (i < 8 && *bit_list)
	{
		bit_value = (*bit_list)->bit;
		shifted_bit = bit_value << (7 - i);
		c = c | shifted_bit;
		temp = *bit_list;
		*bit_list = (*bit_list)->next;
		free(temp);
		i++;
	}
	return (c);
}

void	ft_char_to_bits(char c, int *bits)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		bits[i] = (c >> (7 - i)) & 1;
		i++;
	}
}
