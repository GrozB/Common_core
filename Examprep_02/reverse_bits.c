/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:44:27 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/28 13:40:47 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	res;
	int				i;

	res = 0;
	i = 8;
	while (i > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (res);
}

int main()
{
    unsigned char octet = 0b01000001;
    unsigned char reversed = reverse_bits(octet);

    int i = 7;
    while (i >= 0)
    {
        if (reversed & (1 << i))
            write(1, "1", 1);
        else
            write(1, "0", 1);
        i--;
    }
    write(1, "\n", 1);

    return 0;
}
