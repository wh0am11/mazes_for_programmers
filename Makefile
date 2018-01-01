all_debug:

	cc -g -Wall btree.c -o btree
	cc -g -Wall swinder.c -o swinder
	cc -g -Wall djikstra.c -o djikstra
	cc -g -Wall djikstra2.c -o djikstra2
	cc -g -Wall longest_path.c -o longest_path

testf:

	cc -g -Wall test.c -o test

testf_ndebug:

	cc -g -Wall -DNDEBUG test.c -o test

all:

	cc -g -Wall -DNDEBUG btree.c -o btree
	cc -g -Wall -DNDEBUG swinder.c -o swinder
	cc -g -Wall -DNDEBUG djikstra.c -o djikstra
	cc -g -Wall -DNDEBUG djikstra2.c -o djikstra2
	cc -g -Wall -DNDEBUG longest_path.c -o longest_path
