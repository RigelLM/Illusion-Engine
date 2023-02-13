cd ..\
md Publish
copy bin\Debug-windows-x86_64\Game\Game.exe Publish\Game.exe /Y
copy bin\Debug-windows-x86_64\Game\Game.pdb Publish\Game.pdb /Y
copy Game\ikpFlac.dll Publish\ikpFlac.dll /Y
copy Game\ikpMP3.dll Publish\ikpMP3.dll /Y
copy Game\irrKlang.dll Publish\irrKlang.dll /Y
xcopy Game\assets Publish\assets /E
PAUSE