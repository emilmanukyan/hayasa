#ifndef AST_H
#define AST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct AST_STRUCT
{
	enum {
		AST_VARIABLE_DEFINITION,
		AST_FUNCTION_DEFINITION,
		AST_VARIABLE,
		AST_VARIABLE_REASSIGNMENT,
		AST_FUNCTION_CALL,
		AST_FUNCTION_RETURN,
		AST_STRING,
		AST_NUMBER,
		AST_BOOL,
		AST_CONDITIONAL,
		AST_COMPOUND,
		AST_NOOP,
	} type;

	struct SCOPE_STRUCT* scope;

	/* AST_VARIABLE_DEFINITION */
	char* variable_definition_variable_name;
	struct AST_STRUCT* variable_definition_value;
	
	/* AST_FUNCTION_DEFINITION */
	struct AST_STRUCT* function_definition_body;
	char* function_definition_name;
	struct AST_STRUCT** function_definition_args;
	size_t function_definition_args_size;

	/* AST_VARIABLE */
	char* variable_name;

	/* AST_VARIABLE_REASSIGNMENT */
	char* variable_reassignment_name;
	struct AST_STRUCT* variable_reassignment_value;

	/* AST_FUNCTION_CALL */
	char* function_call_name;
	struct AST_STRUCT** function_call_arguments;
	size_t function_call_arguments_size;

	/* AST_FUNCTION_RETURN */
	struct AST_STRUCT* function_return_expr;

	/* AST_STRING */
	char* string_value;

	/* AST_NUMBER */
	long number_value;

	/* AST_ADD AST_SUB AST_DIV AST_MULT */
	struct AST_STRUCT* left_node;
	struct AST_STRUCT* right_node;

	/* AST_BOOL */
	bool bool_value;

	/* AST_CONDITIONAL */
	struct AST_STRUCT* conditional_condition;
	struct AST_STRUCT* conditional_consequence;
	struct AST_STRUCT* conditional_alternative;

	/* AST_COMPOUND */
	struct AST_STRUCT** compound_value;
	size_t compound_size;
} AST_T;

AST_T* init_ast(int type);

#endif
