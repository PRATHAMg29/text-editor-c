#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
#include "text_editor.h"

void saveFile(TextEditor *editor, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        perror("Error opening file for saving");
        return;
    }

    Node *temp = editor->head;
    while (temp != NULL) 
    {
        fprintf(file, "%s\n", temp->line);
        temp = temp->next;
    }

    fclose(file);
    printf("File saved successfully as '%s'.\n", filename);
}

void openFile(TextEditor *editor, const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Creating new session for file: %s\n", filename);
        return;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        Node *newNode = createNode(buffer);
        if (newNode != NULL) 
        {
            appendNode(editor, newNode);
        }
    }

    fclose(file);
    printf("File '%s' loaded successfully.\n", filename);
}

void closeFile(TextEditor *editor) 
{
    Node *curr = editor->head;
    while (curr != NULL) 
    {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    editor->head = editor->tail = editor->cursor = NULL;
    editor->cursorLine = 0;
    editor->cursorPos = 0;
}