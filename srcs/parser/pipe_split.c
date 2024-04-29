/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:07:23 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/04/29 18:22:44 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	quote;

	words = 0;
	i = 0;
	while (s[i] != 0)
	{
		quote = '\0';
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			words++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		if (s[i])
			i++;
	}
	return (words);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != c)
	{
		quote = '\0';
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		if (s[i])
			i++;
	}
	return (i);
}

char	**pipe_split(char const *s, char c)
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
