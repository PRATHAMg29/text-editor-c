#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void displayText(TextEditor *editor)
{
    Node *temp = editor->head;
    int i=1;
    while(temp != NULL)
    {
        printf("%d. %s\n",i++,temp->line);
        temp = temp->next;
    }
    printf("\n");
}

void showCursorPosition(TextEditor *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        printf("Cursor position: Line 0, Position 0 (File is empty)\n");
        return;
    }
    printf("Cursor Line : %d\n", editor->cursorLine);
    printf("Cursor Pos  : %d\n", editor->cursorPos);
}