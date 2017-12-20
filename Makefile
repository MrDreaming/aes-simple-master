all:
	#gcc aeckey.cpp aes.c random.c main.cpp master_aes_object.cpp -lpthread -lstdc++
	gcc *.cpp *.c -lpthread -lstdc++
libs:
	gcc -c aeckey.cpp aes.c random.c master_aes_object.cpp -lpthread -lstdc++
	ar crv libmyaes.a aeckey.o aes.o random.o master_aes_object.o
exe:
	gcc main.cpp  -lpthread  ./libmyaes.a -lstdc++
clean :
	rm -rf *.o a.out *.a
