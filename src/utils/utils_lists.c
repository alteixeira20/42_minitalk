/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:17:43 by paalexan          #+#    #+#             */
/*   Updated: 2025/03/05 17:04:01 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bit	*ft_new_bit(int bit)
{
	t_bit	*node;

	node = malloc(sizeof(t_bit));
	if (!node)
		return (NULL);
	node->bit = bit;
	node->next = NULL;
	return (node);
}

t_char	*ft_new_char(char c)
{
	t_char	*node;

	node = malloc(sizeof(t_char));
	if (!node)
		return (NULL);
	node->c = c;
	node->next = NULL;
	return (node);
}

void	ft_append_bit(t_bit **head, int bit)
{
	t_bit	*node;
	t_bit	*temp;

	node = ft_new_bit(bit);
	if (!*head)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

void	ft_append_char(t_char **head, char c)
{
	t_char	*node;
	t_char	*temp;

	node = ft_new_char(c);
	if (!*head)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

void	ft_print_chars(t_char *char_list)
{
	t_char	*temp;
	char	c;

	while (char_list)
	{
		c = char_list->c;
		ft_putchar_fd(c, 1);
		temp = char_list;
		char_list = char_list->next;
		free(temp);
	}
	ft_putchar_fd('\n', 1);
}
