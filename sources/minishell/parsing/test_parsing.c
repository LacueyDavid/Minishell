
#include <cgreen/cgreen.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include "fcntl.h"

Describe(exec_full_command);

BeforeEach(exec_full_command) {}

AfterEach(exec_full_command) {}

Ensure(exec_full_command, can_exec_echo_toto)
{
}
