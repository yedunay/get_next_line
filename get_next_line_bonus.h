/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:53:14 by ydunay            #+#    #+#             */
/*   Updated: 2023/11/04 17:17:12 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef NUM_OF_FD
#  define NUM_OF_FD 1024
# endif

# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *buffer);
char	*ft_strjoin(char const *stack, char const *buffer);
void	*ft_free_stack(char **stack, int create_line);
char	*ft_substr(char const *stack, unsigned int start, size_t len);

#endif