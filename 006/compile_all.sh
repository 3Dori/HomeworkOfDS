for index in '1' '2'
do
    for letter in 'a' 'b' 'c' 'd'
    do
	target=$(echo "7_$index""_$letter")
	source=$target.c
	gcc -o $target $source
    done
done
