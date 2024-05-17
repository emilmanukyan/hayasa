#include "include/visitor.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>

// Տպելու գործողություններ

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size)
{
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);

		switch(visited_ast->type)
		{
			case AST_STRING: printf("%s", visited_ast->string_value); break;
			case AST_NUMBER: printf("%ld", visited_ast->number_value); break;
			case AST_BOOL:
				if (visited_ast->bool_value == true) visited_ast->string_value = "ՃՇՄԱՐԻՏ";
				else visited_ast->string_value = "ԿԵՂԾ";
				printf("%s", visited_ast->string_value);
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ՏՊԻՐ` անունով գործառույթի սխալ արգումենտների քանակ:\n");
	        	exit(1);
	        	break;
		}
	}
	return init_ast(AST_NOOP);
}

static AST_T* builtin_function_printl(visitor_T* visitor, AST_T** args, int args_size)
{
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		// printf("%d\n", args[i]->type);
		// printf("%s\n", args[i]->function_call_name);
		// printf("%s\n", visited_ast->variable_name);
		// AST_T* result_ast;
		// if (visited_ast->type == AST_NOOP)
        // {
        //     result_ast = init_ast();
        // }
		switch(visited_ast->type)
		{
			case AST_STRING: printf("%s", visited_ast->string_value); break;
			case AST_NUMBER: printf("%ld", visited_ast->number_value); break;
			case AST_BOOL:
				if (visited_ast->bool_value == true) visited_ast->string_value = "ՃՇՄԱՐԻՏ";
				else visited_ast->string_value = "ԿԵՂԾ";
				printf("%s", visited_ast->string_value);
				break;
			// case AST_NOOP:  break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ՏՊԻՐՏՈՂ` անունով գործառույթի սխալ արգումենտների քանակ:\n");
	        	exit(1);
	        	break;
		}
	}
	printf("\n");
	return init_ast(AST_NOOP);
}

static AST_T* builtin_function_printnl(visitor_T* visitor, AST_T** args, int args_size)
{
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);

		switch(visited_ast->type)
		{
			case AST_STRING: printf("%s\n", visited_ast->string_value); break;
			case AST_NUMBER: printf("%ld\n", visited_ast->number_value); break;
			case AST_BOOL:
				if (visited_ast->bool_value == true) visited_ast->string_value = "ՃՇՄԱՐԻՏ";
				else visited_ast->string_value = "ԿԵՂԾ";
				printf("%s\n", visited_ast->string_value);
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ՏՊԻՐՆՏՈՂ` անունով գործառույթի սխալ արգումենտների քանակ:\n");
	        	exit(1);
	        	break;
		}
	}
	return init_ast(AST_NOOP);
}

// Թվաբանական գործողություններ

static AST_T* builtin_function_add(visitor_T* visitor, AST_T** args, int args_size)
{
	AST_T* result_ast = init_ast(AST_NUMBER);
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_NUMBER:
				result_ast->number_value += visited_ast->number_value;
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ԳՈՒՄԱՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	        	exit(1);
	        	break;
		}
	}
	return result_ast;
}

static AST_T* builtin_function_sub(visitor_T* visitor, AST_T** args, int args_size)
{
	AST_T* result_ast = init_ast(AST_NUMBER);
	AST_T* visited_ast = visitor_visit(visitor, args[0]);
	result_ast->number_value = visited_ast->number_value;
	for (int i = 1; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_NUMBER:
				result_ast->number_value -= visited_ast->number_value;
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ՏԱՐԲԵՐՈՒԹՅՈՒՆ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	        	exit(1);
	        	break;
		}
	}
	return result_ast;
}

static AST_T* builtin_function_mult(visitor_T* visitor, AST_T** args, int args_size)
{
	AST_T* result_ast = init_ast(AST_NUMBER);
	AST_T* visited_ast = visitor_visit(visitor, args[0]);
	result_ast->number_value = visited_ast->number_value;
	for (int i = 1; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_NUMBER:
				result_ast->number_value *= visited_ast->number_value;
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ԱՐՏԱԴՐՅԱԼ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	        	exit(1);
	        	break;
		}
	}
	return result_ast;
}

static AST_T* builtin_function_div(visitor_T* visitor, AST_T** args, int args_size)
{
	AST_T* result_ast = init_ast(AST_NUMBER);
	AST_T* visited_ast = visitor_visit(visitor, args[0]);
	result_ast->number_value = visited_ast->number_value;
	for (int i = 1; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_NUMBER:
				if (visited_ast->number_value == 0)
				{
					printf("\n======= ՍԽԱԼ =======\n");
					printf("Թիվը `0`-ի բաժանման փորձ։\n");
					exit(1);
				}
				result_ast->number_value /= visited_ast->number_value;
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ԲԱԺԱՆՈՒՄ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	        	exit(1);
	        	break;
		}
	}
	return result_ast;
}

static AST_T* builtin_function_mod(visitor_T* visitor, AST_T** args, int args_size)
{
	AST_T* result_ast = init_ast(AST_NUMBER);
	AST_T* visited_ast = visitor_visit(visitor, args[0]);
	result_ast->number_value = visited_ast->number_value;
	for (int i = 1; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_NUMBER:
				if (visited_ast->number_value == 0)
				{
					printf("\n======= ՍԽԱԼ =======\n");
					printf("Թիվը `0`-ի բաժանման փորձ։\n");
					exit(1);
				}
				result_ast->number_value %= visited_ast->number_value;
				break;
			default:
				printf("\n======= ՍԽԱԼ =======\n");
        		printf("`ՄՆԱՑՈՐԴ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	        	exit(1);
	        	break;
		}
	}
	return result_ast;
}

// Համեմատական գործողություններ

static AST_T* builtin_function_equal(visitor_T* visitor, AST_T** args, int args_size)
{
	if (args_size > 2)
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("`ՀԱՎԱՍԱՐ` անունով գործառույթին փոխանցված սխալ արգումենտների քանակ:\n");
		exit(1);
	}
	AST_T* result_ast = init_ast(AST_BOOL);
	AST_T* first_operand = visitor_visit(visitor, args[0]);
	AST_T* second_operand = visitor_visit(visitor, args[1]);
	// if (first_operand->type != second_operand->type)
	// {
	// 	printf("\n======= ՍԽԱԼ =======\n");
	// 	printf("`ՀԱՎԱՍԱՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	// 	exit(1);
	// }
	switch(first_operand->type)
	{
		case AST_STRING:
			result_ast->bool_value = strcmp(first_operand->string_value, second_operand->string_value) == 0;
			break;
		case AST_NUMBER:
			result_ast->bool_value = first_operand->number_value == second_operand->number_value;
			break;
		case AST_BOOL:
			result_ast->bool_value = first_operand->bool_value == second_operand->bool_value;
			break;
		default:
			printf("\n======= ՍԽԱԼ =======\n");
			printf("`ՀԱՎԱՍԱՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
			exit(1);
			break;
	}
	return result_ast;
}

static AST_T* builtin_function_greater(visitor_T* visitor, AST_T** args, int args_size)
{
	if (args_size > 2)
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("`ՄԵԾ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
		exit(1);
	}
	AST_T* result_ast = init_ast(AST_BOOL);
	AST_T* first_operand = visitor_visit(visitor, args[0]);
	AST_T* second_operand = visitor_visit(visitor, args[1]);
	// if (first_operand->type != second_operand->type)
	// {
	// 	printf("\n======= ՍԽԱԼ =======\n");
	// 	printf("`ՄԵԾ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
	// 	exit(1);
	// }
	switch(first_operand->type)
	{
		case AST_STRING:
			result_ast->bool_value = strcmp(first_operand->string_value, second_operand->string_value) > 0;
			break;
		case AST_NUMBER:
			result_ast->bool_value = first_operand->number_value > second_operand->number_value;
			break;
		case AST_BOOL:
			result_ast->bool_value = first_operand->bool_value > second_operand->bool_value;
			break;
		default:
			printf("\n======= ՍԽԱԼ =======\n");
			printf("`ՄԵԾ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
			exit(1);
			break;
	}
	return result_ast;
}

static AST_T* builtin_function_less(visitor_T* visitor, AST_T** args, int args_size)
{
	if (args_size > 2)
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("`ՓՈՔՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
		exit(1);
	}
	AST_T* result_ast = init_ast(AST_BOOL);
	AST_T* first_operand = visitor_visit(visitor, args[0]);
	AST_T* second_operand = visitor_visit(visitor, args[1]);
	if (first_operand->type != second_operand->type)
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("`ՓՈՔՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
		exit(1);
	}
	switch(first_operand->type)
	{
		case AST_STRING:
			result_ast->bool_value = strcmp(first_operand->string_value, second_operand->string_value) < 0;
			break;
		case AST_NUMBER:
			result_ast->bool_value = first_operand->number_value < second_operand->number_value;
			break;
		case AST_BOOL:
			result_ast->bool_value = first_operand->bool_value < second_operand->bool_value;
			break;
		default:
			printf("\n======= ՍԽԱԼ =======\n");
			printf("`ՓՈՔՐ` անունով գործառույթին փոխանցված սխալ արգումենտներ:\n");
			exit(1);
			break;
	}
	return result_ast;
}

// Գործառույթի արժեքի վերադարձ

static AST_T* builtin_function_return(visitor_T* visitor, AST_T** args, int args_size)
{
    if (args_size != 1)
    {
        printf("\n======= ՍԽԱԼ =======\n");
        printf("`ՎԵՐԱԴԱՐՁՐՈՒ` անունով գործառույթին փոխանցված է մեկից ավելի արգումենտ։\n");
        exit(1);
    }

    AST_T* result_ast = visitor_visit(visitor, args[0]);
    builtin_function_printl(visitor, args, args_size);
    return result_ast;
}


visitor_T* init_visitor()
{
	visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
	visitor->scope = init_scope();

	return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node)
{
	switch (node->type)
	{
		case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node); break;
		case AST_FUNCTION_DEFINITION: return visitor_visit_function_definition(visitor, node); break;
		case AST_VARIABLE: return visitor_visit_variable(visitor, node); break;
		case AST_VARIABLE_REASSIGNMENT: visitor_visit_variable(visitor,node); break;
		case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
		case AST_STRING: return visitor_visit_string(visitor, node); break;
		case AST_NUMBER: return visitor_visit_number(visitor, node); break;
		case AST_BOOL: return visitor_visit_boolean(visitor, node); break;
		case AST_CONDITIONAL: return visitor_visit_condition(visitor, node); break;
		case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
		case AST_NOOP: return node; break;
	}
	printf("\n======= ՍԽԱԼ =======\n");
	printf("`%d` տիպին պատկանող անհայտ օպերատոր:\n", node->type);
	exit(1);
	
	return init_ast(AST_NOOP);
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node)
{
	scope_add_variable_definition(
		visitor->scope,
		node
	);

	return node;
}

AST_T* visitor_visit_function_definition(visitor_T* visitor, AST_T* node)
{
	scope_add_function_definition(
		visitor->scope,
		node
	);

	node->scope = visitor->scope;

	return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node)
{
	scope_T* current_scope = visitor->scope;
	AST_T* vdef = NULL;

	while (current_scope != NULL)
	{
	    vdef = scope_get_variable_definition(current_scope, node->variable_name);
	    if (vdef != NULL)
	        break;
	    current_scope = current_scope->parent;
	}

    if (current_scope == NULL)
    {
        printf("\n======= ՍԽԱԼ =======\n");
        printf("Անհայտ փոփոխական `%s` անունով:\n", node->variable_name);
        exit(1);
    }

    if (vdef != NULL)
    {
        if (vdef->type == AST_VARIABLE_DEFINITION)
        {
            return visitor_visit(visitor, vdef->variable_definition_value);
        }
        else if (vdef->type == AST_VARIABLE_REASSIGNMENT)
        {
        	printf("%s\n", vdef->variable_name);
            AST_T* expr = visitor_visit(visitor, vdef->variable_reassignment_value);
            scope_add_variable_definition(visitor->scope, node);
            // scope_reassign_variable(visitor->scope, node->variable_name, expr);
            return expr;
        }
    }

    printf("\n======= ՍԽԱԼ =======\n");
    printf("Անհայտ փոփոխական `%s` անունով:\n", node->variable_name);
    exit(1);
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node)
{
    scope_T* function_scope = init_scope();
    function_scope->parent = visitor->scope;

    if (strcmp(node->function_call_name, "ՏՊԻՐ") == 0)
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    else if (strcmp(node->function_call_name, "ՏՊԻՐՏՈՂ") == 0)
        return builtin_function_printl(visitor, node->function_call_arguments, node->function_call_arguments_size);
    else if (strcmp(node->function_call_name, "ՏՊԻՐՆՏՈՂ") == 0)
        return builtin_function_printnl(visitor, node->function_call_arguments, node->function_call_arguments_size);
    else if (strcmp(node->function_call_name, "ԳՈՒՄԱՐ") == 0)
        return builtin_function_add(visitor, node->function_call_arguments, node->function_call_arguments_size);
    else if (strcmp(node->function_call_name, "ՏԱՐԲԵՐՈՒԹՅՈՒՆ") == 0)
        return builtin_function_sub(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ԱՐՏԱԴՐՅԱԼ") == 0)
        return builtin_function_mult(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ԲԱԺԱՆՈՒՄ") == 0)
        return builtin_function_div(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ՄՆԱՑՈՐԴ") == 0)
        return builtin_function_mod(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ՀԱՎԱՍԱՐ") == 0)
        return builtin_function_equal(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ՄԵԾ") == 0)
        return builtin_function_greater(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ՓՈՔՐ") == 0)
        return builtin_function_less(visitor, node->function_call_arguments, node->function_call_arguments_size);
	else if (strcmp(node->function_call_name, "ՎԵՐԱԴԱՐՁՐՈՒ") == 0)
        return builtin_function_return(visitor, node->function_call_arguments, node->function_call_arguments_size);


    AST_T* fdef = scope_get_function_definition(
        visitor->scope,
        node->function_call_name
    );

    if (fdef == NULL)
    {
        printf("\n======= ՍԽԱԼ =======\n");
        printf("Անհայտ գործառույթ `%s` անունով:\n", node->function_call_name);
        exit(1);
    }

    visitor->scope = function_scope;

    if (fdef->function_definition_args_size > 0)
    {
        if (fdef->function_definition_args_size != node->function_call_arguments_size)
        {
            printf("\n======= ՍԽԱԼ =======\n");
            printf("`%s` անունով գործառույթի սխալ արգումենտների քանակ:\n", node->function_call_name);
            exit(1);
        }
        for (int i = 0; i < (int)fdef->function_definition_args_size; i++)
        {
            AST_T* ast_var = (AST_T*)fdef->function_definition_args[i];

            AST_T* ast_value = (AST_T*)node->function_call_arguments[i];

            if (ast_value->type == AST_VARIABLE)
                ast_value = visitor_visit_variable(visitor, ast_value);

            AST_T* ast_vardef = init_ast(AST_VARIABLE_DEFINITION);

            ast_vardef->variable_definition_value = ast_value;
            ast_vardef->variable_definition_variable_name = (char*)calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
            strcpy(ast_vardef->variable_definition_variable_name, ast_var->variable_name);

            scope_add_variable_definition(function_scope, ast_vardef);
        }
    }

    AST_T* result = visitor_visit(visitor, fdef->function_definition_body);

    visitor->scope = function_scope->parent;

    free(function_scope);

    return result;
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node)
{
	return node;
}

AST_T* visitor_visit_number(visitor_T* visitor, AST_T* node)
{
	return node;
}

AST_T* visitor_visit_boolean(visitor_T* visitor, AST_T* node)
{
	return node;
}

AST_T* visitor_visit_condition(visitor_T* visitor, AST_T* node)
{
    AST_T* visited_condition = visitor_visit(visitor, node->conditional_condition);

	if (visited_condition->type != AST_BOOL)
	{
		printf("\n======= ՍԽԱԼ =======\n");
		printf("Պայմանի կառուցվածքի անվավեր տիպ։\n");
		exit(1);
	}

	if (visited_condition->bool_value == true)
	{
		return visitor_visit(visitor, node->conditional_consequence);
	}
	else if (node->conditional_alternative != NULL)
	{
		return visitor_visit(visitor, node->conditional_alternative);
	}

	return init_ast(AST_NOOP);
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node)
{
	for (int i = 0; i < node->compound_size; i++)
	{
		visitor_visit(visitor, node->compound_value[i]);
	}

	return init_ast(AST_NOOP);
}
