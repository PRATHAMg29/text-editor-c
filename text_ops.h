#include "text_editor.h"

void insertText(TextEditor *editor, char *text);
void delete(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
void deleteCharacters(TextEditor *editor, int length);
void deleteLine(TextEditor *editor);
