/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:26:44 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/25 12:41:13 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*alt_str;
	size_t			i;

	alt_str = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (alt_str[i] == (unsigned char)c)
			return (&alt_str[i]);
		i++;
	}
	return (NULL);
}
