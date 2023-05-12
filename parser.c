/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:57:38 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/12 12:15:53 by mtiago-s         ###   ########.fr       */
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
/* Esta funcao faz o parsing do minishell 
Linha 47: -Se sep encontrado e se encontrado novamente desligado
		if (sep != *str) -> inicializa sep -> sep = 1
		if (sep == *str) -> reinicia sep -> sep = 0;
Linha 49: -Se seo = 0 e ' ' torna em 2 na str
Linha 51: -Se for um token {<, <<, >, >>, |} e sep = 0: 
		  meter um 3 na casa do separador (tem de ser o unico 3 até ver uma 
		  algo diferente de token -> len = 0).
		  -Se nao for um pipe e len>0 --> manter o elemento na str
		  -Se nao for um pipe e slen==2 --> manter o proximo, fazendo dois
		  -No final meter um 2 extra e len passa para 1
Linha 56: Incrementamos o str aqui para poupar linhas
Linha 61: -Caso geral: é ir colando as letras na string res e dizer que 
		  pode começar um novo token -> len = 0*/
void	parse(char *res, char *str, char sep, int slen)
{
	int		len;

	len = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '\"') && (!sep || sep == *str)) 
			sep = (*str) * (sep != *str);
		else if (*str == ' ' && !sep)
			*str = 2;
		if (!sep && check_sep(str, &slen)) // sub de pipes por 3 ou no caso de > colocacao de um tres e do proprio cha
		{
			*res++ = (3 - (len != 0));
			if (*str != '|' || len)
				*res++ = *str;
			if (str++ && *str != '|' && slen == 2)
				*res++ = *str++;
			*res++ = 2;
			len++;
		}
		else
		{	
			*res++ = *str++;
			len = 0;
		}
	}
}

//Example : wc | cat>out ls
//Output:   wc2322cat3>2out2ls

//Example : cat | "grep a" | >>> something
//Output:  cat2322"grep a"23223>>22>22something

//----------------------------------------------------------------
//--  "Makefile < cat"     -- Makefile < cat: command not found --                        --
//----------------------------------------------------------------
//--  "< Makefile cat"     -- Faz here doc e escreve num        --
//--                       -- ficheiro chamado cat              --
//----------------------------------------------------------------
//--  < Makefile cat       --  Faz cat do Makefile no terminal  --
//----------------------------------------------------------------
//--< Makefile cat > out   -- Faz cat para um ficheiro out      --
//----------------------------------------------------------------
//--"< Makefilecat "< cat""-- < Makefilecat : command not found --
//----------------------------------------------------------------
//--    "ls"< cat""        --  Faz o ls no terminal             --
//----------------------------------------------------------------
//--  "Makefile"< ls"      --  Faz o here doc para lado nenhum  --
//----------------------------------------------------------------
//--     ls >>> cat        --  error near unexpected token `>'  --
//----------------------------------------------------------------
//--     ls <<< ola       --   executa o ls                     --
//----------------------------------------------------------------



// int main(int ac, char **av)
// {
// 	char *line = av[1];
// 	(void)ac;
// 	static char res[1000];
// 	printf("%s\n", av[1]);
// 	parse(res,line, 0, 0);
// 	printf("%s\n", res);
// }