/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:12:04 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/28 13:08:37 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int ft_strcount(const char *str)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    while (str[i] != '\0')
    {
        if ((str[i] != ' ' && str[i] != '\t' && str[i] != '\n') && in_word == 0)
        {
            in_word = 1;
            count++;
        }
        else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            in_word = 0;
        i++;
    }
    return count;
}

static char *ft_substr(const char *s, int start, int len)
{
    char *substr;
    int i;

    substr = (char *)malloc((len + 1) * sizeof(char));
    if (!substr)
        return NULL;
    i = 0;
    while (i < len)
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return substr;
}

char **ft_split(const char *str)
{
    int i = 0;
    int j = 0;
    int start;
    int word_count = ft_strcount(str);
    char **result = (char **)malloc((word_count + 1) * sizeof(char *));

    if (!result)
        return NULL;
    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        start = i;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
            i++;
        if (i > start)
        {
            result[j] = ft_substr(str, start, i - start);
            if (!result[j])
                return NULL;
            j++;
        }
    }
    result[j] = NULL;
    return result;
}
#include <stdio.h>
int main(void)
{
    char **result;
    int i;

    char *test_str = "Hello, this is a\ttest\nstring.";

    result = ft_split(test_str);

    if (result)
    {
        i = 0;
        while (result[i])
        {
            printf("Word %d: %s\n", i, result[i]);
            free(result[i]);
            i++;
        }
        free(result);
    }
    else
    {
        printf("Memory allocation failed\n");
    }

    return 0;
}