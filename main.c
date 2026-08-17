
#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"

int main(int argc, char *argv[])
{
    // Initialize the text editor and stacks
    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;
    TextEditor editor;

    init(&editor, &undoStack, &redoStack);

    // User interaction loop
    char filename[100] = "";

    // If filename was provided as CLA (e.g. ./a.out myfile.txt)
    if (argc > 1) 
    {
        strcpy(filename, argv[1]);
        openFile(&editor, filename);
    }
    char command[256];

    while (1) 
    {
        printMenu();
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
         //TODO Remove newline character
        command[strcspn(command,"\n")] = '\0';
        if (strcmp(command, "exit") == 0) 
        {
            char choice[10];
            printf("Do you want to save and exit? (yes/no): ");
            fgets(choice, sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = '\0';

            if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 0) 
            {
                if (strlen(filename) == 0) 
                {
                    printf("Enter filename: ");
                    fgets(filename, sizeof(filename), stdin);
                    filename[strcspn(filename, "\n")] = '\0';
                }
                saveFile(&editor, filename);
            }
            closeFile(&editor);
            free(undoStack.actions);
            free(redoStack.actions);
            break;
        } 
        else 
        {
            handleCommand(&editor, command, &undoStack, &redoStack);
            // printf("Hello.\n");
        }
    }
    return 0;
}

void printMenu() 
{
    printf("\nText Editor Commands:\n");
    printf("1. insert <text> - Insert text at the current cursor position\n");
    printf("2. delete <num_chars> - Delete a number of characters from the current cursor position\n");
    printf("3. undo - Undo the last operation\n");
    printf("4. redo - Redo the last undone operation\n");
    printf("5. cursor - Cursor Navigations\n");
    printf("6. print - Print the current state of the text editor\n");
    printf("7. exit - Exit the text editor\n");
}
