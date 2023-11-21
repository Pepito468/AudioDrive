#! /bin/bash
# gcc
# main.c                            -> file to be compiled
# -o startServer                    -> executable output
# -Wall -pedantic -Werror -Wextra   -> error checking flags
# things that come after            -> extra libs flag
# Extra libs required:
# 
#
gcc main.c -o startServer -Wall -pedantic -Werror -Wextra