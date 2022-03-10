echo hello
for /r %%i in (*.raw) do (
    raw_to_bmp.exe 1920 1080 %%i
)
    