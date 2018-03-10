/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lem_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:24:48 by jcamhi            #+#    #+#             */
/*   Updated: 2018/03/10 20:02:43 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

static	int		ft_strcount(char const *s, char const c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		while (s[i] == c && s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] != '\0' && s[i] != '\n')
			count++;
		while (s[i] != c && s[i] != '\0' && s[i] != '\n')
			i++;
	}
	return (count);
}

static	int		poulet(size_t i, size_t j, char const *s, char c)
{
	while (s[i + j] != c && s[i + j] != '\0' && s[i + j] != '\n')
		j++;
	return (j);
}

static	char	**ft_fln(char const *s, char **res, size_t *x, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	*x = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		while (s[i] == c && s[i] != '\0' && s[i] != '\n')
			i++;
		j = 0;
		j = poulet(i, j, s, c);
		if (s[i + j] != '\0' || s[i + j] != '\n' || s[i + j - 1] != c)
		{
			res[*x] = ft_strsub(s, i, j);
			*x = *x + 1;
		}
		i += j;
	}
	return (res);
}

char			**ft_strsplit_lem_in(char const *s, char c)
{
	char	**res;
	size_t	x;

	res = mallocp((ft_strcount(s, c) + 1) * sizeof(char*));
	if (!s || !res)
		return (NULL);
	if (ft_strcount(s, c) == 0)
	{
		res[0] = NULL;
		return (res);
	}
	res = ft_fln(s, res, &x, c);
	res[x] = NULL;
	print_dtab(res);
	return (res);
}
