clear
cd /Users/daniilignatev/GitHub/Rudiron_Terminal/
root_dir=$(PWD)
echo $root_dir

rm -r release
mkdir release
cp -r /Users/daniilignatev/GitHub/build-Rudiron_Terminal-Desktop_Qt_5_12_12_clang_64bit-Release/Rudiron_Terminal.app release/
cd /Users/daniilignatev/Qt5.12.12/5.12.12/clang_64/bin
./macdeployqt $root_dir/release/Rudiron_Terminal.app -qmldir=$root_dir/Components -dmg

$SHELL