root_dir=$PWD
rm -r release
mkdir release
#cp -a 'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.16.27023/bin/HostX64/x64' release/
cp -a 'C:/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Redist/MSVC/14.16.27012/x64/Microsoft.VC141.CRT/.' release/
cp ../build-Rudiron_Terminal-Desktop_Qt_5_12_10_MSVC2017_64bit-Release/release/Rudiron_Terminal.exe release/
cd C:/Qt/Qt5.12.10/5.12.10/msvc2017_64/bin
./windeployqt.exe --release --qmldir $root_dir $root_dir/release/Rudiron_Terminal.exe

$SHELL
