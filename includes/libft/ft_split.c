/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:21:31 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/05 17:21:43 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_line(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] != 0)
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	size_t	num_words;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	new_str = (char **)malloc(sizeof(char *) * (num_words + 1));
	i = 0;
	j = 0;
	if (!new_str)
		return (NULL);
	while (i < num_words)
	{
		while (s[j] == c)
			j++;
		new_str[i] = ft_substr(&s[j], 0, ft_wordlen(&s[j], c));
		if (!new_str[i])
			return (ft_free_line(new_str, i));
		j = j + ft_wordlen(&s[j], c);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}
