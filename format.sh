# !/bin/bash
#
#
# Automated Shell Script to format the root project

find ./include -iname "*.h" | xargs clang-format -i
find ./src -iname "*.cpp" | xargs clang-format -i