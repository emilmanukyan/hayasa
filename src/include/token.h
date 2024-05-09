#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_ENDPOINT,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_COMMA,
		TOKEN_NUMBER,
		TOKEN_IF,
		TOKEN_THEN,
		TOKEN_ELSE,
		TOKEN_BOOL,
		TOKEN_EOF,
	} type;

	char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
