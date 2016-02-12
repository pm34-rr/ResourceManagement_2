mkdir test_4
cp program test_4/program
cd test_4

for i in `seq 0 301`
do
	fileName=file_$i
	touch $fileName
	echo `expr 400 -  $i` > $fileName
done

./program
cd ..
rm -r test_4