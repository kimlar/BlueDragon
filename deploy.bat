@echo off

REM SDL2 DLLs
echo SDL2 DLLs:
cd SDL2
call "DeployDLL.bat"
cd ..

REM SDL2_image DLLS
echo SDL2_image DLLs:
cd SDL2_image
call "DeployDLL.bat"
cd ..

REM SDL2_ttf
echo SDL2_ttf DLLS:
cd SDL2_ttf
call "DeployDLL.bat"
cd ..
