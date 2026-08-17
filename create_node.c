#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

Node *createNode(char *text)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
    {
        perror("malloc");
        return NULL;
    }
    if (text != NULL)
    {
        strcpy(new->line, text);    
    }
    else
    {
        new->line[0] = '\0';
    }
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void appendNode(TextEditor *editor, Node *new)
{
    if(editor->head == NULL && editor->tail == NULL)
    {
        editor->head = editor->tail = new;
        editor->cursor = editor->head;
        editor->cursorLine = 1;
        editor->cursorPos = strlen(new->line);
        return;
    }
    else
    {
        editor->tail->next = new;
        new->prev = editor->tail;
        editor->tail = new;
        editor->cursor = new;
        editor->cursorLine++;
        editor->cursorPos = strlen(new->line);
        return;
    }
}