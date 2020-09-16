all: client server

client: client.o
	g++ -std=c++11 client.cpp -o client
	
server: server.o
	g++ -std=c++11 server.cpp -o server	
	
clean:
	\rm *.o client server
