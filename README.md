# liba.h - Aiden's Library for C

liba.h is a collection of commonly needed c functions and macros.

## To use:
```c
// main.c
#define LIBA_IMPLEMENTATION
#include "liba.h"

int main(int argc, char *argv[]) {
  liba_log(LIBA_INFO, "Hello from liba.h!");
}
```

## Available functions and macros examples:
```c
/* --- Logging --- */
liba_log(LIBA_FATAL, "The excit code should have been 3 but was %d!", exit_code); 

void greet(const char* name) {
  LIBA_UNIMPLEMENTED();
}

int x = 67;
liba_debug(x); 
```

```c
/* --- Dynamic Arrays --- */
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

## Redefinable constants and handlers:
### Constants
- **LIBA_TEXT_FORMAT_BUFFER_SIZE** (default 1024): size of the `liba_str_format` buffer
- **LIBA_TEXT_FORMAT_NUM_BUFFERS** (default 4): number of static buffers
- **LIBA_DA_BASE_CAPACITY** (default 1): the base capacity for dynamic arrays
- **LIBA_DA_CAPACITY_MULT** (default 2): the capacity scaling multiplier for dynamic arrays

### Handlers
- **LIBA_FATAL_HANDLER** (default `exit(EXIT_FAILURE);`): called on fatal
