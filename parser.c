/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:57:38 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/05 18:43:48 by mtiago-s         ###   ########.fr       */
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
		if ((*str == '\'' || *str == '\"') && (!sep || sep == *str)) // sep encontrado e se encontrado novamente desligado
			sep = (*str) * (sep != *str);
		else if (*str == ' ' && !sep) // se a flag estiver down sub espaco por 2
			*str = '2';
		if (!sep && check_sep(str, &slen)) // sub de pipes por 3 ou no caso de > colocacao de um tres e do proprio cha
		{
			*res++ = ('3' - (len != 0));
			if (*str != '|' || len)
				*res++ = *str;
			if (str++ && *str != '|' && slen == 2) // incrementamos o str aqui para poupar linhas
				*res++ = *str++;
			*res++ = '2';
			len++;
		}
		else
		{	
			*res++ = *str++;
			len = 0;
		}
	}
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
