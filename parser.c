/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:57:38 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/04 18:21:49 by mtiago-s         ###   ########.fr       */
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
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == sep) // se for igual as aspas faz reset
			sep = 0;
		else if (str[i] == '\'' || str[i] == '\"') // primeira aspa apanhada portanto ligamos a flag (sep) e definimos o seu tamanho em sep_len
			sep = str[i];
		else if (str[i] == ' ' && !sep) // se a flag estiver down sub espaco por 2
			str[i] = '2';
		if (!sep && check_sep(&str[i], &slen)) // pipe e sub por 3 caso nao esteja a flag ligada
		{
			*res++ = ('3' - (len != 0));
			if (str[i] != '|' || (len))
				*res++ = str[i];
			if (str[i] != '|' && slen == 2)
				*res++ = str[++i];
			*res++ = '2';
			len = slen;
		}
		else
		{	
			*res++ = str[i];
			len = 0;
		}
	}
}

int main(int ac, char **av)
{
	(void)ac;
	static char res[500];
	printf("%s\n", av[1]);
	parse(res, av[1], 0, 0);
	printf("%s\n", res);
}
