// #include "lexer.h"

// void	print_list(t_lexer *lexer)
// {
// 	while (lexer)
// 	{
// 		printf("[i]: %i; [str]: %s",lexer->i, lexer->str);
// 		lexer = lexer->next;
// 	}
// }
//Lexical Analyzer
/* int main() 
{
	t_lexer 	*lexer;
    char		*input;
	int			i;
	t_tokens 	a;

	a = NEWLINE;
	lexer = NULL;
	i = 0;
    while ((input = readline("> ")) != NULL) 
	{
        add_history(input);
		//ft_lstadd_back(&lexer, ft_lstnew(i, a, input));
        printf("You entered: %s\n", input);
    	rl_on_new_line();
        //free(input);
		i++;
    }
	//print_list(lexer);
    return 0;
} */