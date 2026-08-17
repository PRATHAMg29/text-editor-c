#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void delete(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{ 
    again: 
    printf("\nHow do you want to perform delete operation : \n"); 
    printf("1. Delete characters\n2. Delete line\n"); 
    printf("Enter option : "); 
    int option; 
    scanf("%d", &option); 
    if(option == 1) 
    { 
        printf("Enter number of characters to delete : "); 
        int len; 
        scanf("%d", &len); 
        while(getchar() != '\n'); 
        /* * Store the text that is going to be deleted * BEFORE deleting it. */ 
        // Action action; 
        // strcpy(action.operation, "delete"); 
        // action.cursorLine = editor->cursorLine; 
        // action.cursorPos = editor->cursorPos; 
        // /* * If deleting fewer characters than cursor position, * save only those characters. */ 
        // if(len < editor->cursorPos) 
        // { 
        //     int start = editor->cursorPos - len; 
        //     /* * If the character before the deletion area is a space, * your deleteCharacters() also removes that space. 
        //     * Therefore include it in the saved text. */ 
        //     if(start > 0 && editor->cursor->line[start - 1] == ' ') 
        //     { 
        //         start--; 
        //     } 
        //     strcpy(action.text, editor->cursor->line + start); 
        // } 
        // else 
        // {
        //     strcpy(action.text, editor->cursor->line); 
        // } 
        // deleteCharacters(editor, len);  
        // pushStack(undoStack, action);  
        // redoStack->size = 0; 
        // return;
        Action action;
        strcpy(action.operation, "delete");
        strcpy(action.text, editor->cursor->line);
        action.cursorLine = editor->cursorLine;
        action.cursorPos = editor->cursorPos;
        int oldCursorPos = editor->cursorPos;
        deleteCharacters(editor, len);
        action.cursorPos = oldCursorPos;
        pushStack(undoStack, action);
        redoStack->size = 0;
        return;
    } 
    else if(option == 2) 
    {
        while(getchar() != '\n'); 
        Action action; 
        strcpy(action.operation, "delete"); 
        strcpy(action.text, editor->cursor->line); 
        action.cursorLine = editor->cursorLine; 
        action.cursorPos = editor->cursorPos; 
        deleteLine(editor); 
        pushStack(undoStack, action); 
        redoStack->size = 0; 
        return; 
    } 
    else 
    { 
        printf("Invalid option.\n"); 
        goto again; 
    } 
}

void deleteCharacters(TextEditor *editor, int length)
{
    if(editor->cursor == NULL)
    {
        return;
    }

    if(length <= 0)
    {
        return;
    }

    if(length > editor->cursorPos)
    {
        length = editor->cursorPos;
    }

    if(editor->cursor->line[editor->cursorPos - 1] == ' ')
    {
        editor->cursorPos--;
    }
    int i = editor->cursorPos - length;
    int j = editor->cursorPos;
    while(editor->cursor->line[j] != '\0')
    {
        editor->cursor->line[i] = editor->cursor->line[j];
        i++;
        j++;
    }
    editor->cursor->line[i] = '\0';
    editor->cursorPos = editor->cursorPos - length;

    if(editor->cursorPos > 0 && editor->cursor->line[editor->cursorPos - 1] == ' ')
    {
        i = editor->cursorPos - 1;
        j = editor->cursorPos;
        while(editor->cursor->line[j] != '\0')
        {
            editor->cursor->line[i] = editor->cursor->line[j];
            i++;
            j++;
        }
        editor->cursor->line[i] = '\0';
        editor->cursorPos--;
    }
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void deleteLine(TextEditor *editor)
{
    editor->cursor->line[0] = '\0';
    editor->cursorPos = 0;
    return;
}