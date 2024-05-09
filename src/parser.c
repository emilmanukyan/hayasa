#include "include/parser.h"
#include "include/scope.h"
#include "include/lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

parser_T* init_parser(lexer_T* lexer)
{
	parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->prev_token = parser->current_token;

	parser->scope = init_scope();

	return parser;
}

void parser_eat(parser_T* parser, int token_type)
{
	char *tokens[] = {"ՀԱՅ", "ՎԵՐԱԳՐԻՐ", "\"\"", ";", "«", "»", "ՍԿԻԶԲ", "ԱՎԱՐՏ", "և", "թիվ", "ԵԹԵ", "ԱՊԱ", "ԱՅԼԱՊԵՍ", "ՃՇՄԱՐԻՏ կամ ԿԵՂԾ", "ՎԵՐԱԴԱՐՁՐՈՒ"};
	if (parser->current_token->type == token_type)
	{
		parser->prev_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	else
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf(
			"Չսպասված նույնացուցիչ `%s`: Սպասվում է `%s`:\n",
			parser->current_token->value,
			tokens[token_type]
		);
		printf("Տող՝ « %d »\nՍյուն՝ « %d »\n", parser->lexer->line, parser->lexer->column - (parser->lexer->isArmenian / 2));
		exit(1);
	}
}

AST_T* parser_parse(parser_T* parser, scope_T* scope)
{
	return parser_parse_statements(parser, scope);
}

AST_T* parser_parse_statement(parser_T* parser, scope_T* scope)
{
	switch(parser->current_token->type)
	{
		case TOKEN_ID: return parser_parse_id(parser, scope);
		case TOKEN_IF: return parser_parse_condition(parser, scope);
		// case TOKEN_RETURN: return parser_parse_function_return(parser, scope);
		// default: printf("here we go again\n");
	}

	return init_ast(AST_NOOP);
}

AST_T* parser_parse_statements(parser_T* parser, scope_T* scope)
{
	AST_T* compound = init_ast(AST_COMPOUND);
	compound->scope = scope;
	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* ast_statement = parser_parse_statement(parser, scope);
	ast_statement->scope = scope;
	compound->compound_value[0] = ast_statement;
	compound->compound_size += 1;
	while (parser->current_token->type == TOKEN_ENDPOINT)
	{
		parser_eat(parser, TOKEN_ENDPOINT);
		
		if(ast_statement)
		{
			AST_T* ast_statement = parser_parse_statement(parser, scope);
			compound->compound_size += 1;
			compound->compound_value = realloc(
				compound->compound_value,
				compound->compound_size * sizeof(struct AST_STRUCT*)
			);
			compound->compound_value[compound->compound_size-1] = ast_statement;
		}
	}
	return compound;
}

AST_T* parser_parse_expr(parser_T* parser, scope_T* scope)
{
	switch (parser->current_token->type)
	{
		case TOKEN_STRING: return parser_parse_string(parser, scope);
        case TOKEN_NUMBER: return parser_parse_number(parser, scope);
        case TOKEN_BOOL: return parser_parse_boolean(parser, scope);
		case TOKEN_ID: return parser_parse_id(parser, scope);
		// default: printf("%d\n Unexpected token", parser->current_token->type);
	}

	return init_ast(AST_NOOP);
}

AST_T* parser_parse_factor(parser_T* parser, scope_T* scope)
{

}

AST_T* parser_parse_term(parser_T* parser, scope_T* scope)
{

}

AST_T* parser_parse_function_call(parser_T* parser, scope_T* scope)
{
	AST_T* function_call = init_ast(AST_FUNCTION_CALL);
	
	function_call->function_call_name = parser->prev_token->value;
	parser_eat(parser, TOKEN_LPAREN);
	
	function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* ast_expr = parser_parse_expr(parser, scope);
	function_call->function_call_arguments[0] = ast_expr;
	function_call->function_call_arguments_size += 1;
	
	while (parser->current_token->type == TOKEN_COMMA)
	{
		parser_eat(parser, TOKEN_COMMA);

		AST_T* ast_expr = parser_parse_expr(parser, scope);
		function_call->function_call_arguments_size += 1;
		function_call->function_call_arguments = realloc(
			function_call->function_call_arguments,
			function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*)
		);
		function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
	}

	parser_eat(parser, TOKEN_RPAREN);

	function_call->scope = scope;

	return function_call;
}

AST_T* parser_parse_variable_definition(parser_T* parser, scope_T* scope)
{
	parser_eat(parser, TOKEN_ID); // ՀԱՅ
	char* variable_definition_variable_name = parser->current_token->value;

	parser_eat(parser, TOKEN_ID);
	parser_eat(parser, TOKEN_EQUALS);
	AST_T* variable_definition_value = parser_parse_expr(parser, scope);

	AST_T* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
	variable_definition->variable_definition_variable_name = variable_definition_variable_name;
	variable_definition->variable_definition_value = variable_definition_value;

	scope_add_variable_definition(scope, variable_definition);
	// variable_definition->scope = scope;

	return variable_definition;
}

AST_T* parser_parse_function_definition(parser_T* parser, scope_T* scope)
{
	AST_T* ast = init_ast(AST_FUNCTION_DEFINITION);
	parser_eat(parser, TOKEN_ID); // ԳՈՐԾԱՌՈՒՅԹ

	char* function_name = parser->current_token->value;
	ast->function_definition_name = calloc(
		strlen(function_name) + 1, sizeof(char)
	);
	strcpy(ast->function_definition_name, function_name);
	if (function_name[0] >= '0' && function_name[0] <= '9')
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("Գործառույթի սխալ անվանում ՝%s`\n", function_name); 
		printf("Տող՝ « %d »\nՍյուն՝ « %d »\n", parser->lexer->line, parser->lexer->column - (parser->lexer->isArmenian / 2));
		exit(1);
	}
	parser_eat(parser, TOKEN_ID);

	parser_eat(parser, TOKEN_LPAREN);
	if (parser->current_token->type != TOKEN_RPAREN)
	{
		ast->function_definition_args = calloc(1, sizeof(struct AST_STRUCT*));	
		
		AST_T* arg = parser_parse_variable(parser, scope);
		ast->function_definition_args_size += 1;
		ast->function_definition_args[ast->function_definition_args_size - 1] = arg;
		
		// parser_eat(parser, TOKEN_COMMA);
		while(parser->current_token->type == TOKEN_COMMA)
		{
			parser_eat(parser, TOKEN_COMMA);
			ast->function_definition_args_size += 1;

			ast->function_definition_args =
				realloc(
					ast->function_definition_args,
					ast->function_definition_args_size * sizeof(struct AST_STRUCT*)
				);

			AST_T* arg = parser_parse_variable(parser, scope);
			ast->function_definition_args[ast->function_definition_args_size - 1] = arg;
		}
	}

	parser_eat(parser, TOKEN_RPAREN);

	parser_eat(parser, TOKEN_LBRACE);

	ast->function_definition_body = parser_parse_statements(parser, scope);

	parser_eat(parser, TOKEN_RBRACE);

	ast->scope = scope;
	// scope_add_function_definition(scope, ast);

	return ast;
}

// AST_T* parser_parse_function_return(parser_T* parser, scope_T* scope)
// {
//     parser_eat(parser, TOKEN_RETURN);
//     AST_T* expr = parser_parse_expr(parser, scope);

//     AST_T* function_return = init_ast(AST_FUNCTION_RETURN);
//     function_return->function_return_expr = expr;
// 	// printf("%s\n", function_return->function_return_expr->variable_name);
    
//     function_return->scope = scope;

//     return function_return;
// }

AST_T* parser_parse_variable(parser_T* parser, scope_T* scope)
{
	char* token_value = parser->current_token->value;
	parser_eat(parser, TOKEN_ID);

	if (parser->current_token->type == TOKEN_LPAREN)
		return parser_parse_function_call(parser, scope);
	else if (parser->current_token->type == TOKEN_EQUALS)
    {
        parser_eat(parser, TOKEN_EQUALS);
        AST_T* expr = parser_parse_expr(parser, scope);
        AST_T* variable_reassignment = init_ast(AST_VARIABLE_REASSIGNMENT);
        variable_reassignment->variable_reassignment_name = token_value;
        variable_reassignment->variable_reassignment_value = expr;

        variable_reassignment->scope = scope;
        // printf("%s\n", variable_reassignment->variable_reassignment_name);
        return variable_reassignment;
    }
	
	AST_T* ast_variable = init_ast(AST_VARIABLE);
	ast_variable->variable_name = token_value;

	ast_variable->scope = scope;

	return ast_variable;
}

AST_T* parser_parse_string(parser_T* parser, scope_T* scope)
{
	AST_T* ast_string = init_ast(AST_STRING);
	ast_string->string_value = parser->current_token->value;
	// printf("%s - %s\n", ast_string->variable_name, ast_string->string_value);
	parser_eat(parser, TOKEN_STRING);

	ast_string->scope = scope;

	return ast_string;
}

AST_T* parser_parse_number(parser_T* parser, scope_T* scope)
{
	AST_T* ast_number = init_ast(AST_NUMBER);
	ast_number->number_value = atol(parser->current_token->value);
    parser_eat(parser, TOKEN_NUMBER);
    
    ast_number->scope = scope;

    return ast_number;
}

AST_T* parser_parse_boolean(parser_T* parser, scope_T* scope)
{
	AST_T* ast_bool = init_ast(AST_BOOL);
	if (strcmp(parser->current_token->value, "ՃՇՄԱՐԻՏ") == 0)
	{
		ast_bool->string_value = "ՃՇՄԱՐԻՏ";
		ast_bool->bool_value = true;
	}
	else
	{
		ast_bool->string_value = "ԿԵՂԾ";
		ast_bool->bool_value = false;
	}

    parser_eat(parser, TOKEN_BOOL);
    
    ast_bool->scope = scope;

    return ast_bool;
}

AST_T* parser_parse_condition(parser_T* parser, scope_T* scope)
{
	parser_eat(parser, TOKEN_IF);

	parser_eat(parser, TOKEN_LPAREN);

	AST_T* ast_condition = init_ast(AST_CONDITIONAL);
	ast_condition->conditional_condition = parser_parse_expr(parser, scope);
	
	parser_eat(parser, TOKEN_RPAREN);

	parser_eat(parser, TOKEN_THEN);

	ast_condition->conditional_consequence = parser_parse_statements(parser, scope);

	if (parser->current_token->type == TOKEN_ELSE)
	{
		parser_eat(parser, TOKEN_ELSE);
		// if (strcmp(parser->current_token->value, "ԵԹԵ") == 0)
		// {
		// 	parser_eat(parser, TOKEN_IF);
		// 	parser_eat(parser, TOKEN_LPAREN);
		// 	ast_condition->conditional_condition = parser_parse_expr(parser, scope);
		// 	parser_eat(parser, TOKEN_RPAREN);

		// 	parser_eat(parser, TOKEN_THEN);
		// 	ast_condition->conditional_consequence = parser_parse_statements(parser, scope);
		// }
		ast_condition->conditional_alternative = parser_parse_statements(parser, scope);
	}
	parser_eat(parser, TOKEN_RBRACE);

	ast_condition->scope = scope;

	return ast_condition;
}

AST_T* parser_parse_id(parser_T* parser, scope_T* scope)
{
	if (strcmp(parser->current_token->value, "ՀԱՅ") == 0)
	{
		return parser_parse_variable_definition(parser, scope);
	}
	else if (strcmp(parser->current_token->value, "ԳՈՐԾԱՌՈՒՅԹ") == 0)
	{
		return parser_parse_function_definition(parser, scope);	
	}
	// else if (strcmp(parser->current_token->value, "ՎԵՐԱԴԱՐՁՐՈՒ") == 0)
	// {
	// 	return parser_parse_function_return(parser, scope);
	// }
	else
	{
		return parser_parse_variable(parser, scope);
	}
}
