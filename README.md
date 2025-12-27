# liba.h - Aiden's Library for C
liba.h is a collection of commonly needed c functions and macros.

## To use:

```bash
wget https://raw.githubusercontent.com/AineeJames/liba.h/refs/heads/main/liba.h
```

```c
// main.c
#define LIBA_IMPLEMENTATION
#include "liba.h"

int main(int argc, char *argv[]) {
  liba_log(LIBA_INFO, "Hello from liba.h!");
}
```

## Available functions and macros examples:

### Logging
```c
liba_log(LIBA_FATAL, "The excit code should have been 3 but was %d!", exit_code); 

void greet(const char* name) {
  LIBA_UNIMPLEMENTED(); // Fatal log happens here.
}

int x = 67;
liba_debug(x); 
```

### Dynamic Arrays
```c
liba_da(int) numbers = liba_da_init(); // Initialize a dynamic array of integers.

for (int i = 0; i++; i < 10) {
  liba_da_append(numbers, i * 2); // Append some numbers into the array.
}

// Loop over each element in the dynamic array:
liba_da_foreach(numbers, x, index) {
  liba_log(LIBA_INFO, "numbers[%d] = %d", index, x);
}

liba_da_clear(numbers); // Sets count back to 0.
liba_da_free(numbers);  // Cleans up the memory allocated for `numbers`.
```

### String Manipulation
```c
const char* formatted = liba_str_format("Hello, %s", name);

liba_str_contains(haystack, needle); // Returns true of needle is found in the haystack.
liba_str_equals("string", "string"); // Compare the strings and return true of equal.

liba_str_startswith("string", "s");
liba_str_endswith("string", "g");

// Split a string and iterate the columns:
liba_da_foreach(liba_str_split("john,doe,67", ","), col, i) {
  liba_log(LIBA_INFO, "column %d: %s", i, col);
}
```

## Redefinable constants and handlers:
### Constants
- **LIBA_TEXT_FORMAT_BUFFER_SIZE** (default 1024): size of the `liba_str_format` buffer
- **LIBA_TEXT_FORMAT_NUM_BUFFERS** (default 4): number of static buffers
- **LIBA_DA_BASE_CAPACITY** (default 1): the base capacity for dynamic arrays
- **LIBA_DA_CAPACITY_MULT** (default 2): the capacity scaling multiplier for dynamic arrays

### Handlers
- **LIBA_FATAL_HANDLER** (default `exit(EXIT_FAILURE);`): called on fatal

## Stripping prefixes:
Optionally, you can strip off the `liba_` prefix to functions and macros by including the following:
```c
#define LIBA_IMPLEMENTATION
#define LIBA_STRIP_PREFIX
#include "liba.h"

int main(int argc, char *argv[]) {
  log(INFO, "Look! I didn't need the `liba_` prefix!");
}
```
