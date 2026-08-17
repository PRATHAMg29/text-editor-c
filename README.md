# Text Editor in C

A simple command-line text editor developed in C. The project demonstrates the use of **doubly linked lists, stacks, dynamic memory allocation, file handling, pointers, and modular programming**.

## Features

* Insert text at the cursor position
* Delete characters
* Cursor navigation
* Display the current text
* Open text files
* Save text to files
* Undo operations
* Redo operations
* Create and edit text dynamically
* Command-based user interface

## Data Structures Used

### Doubly Linked List

The text inside the editor is stored using a doubly linked list.

Each node represents a line of text and contains:

* The text stored in the line
* A pointer to the previous line
* A pointer to the next line

This allows efficient movement between lines and modification of the text.

### Dynamic Stack

Two stacks are used for implementing undo and redo functionality:

* **Undo Stack** – stores previous editing operations
* **Redo Stack** – stores operations that have been undone

## Project Structure

```text
Text-Editor/
│
├── create_node.c
├── cursor_navigation.c
├── delete.c
├── display.c
├── file_ops.c
├── handle.c
├── init.c
├── main.c
├── push_pop.c
├── undo_stack.c
│
├── text_editor.h
├── text_ops.h
├── file_ops.h
├── redo_undo.h
├── curser_navigations.h
├── display_search.h
│
└── first.txt
```

## Commands

The editor provides the following commands:

| Command           | Description                                         |
| ----------------- | --------------------------------------------------- |
| `insert <text>`   | Inserts text at the current cursor position         |
| `delete <number>` | Deletes characters from the current cursor position |
| `undo`            | Undoes the previous editing operation               |
| `redo`            | Redoes a previously undone operation                |
| `cursor`          | Provides cursor navigation                          |
| `print`           | Displays the current contents of the editor         |
| `exit`            | Exits the text editor                               |

## Technologies Used

* **Language:** C
* **Compiler:** GCC
* **Data Structures:** Doubly Linked List, Stack
* **Memory Management:** Dynamic Memory Allocation
* **File Handling:** C File I/O
* **Development Environment:** Linux / GCC

## Concepts Demonstrated

This project was developed to practice and demonstrate:

* Structures
* Pointers
* Dynamic memory allocation
* Linked lists
* Doubly linked lists
* Stacks
* Dynamic arrays
* File handling
* String manipulation
* Command-line input
* Modular programming
* Undo/Redo implementation
* Cursor management

## Compilation

Compile all the source files using GCC:

```bash
gcc *.c -o text_editor
```

Run the program:

```bash
./text_editor
```

## Example

A typical interaction with the editor looks like:

```text
Text Editor

Enter command: insert Hello World

Enter command: print

Hello World

Enter command: undo

Enter command: redo
```

## Future Improvements

Some possible improvements for the project are:

* Search and replace functionality
* Copy and paste functionality
* Multiple-line selection
* Improved cursor movement
* Line insertion and deletion
* Better error handling
* Syntax highlighting
* Improved command interface
* Cross-platform terminal support

## Learning Outcomes

This project helped strengthen understanding of:

* Dynamic data structures
* Pointer manipulation
* Memory allocation and deallocation
* Stack-based algorithms
* Linked-list operations
* File I/O in C
* Modular program design
* Implementation of undo/redo systems

## Author

**Pratham**
