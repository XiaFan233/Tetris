xmake project -k compile_commands
Copy-Item .\compile_commands.json .\.vscode\
Copy-Item .\images\ -Recurse .\build\windows\x64\release\ -Force
Remove-Item .\compile_commands.json