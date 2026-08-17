#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void cursor_navigation(TextEditor *editor)
{
    printf("CURSOR NAVIGATION MENU\n");
    printf("1. Move cursor up\n");
    printf("2. Move cursor down\n");
    printf("3. Move cursor left\n");
    printf("4. Move cursor right\n");
    printf("5. Jump cursor to start of file\n");
    printf("6. Jump cursor to end of file\n");
    printf("7. Jump cursor to start of line\n");
    printf("8. Jump cursor to end of line\n");
    int option;
    printf("Enter your option : ");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        { 
            moveCursorUp(editor);
            break;
        }
        case 2:
        { 
            moveCursorDown(editor);
            break;
        }
        case 3:
        { 
            moveCursorLeft(editor);
            break;
        }
        case 4:
        { 
            moveCursorRight(editor);
            break;
        }
        case 5:
        { 
            jumpToStartOfFile(editor);
            break;
        }
        case 6:
        { 
            jumpToEndOfFile(editor);
            break;
        }
        case 7:
        { 
            jumpToStartOfLine(editor);
            break;
        }
        case 8:
        { 
            jumpToEndOfLine(editor);
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
    while(getchar() != '\n');
}
void moveCursorUp(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL || editor->cursor->prev == NULL)
    {
        printf("Already at the top line.\n");
        return;
    }

    // Move to previous line
    editor->cursor = editor->cursor->prev;
    editor->cursorLine--;

    // Edge case: If target line is shorter than current cursorPos, clamp to target line length
    int lineLen = strlen(editor->cursor->line);
    if (editor->cursorPos > lineLen)
    {
        editor->cursorPos = lineLen;
    }

    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void moveCursorDown(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL || editor->cursor->next == NULL)
    {
        printf("Already at the bottom line.\n");
        return;
    }

    // Move to next line
    editor->cursor = editor->cursor->next;
    editor->cursorLine++;

    // Edge case: If target line is shorter than current cursorPos, clamp to target line length
    int lineLen = strlen(editor->cursor->line);
    if (editor->cursorPos > lineLen)
    {
        editor->cursorPos = lineLen;
    }

    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void moveCursorLeft(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        return;
    }

    if (editor->cursorPos > 0)
    {
        editor->cursorPos--;
    }
    else if (editor->cursor->prev != NULL)
    {
        // Edge case: At start of line, wrap to end of previous line
        editor->cursor = editor->cursor->prev;
        editor->cursorLine--;
        editor->cursorPos = strlen(editor->cursor->line);
    }
    else
    {
        printf("Already at the beginning of the file.\n");
        return;
    }
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void moveCursorRight(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        return;
    }

    int lineLen = strlen(editor->cursor->line);

    if (editor->cursorPos < lineLen)
    {
        editor->cursorPos++;
    }
    else if (editor->cursor->next != NULL)
    {
        // Edge case: At end of line, wrap to start of next line
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;
        editor->cursorPos = 0;
    }
    else
    {
        printf("Already at the end of the file.\n");
        return;
    }
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void jumpToStartOfFile(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        return;
    }
    // Traverse to the first line node
    while (editor->cursor->prev != NULL)
    {
        editor->cursor = editor->cursor->prev;
    }
    editor->cursorLine = 1;
    editor->cursorPos = 0;
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}

void jumpToEndOfFile(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        return;
    }
    // Traverse to the last line node while updating line count
    while (editor->cursor->next != NULL)
    {
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;
    }
    editor->cursorPos = strlen(editor->cursor->line);
    printf("CursorLine : %d\n", editor->cursorLine);
    printf("Cursor Pos : %d\n", editor->cursorPos);
}
void jumpToStartOfLine(TextEditor *editor)
{
    editor->cursorPos = 0;
    printf("CursorLine : %d\n",editor->cursorLine);
    printf("Cursor Pos : %d\n",editor->cursorPos);
}
void jumpToEndOfLine(TextEditor *editor)
{
    int len = strlen(editor->cursor->line);
    editor->cursorPos = len;
    printf("CursorLine : %d\n",editor->cursorLine);
    printf("Cursor Pos : %d\n",editor->cursorPos);
}