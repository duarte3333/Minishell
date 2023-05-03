#include "lexer.h"

void	print_list(t_lexer *lexer)
{
	while (lexer)
	{
		printf("[i]: %i; [str]: %s",lexer->i, lexer->str);
		lexer = lexer->next;
	}
}
//Lexical Analyzer
int main() 
{
	t_lexer 	*lexer;
    char		*input;
	int			i;
	t_tokens 	a;

	(input = readline("> "));
	i = 0;
	a = NEWLINE;
	lexer = ft_lstnew(i, a,de input);
    free(input);
	i++;
    while ((input = readline("> ")) != NULL) {
        add_history(input);
		ft_lstadd_back(&lexer, ft_lstnew(i, a, input));
        printf("You entered: %s\n", input);
        free(input);
		i++;
    }
	//print_list(lexer);
    return 0;
}