@echo off
pushd C:
cd Program Files (x86)\Microsoft Visual Studio\Installer
for /f "delims=" %%t in ('vswhere.exe -property catalog_productLineVersion') do set version=%%t
popd
cd ..\
call Lib\premake5\Premake5.exe vs%version%
PAUSE
