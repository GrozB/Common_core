/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:16:30 by bgroz             #+#    #+#             */
/*   Updated: 2024/04/18 10:04:15 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	p = malloc(size * nmemb);
	if (p == 0)
		return (NULL);
	ft_memset(p, 0, size * nmemb);
	return (p);
}
