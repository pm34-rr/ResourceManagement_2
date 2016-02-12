mkdir test_3
cp program test_3/program
chmod 100 test_3
cd test_3
./program
cd ..
chmod 755 test_3
rm -r test_3