/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoyer <efoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:53:51 by efoyer            #+#    #+#             */
/*   Updated: 2026/04/29 13:30:46 by efoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_isnumber(char *s)
{
    int i;
    
    if (s[0] == '\0' || !s)
        return (1);
    i = 0;
    if (s[0] == '+')
        i++;
    if (s[i] == '\0')
        return (1);
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

int check_global(int argc, char **argv)
{
    int i;

    if(argc != 9)
        return (1);
    i = 1;
    while(i < 8)
    {
        if (ft_isnumber(argv[i]))
            return (1);
        if (atoi(argv[i]) <= 0 || atoi(argv[i]) > INT_MAX)
            return (1);
        i++;
    }
    if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
        return (1);
    return (0);
}
