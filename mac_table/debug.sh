case $1 in
e)
	clear;$0 && clear && ./test
	;;
n)
	gcc umactable.c udebug.c main.c -o test
	;;
*)
	gcc -DDEBUG -DDEBUG_MAC_TABLE main.c udebug.c umactable.c -o test
	# gcc -DDEBUG -DDEBUG_MAC_TABLE main.c udebug.c -o test
	;;
esac




