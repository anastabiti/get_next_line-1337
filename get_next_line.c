/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 09:45:21 by atabiti           #+#    #+#             */
/*   Updated: 2021/12/30 09:58:09 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*reader(char *b, int fd)
{
	char	*r;
	int		bytes;

	r = malloc(BUFFER_SIZE + 1 * sizeof(char ));
	if (!r)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, r, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free (r);
			return (NULL);
		}
		r[bytes] = '\0';
		b = ft_join(b, r);
		if (ft_strchr(b, '\n'))
			break ;
	}
	free (r);
	return (b);
}

static char	*grabline(char *b)
{
	int		i;
	int		a;
	char	*line;

	i = 0;
	while (b[i] && b[i] != '\n')
		i++;
	if (b[i] == '\n')
		i++;
	line = (char *) malloc (sizeof(char ) * i + 1);
	a = 0;
	while (a < i)
	{
		line[a] = b[a];
		a++;
	}
	line[a] = '\0';
	return (line);
}

static char	*removeremaininig(char *b)
{
	int		i;
	int		a;
	char	*line;

	i = 0;
	while (b[i] && b[i] != '\n')
		i++;
	if (b[i] == '\n')
		i++;
	if (b[i] == '\0')
	{
		free (b);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(b) - i + 1));
	if (!line)
		return (NULL);
	a = 0;
	while (b[i])
		line[a++] = b[i++];
	line[a] = '\0';
	free (b);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*b;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	b = reader(b, fd);
	if (!b)
		return (NULL);
	line = grabline(b);
	b = removeremaininig(b);
	return (line);
}
