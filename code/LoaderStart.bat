taskkill /f /im PSIM.exe
mkdir build
cd build
g++ -std=c++17 -c ..\src\*.cpp
g++ -shared -o ..\..\output.dll *.o
start "" "..\..\Project.psimsch"