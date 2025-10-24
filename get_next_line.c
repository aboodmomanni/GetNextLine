/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmoman <aalmoman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:49:02 by aalmoman          #+#    #+#             */
/*   Updated: 2025/10/19 18:49:02 by aalmoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*concatonate(char *left, char *buf, int flag)
{
	char	*tmp;

	if (flag == 1)
	{
		free (left);
		return (NULL);
	}
	if (!left)
		return (f_dup(buf));
	tmp = f_join(left, buf);
	if (!tmp)
	{
		free(left);
		return (NULL);
	}
	return (tmp);
}

static char	*readloop(int fd, char *left)
{
	char	*buf;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		left = concatonate(left, buf, 0);
		if (!left)
		{
			free (buf);
			return (NULL);
		}
		if (f_strchr(left, '\n') != -1)
			break ;
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	free (buf);
	if (bytes < 0)
		concatonate (left, NULL, 1);
	return (left);
}

static char	*extract_line(char *s)
{
	int		i;
	char	*line;

	if (!s || !s[0])
		return (NULL);
	i = f_strchr(s, '\n');
	if (i == -1)
		i = f_strlen(s);
	else
		i++;
	line = f_ssubstr(s, 0, i);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*update_leftover(char *s)
{
	int		start;
	char	*new;

	if (!s)
		return (NULL);
	start = f_strchr(s, '\n');
	if (start == -1)
	{
		free(s);
		return (NULL);
	}
	start++;
	if (s[start] == '\0')
	{
		free(s);
		return (NULL);
	}
	new = f_ssubstr(s, start, f_strlen(s) - start);
	free(s);
	if (!new || new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = readloop(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	if (!line)
	{
		free(leftover);
		return (NULL);
	}
	leftover = update_leftover(leftover);
	return (line);
}

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *line;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
