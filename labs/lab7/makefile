#아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
#Signed: [박건우]
#Student Number: [21901023]

qsort: quick.o comparator.o printlist.o
	g++ quick.o comparator.o printlist.o -o qsort
quick.o: quick.cpp
	g++ -c quick.cpp -I../../include
comparator.o: comparator.cpp
	g++ -c comparator.cpp
printlist.o: printlist.cpp
	g++ -c printlist.cpp
clean:
	rm -f *.o qsort.exe qsort