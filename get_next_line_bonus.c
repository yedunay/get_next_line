/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:52:46 by ydunay            #+#    #+#             */
/*   Updated: 2023/11/04 17:17:23 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static char	*ft_copy_to_stack(char *stack, char *buffer)
{
	char	*new_stack;

	new_stack = 0;
	if (!stack && buffer)
	{
		new_stack = ft_strdup(buffer);
		if (!new_stack)
			return (NULL);
		return (new_stack);
	}
	new_stack = ft_strjoin(stack, buffer);
	ft_free_stack(&stack, 0);
	return (new_stack);
}

static int	is_newline(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*gets_before_nl(char *stack)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		line[j] = stack[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*new_line(char *stack)
{
	size_t	i;
	char	*new_stack;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free_stack(&stack, 0));
	new_stack = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!new_stack)
	{
		ft_free_stack(&stack, 0);
		return (NULL);
	}
	ft_free_stack(&stack, 0);
	return (new_stack);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		read_byte;
	static char	*stack[NUM_OF_FD];
	char		*line;

	line = 0;
	read_byte = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack[fd], 0));
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if ((read_byte <= 0 && !stack[fd]) || read_byte == -1)
			return (ft_free_stack(&stack[fd], 0));
		buffer[read_byte] = '\0';
		stack[fd] = ft_copy_to_stack(stack[fd], buffer);
		if (is_newline(stack[fd]))
		{
			line = gets_before_nl(stack[fd]);
			if (!line)
				return (ft_free_stack(&stack[fd], 0));
			return (stack[fd] = new_line(stack[fd]), line);
		}
	}
	return (ft_free_stack(&stack[fd], 1));
}
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	fd = open("test1.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	close(fd);
	return (0);
}