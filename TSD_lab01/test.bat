@echo off
bin\Debug\TSD_lab01_ver6.exe < test\in_%1.txt > test\out.txt
fc test\out_%1.txt test\out.txt
del test\out.txt