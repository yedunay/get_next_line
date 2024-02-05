# get_next_line

## Overview

`get_next_line` is a function in the C programming language designed to read a line from a file descriptor. It provides a flexible and efficient way to read and process data from files or other input sources. This README serves as a guide to understanding and implementing the `get_next_line` function.

## Function Signature

```c
int get_next_line(int fd, char **line);
```

- **Parameters:**
  - `fd`: The file descriptor for reading.
  - `line`: A pointer to a character pointer where the line read will be stored.

- **Return Value:**
  - Returns 1 when a line is successfully read.
  - Returns 0 when the end of file (EOF) is reached.
  - Returns -1 on error.

## Usage

To use `get_next_line`, include the function prototype in your code and compile it along with the source file containing the function.

```c
#include "get_next_line.h"

int main() {
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("File could not be opened");
        return 1;
    }

    while (get_next_line(fd, &line) > 0) {
        // Process the line as needed
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

Ensure to handle memory properly by freeing the allocated memory for each line.

## Implementation Details

The `get_next_line` function dynamically allocates memory for the line read and adjusts the buffer size as needed. It efficiently handles reading from files of any size by reading and processing the input in chunks.

## Error Handling

- Ensure that the file descriptor passed to `get_next_line` is valid.
- Check the return value for errors (-1) during the function call.

```c
if (get_next_line(fd, &line) == -1) {
    perror("Error reading line");
    return 1;
}
```

## Compilation

Compile your program with the appropriate flags and include the necessary headers.

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 your_program.c get_next_line.c -o your_program
```

Ensure to define `BUFFER_SIZE` appropriately to control the size of the internal buffer used by `get_next_line`.

## Contributions

Contributions to enhance the functionality, performance, or documentation of `get_next_line` are welcome. Feel free to submit issues or pull requests.
