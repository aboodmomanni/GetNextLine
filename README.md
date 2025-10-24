# get_next_line

A C function that reads a file line by line, returning one line at a time from a given file descriptor.

## Overview

`get_next_line` is a project from 42 School that implements a function to read files efficiently line by line. The function uses static variables to maintain state across multiple calls, allowing it to read a file one line at a time without loading the entire file into memory.

## Features

- Reads files line by line from any file descriptor
- Handles files with or without trailing newlines
- Memory efficient with configurable buffer size
- Supports multiple file descriptors (bonus version)
- No memory leaks with proper cleanup

## Project Structure

```
.
├── get_next_line.c          # Main function
├── get_next_line.h          # Header file with function declaration
├── get_next_line_utils.c    # Helper utility functions
├── get_next_line_bonus.c    # Bonus version for multiple file descriptors
├── get_next_line_bonus.h    # Bonus header file
└── get_next_line_utils_bonus.c  # Bonus utility functions
```

## Compilation

### Standard Version
```bash
gcc -D BUFFER_SIZE=1000 -c get_next_line.c get_next_line_utils.c
gcc -o program main.c get_next_line.o get_next_line_utils.o
```

### Bonus Version (Multiple File Descriptors)
```bash
gcc -D BUFFER_SIZE=1000 -c get_next_line_bonus.c get_next_line_utils_bonus.c
gcc -o program main.c get_next_line_bonus.o get_next_line_utils_bonus.o
```

## Usage

```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Function Documentation

### `char *get_next_line(int fd)`

Reads the next line from the given file descriptor.

**Parameters:**
- `fd`: File descriptor to read from

**Return:**
- Pointer to the next line (including newline if present)
- NULL when end of file is reached or on error

**Important:** The returned pointer must be freed by the caller.

## Buffer Size

The `BUFFER_SIZE` macro defines how many bytes are read at a time. You can adjust it during compilation:

```bash
gcc -D BUFFER_SIZE=4096 ...  # Larger buffer
gcc -D BUFFER_SIZE=1 ...     # Smaller buffer
```

Default is 1000 bytes.

## Utility Functions

- `f_strlen()` - Calculate string length
- `f_strchr()` - Find character in string
- `f_dup()` - Duplicate string
- `f_join()` - Concatenate two strings
- `f_ssubstr()` - Extract substring

## Bonus Features

The bonus version (`get_next_line_bonus.c`) handles multiple file descriptors simultaneously using an array of static variables indexed by file descriptor number. This allows reading from multiple files at the same time without losing track of each file's position.

## Key Implementation Details

- **Static Variable**: Maintains leftover data between function calls
- **Leftover Management**: Preserves unread data for the next call
- **Memory Efficiency**: Uses dynamic allocation and proper cleanup
- **Error Handling**: Returns NULL on read errors or invalid input

## Memory Management

The function properly manages memory by:
- Freeing old leftover data after extracting the line
- Preserving remaining unread data in the static variable
- Handling allocation failures gracefully
- Requiring the caller to free returned line pointers

## Example with Error Checking

```c
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;
    
    fd = open("input.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (1);
    }
    
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Limitations

- `MAX_FD` in bonus version is set to 1024 (maximum file descriptors)
- File descriptor must be valid and open
- BUFFER_SIZE must be greater than 0

## Author

Created by aalmoman at 42 School
