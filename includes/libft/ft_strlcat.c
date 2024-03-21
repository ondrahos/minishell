/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:00 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/04 15:58:58 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	char	*str;
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	res;

	if (dest == NULL && dstsize == 0)
		return (0);
	str = (char *)src;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	res = 0;
	if (dstsize < dest_len)
		res = src_len + dstsize;
	else
		res = src_len + dest_len;
	while (str[i] != '\0' && (dest_len + 1) < dstsize)
	{
		dest[dest_len] = str[i];
		dest_len++;
		i++;
	}
	dest[dest_len] = '\0';
	return (res);
}
