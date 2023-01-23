cd ..\
rd /s /q .vs
rd /s /q bin
rd /s /q bin-int
del /a Project.sln
del /a /s *.vcxproj.*
pushd Illusion\Lib\Glad
rd /s /q bin
rd /s /q bin-int
popd
pushd Illusion\Lib\GLFW
rd /s /q bin
rd /s /q bin-int
popd
pushd Illusion\Lib\imgui
rd /s /q bin
rd /s /q bin-int
popd
PAUSE