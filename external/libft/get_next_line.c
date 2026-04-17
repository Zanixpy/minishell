/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omawele <omawele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:39:45 by omawele           #+#    #+#             */
/*   Updated: 2025/12/18 19:57:22 by omawele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_str(char **s)
{
	if ((*s))
	{
		free(*s);
		*s = NULL;
	}
}

static char	*update_tmp_buf(char **tmp_buf)
{
	char	*new_tmp_buf;
	char	*tmp;
	int		i;

	tmp = *tmp_buf;
	if (ft_strchr(*tmp_buf, '\n'))
		tmp = ft_strchr(*tmp_buf, '\n') + 1;
	else
		tmp = NULL;
	if (!tmp)
	{
		free_str(tmp_buf);
		new_tmp_buf = ft_calloc(1, sizeof(char));
		if (!new_tmp_buf)
			return (NULL);
		return (new_tmp_buf);
	}
	new_tmp_buf = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	if (!new_tmp_buf)
		return (free_str(tmp_buf), NULL);
	i = -1;
	while (tmp[++i])
		new_tmp_buf[i] = tmp[i];
	return (free_str(tmp_buf), new_tmp_buf);
}

static char	*create_line(char **tmp_buf)
{
	char	*line;
	char	*tmp;
	int		size;
	int		i;

	tmp = ft_strchr(*tmp_buf, '\n');
	if (!tmp)
		size = ft_strlen(*tmp_buf);
	else
		size = ft_strlen(*tmp_buf) - ft_strlen(tmp) + 1;
	line = ft_calloc(size + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while ((*tmp_buf)[i] != '\n' && (*tmp_buf)[i])
	{
		line[i] = (*tmp_buf)[i];
		i++;
	}
	if ((*tmp_buf)[i] == '\n')
		line[i] = '\n';
	*tmp_buf = update_tmp_buf(tmp_buf);
	if (!(*tmp_buf))
		return (free(line), NULL);
	return (line);
}

static int	read_line(int fd, char **tmp_buf)
{
	char	*buf;
	char	*tmp;
	int		n;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (-2);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		tmp = *tmp_buf;
		*tmp_buf = ft_strjoin(tmp, buf);
		if (!(*tmp_buf))
			return (free(buf), -2);
		if (ft_strchr(*tmp_buf, '\n') || n < BUFFER_SIZE)
			return (free(buf), n);
		n = read(fd, buf, BUFFER_SIZE);
	}
	return (free(buf), n);
}

char	*get_next_line(int fd)
{
	static char	*tmp_buf = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		free_str(&tmp_buf);
		return (NULL);
	}
	if (!tmp_buf)
	{
		tmp_buf = ft_calloc(1, sizeof(char));
		if (!tmp_buf)
			return (NULL);
	}
	if (read_line(fd, &tmp_buf) < 0)
		return (NULL);
	if (!tmp_buf || tmp_buf[0] == '\0')
		return (free_str(&tmp_buf), NULL);
	line = create_line(&tmp_buf);
	if (!line)
		return (free_str(&tmp_buf), NULL);
	return (line);
}
/*int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *s = "Zan";
	while ((s = get_next_line(fd)) != NULL)
	{
		printf("%s", s);
		if (s)
			free(s);
	}
	return (0);
}*/