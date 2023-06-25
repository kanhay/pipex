/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:49:46 by khanhayf          #+#    #+#             */
/*   Updated: 2023/03/09 18:44:55 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *s)
{
	perror(s);
	exit (1);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dsize)
{
	size_t	i;
	size_t	l;

	l = ft_strlen(src);
	if (dsize == 0)
		return (l);
	i = 0;
	while (src[i] && i < dsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (s1[i] == s2[i] && i < n - 1))
	{
			i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char *s1, char *s2, char *s3)
{
	char	*p;
	int		l1;
	int		l2;
	int		l3;

	if (!s1 && !s2 && !s3)
		return (0);
	l1 = ft_strlen(s1);
	l2 = 1;
	l3 = ft_strlen(s3);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + l3 + 1));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, l1 + 1);
	ft_strlcpy(p + l1, s2, l2 + 1);
	ft_strlcpy(p + (l1 + l2), s3, l3 + 1);
	return (p);
}
