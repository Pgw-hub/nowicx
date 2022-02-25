#아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
#Signed: [박건우]
#Student Number: [21901023]

sortDriver : sortDriver.o comparator.o printlist.o bubble.o quick.o
	g++ sortDriver.o comparator.o printlist.o bubble.o quick.o \
		-I../../include -L../../lib -lnowic_mac -o sortDriver

sortDriver.o : sortDriver.cpp
	g++ -c -std=c++11 -Wall sortDriver.cpp -I../../include
comparator.o: comparator.cpp
	g++ -c -std=c++11 -Wall comparator.cpp
printlist.o: printlist.cpp
	g++ -c -std=c++11 -Wall printlist.cpp
bubble.o : bubble.cpp
	g++ -c -std=c++11 -Wall bubble.cpp -I../../include
quick.o: quick.cpp
	g++ -c -std=c++11 -Wall quick.cpp -I../../include
clean:
	rm -f *.o sortDriver.exe sortDriver