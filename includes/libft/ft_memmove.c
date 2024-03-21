/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:56:15 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/25 14:52:41 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	tmp_dest = (unsigned char *)dest;
	tmp_src = (unsigned char *)src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	if (dest > src)
		while (n--)
			tmp_dest[n] = tmp_src[n];
	return (dest);
}
