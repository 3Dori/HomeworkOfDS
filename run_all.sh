:>7_1.txt
for index in '1' '2'
do
    for letter in 'a' 'b' 'c' 'd'
    do
	file=$(echo 7_"$index""_$letter")
	echo $file >> 7_1.txt
	./$file >> 7_1.txt
	echo >> 7_1.txt
    done
done
