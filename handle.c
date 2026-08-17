#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void handleCommand(TextEditor *editor, char command[], DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{
    Action action;
    char first_command[50], second_command[100];
    int i=0;
    while(command[i] != ' ' && command[i] != '\0' && command[i] != '\t')
    {
        first_command[i] = command[i];
        i++;
    }
    first_command[i] = '\0';
    int count = 0;
    if(command[i] != '\0')
    {
        while(command[i] == ' ' || command[i] == '\t')
            i++;
    }
    while(command[i] != '\0')
    {
        second_command[count] = command[i];
        i++;
        count++;
    }
    second_command[count] = '\0';
    if(strcmp(first_command,"insert") == 0)
    {
        // insertText(editor,second_command);
        if(count == 0)
        {
            // insertText(editor, NULL);
            // strcpy(action.operation, first_command);
            // strcpy(action.text,"");
            // action.cursorLine = editor->cursorLine;
            // action.cursorPos = editor->cursorPos;
            // pushStack(undoStack,action);
            // redoStack->size = 0;
            int oldCursorPos = editor->cursorPos;
            insertText(editor, second_command);
            strcpy(action.operation, first_command);
            strcpy(action.text, second_command);
            action.cursorLine = editor->cursorLine;
            action.cursorPos = oldCursorPos;
        }
        else
        {
            int oldCursorPos = editor->cursorPos;
            insertText(editor, second_command);
            strcpy(action.operation, first_command);
            strcpy(action.text, second_command);
            action.cursorLine = editor->cursorLine;
            action.cursorPos = oldCursorPos;
//             printf("ACTION: %s\n", action.operation);
// printf("ACTION TEXT: %s\n", action.text);
// printf("ACTION CURSOR POS: %d\n", action.cursorPos);
            pushStack(undoStack,action);
            redoStack->size = 0;
        }
            
    }
    else if(strcmp(first_command,"delete") == 0)
    {
        delete(editor, undoStack, redoStack);
    }
    else if(strcmp(first_command,"print") == 0)
    {
        // printf("Print command deteteced.\n");
        displayText(editor);
    }
    else if(strcmp(first_command,"undo") == 0)
    {
        // printf("Undo command deteteced.\n");
        undo(editor, undoStack, redoStack);
    }
    else if(strcmp(first_command, "redo") == 0)
    {
        redo(editor, undoStack, redoStack);
    }
    else if(strcmp(first_command,"cursor") == 0)
    {
        cursor_navigation(editor);
    }
    else if(strcmp(first_command,"clear") == 0)
    {
        printf("Clear command deteteced.\n");
        system("clear");
    }
}

void insertText(TextEditor *editor, char *text)
{
    if(editor->head == NULL)
    {
        Node *newNode = createNode(text);

        if(newNode == NULL)
        {
            return;
        }

        appendNode(editor, newNode);

        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
        return;
    }

    if(text == NULL || strlen(text) == 0)
    {
        Node *newNode = createNode("");

        if(newNode == NULL)
        {
            return;
        }

        appendNode(editor, newNode);

        printf("CursorLine : %d\n", editor->cursorLine);
        printf("Cursor Pos : %d\n", editor->cursorPos);
        return;
    }

    int currlen = strlen(editor->cursor->line);
    int len = strlen(text);
    if(editor->cursorPos == currlen)
    {
        editor->cursor->line[currlen] = ' ';
        currlen++;
        int i = 0;
        while(i < len)
        {
            editor->cursor->line[currlen] = text[i];
            currlen++;
            i++;
        }
        editor->cursorPos = currlen;
    }
    else if(editor->cursorPos == 0)
    {
        int i = currlen;
        while(i >= 0)
        {
            editor->cursor->line[i + len + 1] =
                editor->cursor->line[i];

            i--;
        }
        i = 0;
        while(i < len)
        {
            editor->cursor->line[i] = text[i];
            i++;
        }
        editor->cursor->line[len] = ' ';
        editor->cursorPos = len + 1;
    }
    else
    {
        int i = currlen;
        while(i >= editor->cursorPos)
        {
            editor->cursor->line[i + len + 1] = editor->cursor->line[i];
            i--;
        }
        i = 0;
        while(i < len)
        {
            editor->cursor->line[editor->cursorPos] = text[i];
            editor->cursorPos++;
            i++;
        }
        editor->cursor->line[editor->cursorPos] = ' ';
        editor->cursorPos++;
    }
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}