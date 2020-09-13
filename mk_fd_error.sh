filename_list=("test" "test_continu" "test_ligne_7+1" "test_ligne_8+1" "test_lignes_vides" "test_vide")
bonus="_bonus"


if [ -f "a.out" ]
then
	echo "executable already exists, deleting"
	rm a.out
fi


if [ ! -z $1 ]
then
	echo "dollar 1 = $1"
	buffer_size=$1
else
	echo "no dollar 1"

	buffer_size=1
fi

if [ ! -z $2 ]
then
	echo "dollar 2 = $2"
	iterations_count=$2
else
	echo "no dollar 2"
	iterations_count=3
fi

for filename in ${filename_list[@]}
do
	gcc \
	-Wall -Wextra -Werror \
	-I gnl \
	-fsanitize=address -g \
	main_fd_error.c \
	gnl/get_next_line$bonus.c gnl/get_next_line_utils$bonus.c gnl/get_next_line$bonus.h \
	-D BUFFER_SIZE=$buffer_size
	./a.out $filename $iterations_count
done
