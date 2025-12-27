#include <stdio.h>
#include <sys/wait.h>

#define TESTS                                                                  \
  ADD(test_dynamic_arrays)                                                     \
  ADD(test_logging)
#define CTEST_IMPLEMENTATION
#include "ctest.h"

#define LIBA_IMPLEMENTATION
#include "liba.h"

TEST(test_dynamic_arrays, {
  liba_da(int) numbers = liba_da_init();

  for (int i = 0; i < 10; i++) {
    liba_da_append(numbers, i);
  }
  liba_da_foreach(numbers, it, idx) {
    ASSERT_MSG(it == idx, "it = %d, idx = %d", it, idx);
  }

  liba_da_foreach_ptr(numbers, it, idx) { *it += 1; }
  liba_da_foreach(numbers, it, idx) {
    ASSERT_MSG(it == idx + 1, "it = %d, idx = %d", it, idx);
  }

  liba_da_clear(numbers);
  ASSERT(numbers.count == 0);

  liba_da_free(numbers);
  ASSERT(numbers.items == NULL);
})

TEST(test_logging, {
  FILE *tmp = tmpfile();
  ASSERT(tmp);

  FILE *old_stdout = stdout;
  stdout = tmp;

  liba_log(LIBA_INFO, "info: %d", 1);
  liba_log(LIBA_WARN, "warn");
  liba_log(LIBA_ERROR, "error");

  pid_t pid = fork();
  if (pid == 0) {
    // child
    liba_log(LIBA_FATAL, "fatal");
    _exit(0); // safety, shouldn't reach here
  } else {
    // parent
    int status;
    waitpid(pid, &status, 0);
    ASSERT(WIFEXITED(status));
    ASSERT(WEXITSTATUS(status) == EXIT_FAILURE);
  }

  fflush(stdout);
  fseek(tmp, 0, SEEK_SET);

  char buf[256];
  size_t n = fread(buf, 1, sizeof(buf) - 1, tmp);
  buf[n] = '\0';

  stdout = old_stdout;

  ASSERT_MSG(liba_str_contains(buf, "[INFO] info: 1\n"), "buf = \"%s\"", buf);
  ASSERT_MSG(liba_str_contains(buf, "[WARN] warn\n"), "buf = \"%s\"", buf);
  ASSERT_MSG(liba_str_contains(buf, "[ERROR] error\n"), "buf = \"%s\"", buf);
  ASSERT_MSG(liba_str_contains(buf, "[FATAL] fatal\n"), "buf = \"%s\"", buf);
})

RUN_TESTS();
