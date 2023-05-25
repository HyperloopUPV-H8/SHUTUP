from inspect  import  getmembers, isfunction

import __main__
import sys

def execute_all_tests_main():
    functions = getmembers(__main__, isfunction)
    for name, function in functions:            
        if name.startswith("test_") or name.startswith("setup_") or name.startswith("close_"):
            function()
    print()
    exit(0)
            
execute_all_tests_main()