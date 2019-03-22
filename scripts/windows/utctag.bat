@Echo off
:: Check WMIC is available
WMIC.EXE Alias /? >NUL 2>&1 || GOTO s_error

:: Use WMIC to retrieve date and time
FOR /F "skip=1 tokens=1-7" %%a IN ('WMIC Path Win32_LocalTime Get Day^,Hour^,Minute^,Month^,Second^,Year /Format:table') DO (
      
   IF not "%%~f"=="" (
      SET _yyyy=%%f
      SET _mm=00%%d
      SET _dd=00%%a
      SET _hour=00%%b
      SET _minute=00%%c
      SET _second=00%%e
      )
)
:s_done

:: Pad digits with leading zeros
      SET _mm=%_mm:~-2%
      SET _dd=%_dd:~-2%
      SET _hour=%_hour:~-2%
      SET _minute=%_minute:~-2%
      SET _second=%_second:~-2%

:: Display the date/time in ISO 8601 format:
SET _utctag=%_yyyy%%_mm%%_dd%%_hour%%_minute%%_second%

GOTO:EOF

:s_error