@echo off
gcc bfcompiler.c ast.c -o bfcompiler.exe
if %errorlevel% neq 0 (
    echo Compilation failed.
) else (
    echo Compilation succeeded.
)
pause
