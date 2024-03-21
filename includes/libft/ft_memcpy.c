/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:45:53 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/04 14:43:50 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*alt_dest;
	unsigned char	*alt_src;

	if (!dest && !src)
		return (NULL);
	alt_src = (unsigned char *)src;
	alt_dest = (unsigned char *)dest;
	while (n > 0)
	{
		*alt_dest = *alt_src;
		alt_src++;
		alt_dest++;
		n--;
	}
	return (dest);
}
