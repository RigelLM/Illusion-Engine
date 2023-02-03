cd ..\
md Publish
copy bin\Debug-windows-x86_64\Game\Game.exe Publish\Game.exe /Y
copy bin\Debug-windows-x86_64\Game\Game.pdb Publish\Game.pdb /Y
xcopy Game\assets Publish\assets /E
PAUSE