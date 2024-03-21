/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:09:46 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/08/28 11:35:10 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!nitems || !size || nitems <= SIZE_MAX / size)
		ptr = malloc(nitems * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * nitems);
	return (ptr);
}
