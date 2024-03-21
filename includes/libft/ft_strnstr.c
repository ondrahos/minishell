/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:54:56 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/04 16:00:51 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	small_len;
	char	*small;
	char	*large;

	if (big == NULL && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	large = (char *)big;
	small = (char *)little;
	small_len = ft_strlen(small);
	i = 0;
	while (large[i] != '\0' && (i + small_len) <= len)
	{
		if (ft_strncmp(large + i, small, small_len) == 0)
			return (large + i);
		i++;
	}
	return (NULL);
}
