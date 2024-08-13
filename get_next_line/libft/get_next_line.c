/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:38:12 by rrisseli          #+#    #+#             */
/*   Updated: 2024/06/13 01:51:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd, int n)
{
	char		*line;
	static char	*buffer;

	if (n == 1)
	{
		free(buffer);
		return (NULL);
	}
	if (fd == -1 || BUFFER_SIZE1 <= 0)
		return (NULL);
	buffer = ft_readline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	buffer = ft_buffertrim(buffer);
	return (line);
}

//fonction pour pouvoir retrouver le premier caractere 
//apres le \n dans mon buffer
//allou la memoire avec la taille pour stocker la partie du buffer après le \n.
//deuxieme boucle pour copier le reste du buffer dans line.
//free buffer + return line
char	*ft_buffertrim(char *buffer)
{
	size_t	buffer_i;
	size_t	line_i;
	char	*line;

	buffer_i = 0;
	line_i = 0;
	while (buffer[buffer_i] != '\n' && buffer[buffer_i])
		buffer_i++;
	if (!buffer[buffer_i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(buffer) - buffer_i + 1, sizeof(char));
	buffer_i++;
	while (buffer[buffer_i])
		line[line_i++] = buffer[buffer_i++];
	free(buffer);
	return (line);
}

//prend mon buffer precedent et cherche la position du \n
//une fois trouver on peut allouer la memoire avec i donc taille jusqu'au \n
//on copie buffer dans line et on return line 
char	*ft_getline(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (*buffer != '\n' && *buffer)
		line[i++] = *buffer++;
	if (*buffer == '\n')
		line[i] = '\n';
	return (line);
}

// Alloue la memoire pour stocker dans read_buffer
//cherche un retour a la ligne dans mon buffer 
// ajoute mon temp buffer a mon buffer 
// free le temp buffer et recomence tant qu'on trouve pas de \n
//free en sortant de la boucle et return buffer
char	*ft_readline(int fd, char *buffer)
{
	char	*temp_buffer;
	char	*read_buffer;
	ssize_t	bytes_read;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	temp_buffer = buffer;
	read_buffer = ft_calloc(BUFFER_SIZE1 + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE1);
		if (bytes_read == -1)
		{
			free(read_buffer);
			free(temp_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		temp_buffer = buffer;
		buffer = ft_strjoin(temp_buffer, read_buffer);
		free(temp_buffer);
	}
	free(read_buffer);
	return (buffer);
}
