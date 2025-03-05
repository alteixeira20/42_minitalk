/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:37:40 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 17:04:55 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../libft/libft/libft.h"
# include "../../libft/printf/ft_printf_bonus.h"
# include <signal.h>

typedef struct s_bit
{
	int				bit;
	struct s_bit	*next;
}	t_bit;

typedef struct s_char
{
	char			c;
	struct s_char	*next;
}	t_char;

// Linked Lists
t_bit	*ft_new_bit(int bit);
t_char	*ft_new_char(char c);
void	ft_append_bit(t_bit **head, int bit);
void	ft_append_char(t_char **head, char c);
int		ft_count_bits(t_bit *bit_list);
char	ft_bits_to_char(t_bit **bit_list);
void	ft_char_to_bits(char c, int *bits);
#endif
