FOR /d /r . %%d IN (".vs") DO @IF EXIST "%%d" rd /s /q "%%d"
del /s /q *.pch
