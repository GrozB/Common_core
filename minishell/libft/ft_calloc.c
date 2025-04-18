/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:32 by amadiev           #+#    #+#             */
/*   Updated: 2024/04/14 12:34:28 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*allocate memory for nmemb array of size bytes each with 0 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (nmemb != 0 && (size * nmemb) / nmemb != size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, size * nmemb);
	return (ptr);
}
