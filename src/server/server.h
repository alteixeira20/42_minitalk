/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:37:40 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 20:11:18 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../../libft/libft/libft.h"
# include "../../libft/printf/ft_printf_bonus.h"
# include "../utils/utils.h"

void	ft_print_chars(t_char *char_list);
void	handler(int sig);

#endif
