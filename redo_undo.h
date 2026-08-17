#include "text_editor.h"
// Stack operations
void initStack(DynamicArrayStack *stack);
void pushStack(DynamicArrayStack *stack, Action action);
Action popStack(DynamicArrayStack *stack);
int isStackEmpty(DynamicArrayStack *stack);

// Undo/redo operations
void undo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
void redo(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
// Utility functions
void init(TextEditor *, DynamicArrayStack *, DynamicArrayStack *);
void printMenu();
void handleCommand(TextEditor *editor, char command[], DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);

Node *createNode(char *text);
void appendNode(TextEditor *editor, Node *new);