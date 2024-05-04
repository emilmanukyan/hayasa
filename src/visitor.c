#include "include/visitor.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size)
{
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);

		switch(visited_ast->type)
		{
			case AST_STRING: printf("%s", visited_ast->string_value); break;
			default: printf("%p\n", visited_ast); break;
		}
	}
	return init_ast(AST_NOOP);
}

static AST_T* builtin_function_printl(visitor_T* visitor, AST_T** args, int args_size)
{
	// printf("%s\n", );
	for (int i = 0; i < args_size; i++)
	{
		AST_T* visited_ast = visitor_visit(visitor, args[i]);
		switch(visited_ast->type)
		{
			case AST_STRING: printf("%s", visited_ast->string_value); break;
			default: printf("%s", visited_ast->string_value); break;
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
			default: printf("%p\n", visited_ast); break;
		}
	}
	return init_ast(AST_NOOP);
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
		case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
		case AST_FUNCTION_RETURN: return visitor_visit_function_return(visitor, node); break;
		case AST_STRING: return visitor_visit_string(visitor, node); break;
		case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
		case AST_NOOP: return node; break;
	}

	//printf("Uncaught statement of type `%d`\n", node->type);
	printf("======= ՍԽԱԼ =======\n");
	printf("«%d» տիպին պատկանող անհայտ օպերատոր:\n", node->type);
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
    scope_T* current_scope = visitor->scope; // Use visitor's scope instead of node's scope
    AST_T* vdef = NULL;

    while (current_scope != NULL)
    {
        vdef = scope_get_variable_definition(current_scope, node->variable_name);
        if (vdef != NULL)
            break;
        current_scope = current_scope->parent;
    }

    if (vdef != NULL)
    {
        return visitor_visit(visitor, vdef->variable_definition_value);
    }

    printf("======= ՍԽԱԼ =======\n");
    printf("Անհայտ փոփոխական` «%s» անունով:\n", node->variable_name);
    exit(1);
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node)
{
    // Create a new scope for this function call
    scope_T* function_scope = init_scope();
    function_scope->parent = visitor->scope;

    if (strcmp(node->function_call_name, "ՏՊԻՐ") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }
    else if (strcmp(node->function_call_name, "ՏՊԻՐՏՈՂ") == 0)
    {
        return builtin_function_printl(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }
    else if (strcmp(node->function_call_name, "ՏՊԻՐՆՏՈՂ") == 0)
    {
        return builtin_function_printnl(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    AST_T* fdef = scope_get_function_definition(
        visitor->scope,
        node->function_call_name
    );

    if (fdef == NULL)
    {
        printf("======= ՍԽԱԼ =======\n");
        printf("Անհայտ գործառույթ` «%s» անունով:\n", node->function_call_name);
        exit(1);
    }

    // Create a new scope for the function body
    visitor->scope = function_scope;

    if (fdef->function_definition_args_size > 0)
    {
        if (fdef->function_definition_args_size != node->function_call_arguments_size)
        {
            printf("======= ՍԽԱԼ =======\n");
            printf("«%s» անունով գործառույթի սխալ արգումենտների քանակ:\n", node->function_call_name);
            exit(1);
        }
        for (int i = 0; i < (int)fdef->function_definition_args_size; i++)
        {
            // Get the variable from the function definition
            AST_T* ast_var = (AST_T*)fdef->function_definition_args[i];

            // Get the value of the argument passed to the function
            AST_T* ast_value = (AST_T*)node->function_call_arguments[i];

            // Create a new variable definition with the argument value
            AST_T* ast_vardef = init_ast(AST_VARIABLE_DEFINITION);
            ast_vardef->variable_definition_value = ast_value;
            ast_vardef->variable_definition_variable_name = (char*)calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
            strcpy(ast_vardef->variable_definition_variable_name, ast_var->variable_name);

            // Push the variable definition into the function body scope
            scope_add_variable_definition(function_scope, ast_vardef);
        }
    }

    // Visit the function body with the new scope
    AST_T* result = visitor_visit(visitor, fdef->function_definition_body);

    // Restore the original scope
    visitor->scope = function_scope->parent;

    // Free the memory allocated for the function scope
    free(function_scope);

    return result;
}

AST_T* visitor_visit_function_return(visitor_T* visitor, AST_T* node)
{
	// ========================================================================
	// ========================== Շարունակելի =================================
	// ========================================================================

	// // AST_T* visited_ast = visitor_visit(visitor, node);
    // // AST_T* function_return = init_ast(AST_FUNCTION_RETURN);
    // // function_return->function_return_expr = visitor_visit(visitor, node);
    // // function_return->scope = node->scope;

	// // return function_return;

	// printf("here we are\n");
	// return node;

	AST_T* function_return = init_ast(AST_FUNCTION_RETURN);
    function_return->function_return_expr = visitor_visit(visitor, node->function_return_expr);
    
    function_return->scope = node->scope;

    return function_return;
}


AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node)
{
	return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node)
{
	for (int i = 0; i < node->compound_size; i++)
	{
		visitor_visit(visitor, node->compound_value[i]);
	}

	return init_ast(AST_NOOP);
}
