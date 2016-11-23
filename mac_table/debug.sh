case $1 in
e)
	clear;$0 && clear && ./test
	;;
n)
	gcc main.c udebug.c umactable.c -o test
	;;
*)
	gcc -DDEBUG main.c udebug.c umactable.c -o test
	;;
esac




