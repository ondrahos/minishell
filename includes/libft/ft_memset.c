/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:00:31 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/16 14:53:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*placeholder;

	placeholder = (char *)str;
	while (n > 0)
	{
		*placeholder = c;
		placeholder++;
		n--;
	}
	return (str);
}
