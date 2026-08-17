#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if(isStackEmpty(undoStack))
    {
        printf("Nothing to undo\n");
        return;
    }
    Action action = popStack(undoStack);
    // if(strcmp(action.operation,"insert")==0)
    // {
    //     // reverse insert
    //     // deleteCharacters(editor, strlen(action.text));
        
    // }
    if(strcmp(action.operation,"insert") == 0)
    {
        int pos = action.cursorPos;
        int len = strlen(action.text);
        int deleteLen = len;
        if(editor->cursor->line[pos + len] == ' ')
        {
            deleteLen++;
        }
        int i = pos;
        int j = pos + deleteLen;

        while(editor->cursor->line[j] != '\0')
        {
            editor->cursor->line[i] = editor->cursor->line[j];
            i++;
            j++;
        }
        editor->cursor->line[i] = '\0';
        editor->cursorPos = pos;
        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
    }
    else if (strcmp(action.operation, "delete") == 0)
    {
        // 1. Save state AFTER deletion to push onto redoStack
        Action redoAction;
        strcpy(redoAction.operation, "delete");
        strcpy(redoAction.text, editor->cursor->line); // State AFTER deletion
        redoAction.cursorLine = editor->cursorLine;
        redoAction.cursorPos = editor->cursorPos;
        // 2. Restore state BEFORE deletion
        strcpy(editor->cursor->line, action.text);
        editor->cursorLine = action.cursorLine;
        editor->cursorPos = action.cursorPos;
        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
        // 3. Push to redoStack
        pushStack(redoStack, redoAction);
        return;
    }
    pushStack(redoStack, action);
}

void redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    if(isStackEmpty(redoStack))
    {
        printf("Nothing to redo\n");
        return;
    }

    Action action = popStack(redoStack);

    if(strcmp(action.operation, "insert") == 0)
    {
        int pos = action.cursorPos;
        int len = strlen(action.text);
        int currlen = strlen(editor->cursor->line);

        /* If line is empty */
        if(currlen == 0)
        {
            strcpy(editor->cursor->line, action.text);
            editor->cursorPos = len;
        }
        else
        {
            int i = currlen;

            while(i >= pos)
            {
                editor->cursor->line[i + len + 1] =
                    editor->cursor->line[i];
                i--;
            }

            for(i = 0; i < len; i++)
            {
                editor->cursor->line[pos + i] = action.text[i];
            }

            editor->cursor->line[pos + len] = ' ';

            editor->cursorPos = pos + len + 1;
        }

        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
    }
    else if (strcmp(action.operation, "delete") == 0)
    {
        // 1. Save state BEFORE deletion to push onto undoStack
        Action undoAction;
        strcpy(undoAction.operation, "delete");
        strcpy(undoAction.text, editor->cursor->line); // State BEFORE deletion
        undoAction.cursorLine = editor->cursorLine;
        undoAction.cursorPos = editor->cursorPos;
        // 2. Restore state AFTER deletion
        strcpy(editor->cursor->line, action.text);
        editor->cursorLine = action.cursorLine;
        editor->cursorPos = action.cursorPos;
        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
        // 3. Push to undoStack
        pushStack(undoStack, undoAction);
        return;
    }
    pushStack(undoStack, action);
}