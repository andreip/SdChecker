if [ "$#" -ne 1 ]; then
	echo "Usage $0 <path_to_input_file.txt>"
	exit
fi

function plot_input() {
	rm newStoreCoords.txt

	echo "Running student file for $1"
	./a.out < $1
	echo ""

	echo "Found coords"
	cat newStoreCoords.txt
	echo ""

	cd mapgen
	echo "Generating map for file $1"
	./a.out < ../$1

	open map1.html
}

plot_input $1
