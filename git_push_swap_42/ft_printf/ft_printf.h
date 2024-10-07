/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:23:55 by bgroz             #+#    #+#             */
/*   Updated: 2024/10/07 16:34:57 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <aio.h>

int				ft_putcharr(char c);
int				ft_putnbrr(int n);
int				ft_putstrr(char *s);
int				ft_hexadec(unsigned int value);
int				ft_strlenn(char *s);
char			*ft_strrevv(char *str);
int				ft_capital_hexadec(unsigned int value);
int				ft_pointer(void *value);
unsigned int	ft_unsigned_dec(unsigned int n);
int				ft_printf(const char *str, ...);
int				ft_hexadec_long(long long value);
void			*ft_memsett(void *s, int c, size_t n);

#endif