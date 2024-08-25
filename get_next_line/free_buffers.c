/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:23:15 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/25 18:38:41 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h" 

char	*free_buff(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}

char	*free_all_buff(char *buffer, char *read_buff)
{
	if (read_buff)
		free(read_buff);
	if (buffer)
		free(buffer);
	return (NULL);
}
