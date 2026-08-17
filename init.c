#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void init(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;
    editor->cursorLine = 0;
    editor->cursorPos = 0;

    initStack(undoStack);
    initStack(redoStack);
}

void initStack(DynamicArrayStack *stack)
{
    stack->actions = malloc(INITIAL_CAPACITY * sizeof(Action));
    if(stack->actions == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
}