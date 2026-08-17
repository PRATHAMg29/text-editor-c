#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void pushStack(DynamicArrayStack *stack, Action action)
{
    if(stack->size == stack->capacity)
    {
        stack->capacity = stack->capacity * 2;
        Action *temp = realloc(stack->actions, stack->capacity * sizeof(Action));
        if(temp == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        stack->actions = temp;
    }
    stack->actions[stack->size] = action;
    stack->size++;
}

Action popStack(DynamicArrayStack *stack)
{
    Action action;
    if(stack->size == 0)
    {
        strcpy(action.operation, "");
        return action;
    }
    stack->size--;
    return stack->actions[stack->size];
}

int isStackEmpty(DynamicArrayStack *stack)
{
    if(stack->size == 0)
    {
        return 1;
    }
    return 0;
}