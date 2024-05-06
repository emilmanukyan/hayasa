#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <wctype.h>

lexer_T* init_lexer(char* contents)
{
	lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->line = 1;
	lexer->column = 1;

	return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
        if (lexer->c == '\n' || lexer->c == '\r')
        {
            lexer->line++;
            lexer->column = 1;
            lexer->isArmenian = 0;
        }
        else
        {
        	if (lexer->c == '\t')
        	{
        		lexer->column += 4;
        	}
            lexer->column += 1;
        }
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
	while (lexer->c == ' ' || lexer->c == 10 || lexer->c == 9)
	{
		lexer_advance(lexer);
	}
}

bool isArmenianAndNumeric(wchar_t ch)
{
	const char* set = "«»ԱԲԳԴԵԶԷԸԹԺԻԼԽԾԿՀՁՂՃՄՅՆՇՈՉՊՋՌՍՎՏՐՑՒՓՔևՕՖաբգդեզէըթժիլխծկհձղճմյնշոչպջռսվտրցւփքօֆ";
	
	if (strchr(set, ch) != NULL)
		return true;
	return false;
}

bool isComment(wchar_t ch)
{
	const char* set = "―";

	if (strchr(set, ch) != NULL)
		return true;
	return false;
}

bool isNumeric(wchar_t ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}

void lexer_collect_comment(lexer_T* lexer)
{
	if (isComment(lexer->c))
		lexer_advance(lexer);
	while(!isComment(lexer->c) && lexer->c != '\0' && lexer->c != '\n'){
		lexer_advance(lexer);
	}
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == 10 || lexer->c == 9)
			lexer_skip_whitespace(lexer);
		
		if (isComment(lexer->c))
		{
			lexer_collect_comment(lexer);
			continue;
		}

		if (isArmenianAndNumeric(lexer->c))
			return lexer_collect_id(lexer);

		if (lexer->c == '"')
			return lexer_collect_string(lexer);


		if (isNumeric(lexer->c))
			return lexer_collect_number(lexer);

		switch (lexer->c)
		{
			case L';': return lexer_advance_with_token(lexer, init_token(TOKEN_ENDPOINT, lexer_get_current_char_as_string(lexer))); break;
			case L',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))); break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
				printf("Անհայտ սիմվոլ `%c`\n", lexer->c);
				printf("Տող՝ « %d »\nՍյուն՝ « %d »\n", lexer->line, lexer->column - (lexer->isArmenian / 2));
				exit(1);
		}
	}

	return init_token(TOKEN_EOF, "\0");
}

token_T* lexer_collect_string(lexer_T* lexer)
{
	lexer_advance(lexer);
	char* value = calloc(1, sizeof(wchar_t));
	value[0] = '\0';

	while (lexer->c != '"')
	{
		char* s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(wchar_t));
		strcat(value, s);
		lexer_advance(lexer);
		lexer->isArmenian++;
	}
	lexer_advance(lexer);

	return init_token(TOKEN_STRING, value);
}


token_T* lexer_collect_number(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    char* s = "";

    value[0] = '\0';

    while (isNumeric(lexer->c))
    {
        s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }

    return init_token(TOKEN_NUMBER, value);
}


token_T* lexer_collect_id(lexer_T* lexer)
{
	char* value = calloc(1, sizeof(wchar_t));
	char* s = "";

	value[0] = '\0';

	while (isArmenianAndNumeric(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(wchar_t));
		strcat(value, s);
		lexer_advance(lexer);
		lexer->isArmenian++;
	}

	if (strcmp(value, "ՎԵՐԱԳՐԻՐ") == 0)
	 	return init_token(TOKEN_EQUALS, value);
	else if (strcmp(value, "ՍԿԻԶԲ") == 0)
	 	return init_token(TOKEN_LBRACE, value);
	else if (strcmp(value, "ԱՎԱՐՏ") == 0)
	 	return init_token(TOKEN_RBRACE, value);
	else if (strcmp(value, "«") == 0)
		return init_token(TOKEN_LPAREN, value);
	else if (strcmp(value, "»") == 0)
		return init_token(TOKEN_RPAREN, value);	

	return init_token(TOKEN_ID, value);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
	lexer_advance(lexer);

	return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer)
{
	char* str = calloc(2, sizeof(wchar_t));
	str[0] = lexer->c;
	str[1] = '\0';

	return str;
}
