/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:57:38 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/04 18:45:21 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char *str, int *slen)
{
	*slen = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		*slen = 2;
	else if (str[0] == '<' || str[0] == '>')
		*slen = 1;
	else if (str[0] == '|')
		*slen = 1;
	return (*slen);
}

void	parse(char *res, char *str, char sep, int slen)
{
	int		len;

	len = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '\"') && (!sep || sep == *str)) // primeira aspa apanhada portanto ligamos a flag (sep) e definimos o seu tamanho em sep_len
			sep = (*str) * (sep != *str);
		else if (*str == ' ' && !sep) // se a flag estiver down sub espaco por 2
			*str = '2';
		if (!sep && check_sep(str, &slen) && ++len) // pipe e sub por 3 caso nao esteja a flag ligada
		{
			*res++ = ('3' - (len != 0));
			if (*str != '|' || (len))
				*res++ = *str++;
			if (*str != '|' && slen == 2)
				*res++ = *str++;
			*res++ = '2';
		}
		else
		{	
			*res++ = *str++;
			len = 0;
		}
	}
	*res = 0;
}

// int main(int ac, char **av)
// {
// 	char *line = av[1];
// 	(void)ac;
// 	static char res[1000];
// 	printf("%s\n", av[1]);
// 	parse(res,line, 0, 0);
// 	printf("%s\n", res);
// }
