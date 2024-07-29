@REM Run for python
@REM C:\Users\ADMIN\AppData\Local\Programs\Python\Python310\python.exe D:\C-development\Interview\MAS\Test_Log.py > D:\C-development\Interview\MAS\Output.txt && D:\C-development\Interview\MAS\Log.py

@REM Run for c file
cd /d D:\C-development\Interview\MAS 
gcc -o MAS MAS.c 
.\MAS.exe > D:\C-development\Interview\MAS\Output.txt
C:\Users\ADMIN\AppData\Local\Programs\Python\Python310\python.exe D:\C-development\Interview\MAS\Log.py

@REM The both c and python and debugger
@REM @echo off
@REM cd /d D:\C-development\Interview\MAS
@REM gcc -o MAS MAS.c
@REM if %errorlevel% neq 0 (
@REM     echo Compilation failed.
@REM     pause
@REM     exit /b %errorlevel%
@REM )
@REM .\MAS.exe > Output.txt
@REM if %errorlevel% neq 0 (
@REM     echo Execution failed.
@REM     pause
@REM     exit /b %errorlevel%
@REM )
@REM C:\Users\ADMIN\AppData\Local\Programs\Python\Python310\python.exe D:\C-development\Interview\MAS\Log.py
@REM echo Done.
@REM pause