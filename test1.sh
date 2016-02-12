mkdir test_1
cp program test_1/program
cd test_1
mkdir 1
mkdir 2
touch 1.txt
touch foobar.txt
echo "aslkdjaskljd" > 1.txt
./program
cd ..
rm -r test_1