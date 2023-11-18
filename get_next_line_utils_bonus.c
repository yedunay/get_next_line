/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:42:43 by ydunay            #+#    #+#             */
/*   Updated: 2023/11/04 16:35:33 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *buffer)
{
	char	*stack;
	int		i;

	i = 0;
	stack = (char *)malloc(ft_strlen(buffer) + 1);
	if (!stack)
		return (NULL);
	while (*buffer)
		stack[i++] = *buffer++;
	stack[i] = '\0';
	return (stack);
}

char	*ft_strjoin(char const *stack, char const *buffer)
{
	size_t	i;
	char	*new_str;

	if (!stack || !buffer)
		return (NULL);
	new_str = (char *)malloc(ft_strlen(stack) + ft_strlen(buffer) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*stack)
		new_str[i++] = *stack++;
	while (*buffer)
		new_str[i++] = *buffer++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *stack, unsigned int start, size_t len)
{
	char	*new_line;
	size_t	i;
	size_t	j;
	size_t	calc_len;

	calc_len = ft_strlen(stack);
	if (!stack || len <= 0)
		return (NULL);
	if (len > calc_len)
		len = calc_len;
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = start;
	j = 0;
	while (i < calc_len)
	{
		new_line[j] = stack[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	*ft_free_stack(char **stack, int create_line)
{
	char	*line;

	if (!*stack)
		return (NULL);
	if (!create_line)
	{
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
		return (NULL);
	}
	else if (create_line)
	{
		line = ft_strdup(*stack);
		free(*stack);
		*stack = NULL;
		return (line);
	}
	return (NULL);
}
