rm -r release
mkdir release
cp -a 'C:/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Redist/MSVC/14.16.27012/x64/Microsoft.VC141.CRT/.' release/
cp C:/Users/daniil/Documents/GitHub/build-Rudiron_Terminal-Desktop_Qt_5_12_10_MSVC2017_64bit-Release/release/Rudiron_Terminal.exe release/
cd C:/Qt/Qt5.12.10/5.12.10/msvc2017_64/bin
./windeployqt.exe --release --qmldir C:/Users/daniil/Documents/GitHub/Rudiron_Terminal C:/Users/daniil/Documents/GitHub/Rudiron_Terminal/release/Rudiron_Terminal.exe
$SHELL
