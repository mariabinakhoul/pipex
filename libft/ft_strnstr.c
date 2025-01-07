/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:33:27 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/06/17 14:18:32 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	j;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!*needle || (*needle == '\0' && n == 0))
		return ((char *)haystack);
	while (*haystack && (n >= needle_len))
	{
		j = 0;
		while (*(haystack + j) == *(needle + j) && *(needle + j))
		{
			j++;
			if (j == needle_len)
				return ((char *)haystack);
		}
		haystack ++;
		n--;
	}
	return (NULL);
}
