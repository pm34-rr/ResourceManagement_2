for i in `seq 1 4`
do
	echo "Test #$i"
	scriptName=test$i.sh
	./$scriptName
	echo " "
done