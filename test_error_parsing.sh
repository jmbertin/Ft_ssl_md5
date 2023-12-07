#!/bin/bash

execute_test()
{
    echo "Command: $1"
    eval $1
    echo "-------------------------------------"
}

echo "=== Invalid commands ==="
execute_test "./ft_ssl md5 -x" # Unknown flag
execute_test "./ft_ssl md5 - - - -q" # Unknown flag
execute_test "./ft_ssl md5 -s" # String without argument
execute_test "./ft_ssl unknown_command" # Unknown command
execute_test "./ft_ssl md5 -p -q -r -s" # String without argument
execute_test "./ft_ssl md5 -p -s -r -q" # String without argument
