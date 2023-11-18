/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:33:21 by ydunay            #+#    #+#             */
/*   Updated: 2023/11/04 17:16:40 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	long		readval;
	static char	*stack = NULL;
	char		*line;

	line = NULL;
	readval = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (readval > 0)
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		if ((readval <= 0 && !stack) || readval == -1)
			return (ft_free_stack(&stack, 0));
		buffer[readval] = '\0';
		stack = ft_copy_to_stack(stack, buffer);
		if (is_newline(stack))
		{
			line = gets_before_nl(stack);
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = new_line(stack), line);
		}
	}
	return (ft_free_stack(&stack, 1));
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
