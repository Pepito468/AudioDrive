#! /bin/bash
# gcc
# main.c                            -> file to be compiled
# -o startServer                    -> executable output
# -Wall -pedantic -Werror -Wextra   -> error checking flags
# -lcurl                            -> extra libs flag
# Extra libs required:
# curl -> -lcurl
#
gcc main.c -o startServer -Wall -pedantic -Werror -Wextra -lcurl