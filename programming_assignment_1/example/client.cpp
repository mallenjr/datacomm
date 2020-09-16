// Author: Maxwell Young

#include <iostream>
#include <sys/types.h>   // defines types (like size_t)
#include <sys/socket.h>  // defines socket class
#include <netinet/in.h>  // defines port numbers for (internet) sockets, some address structures, and constants
#include <netdb.h> 
#include <iostream>
#include <fstream>
#include <arpa/inet.h>   // if you want to use inet_addr() function
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
  
  struct hostent *s; 
  s = gethostbyname(argv[1]);
  
  struct sockaddr_in server;
  int mysocket = 0;
  socklen_t slen = sizeof(server);
  char payload[512]="123"; 
  cout << "Payload contains:  " << payload << endl;
  
  
  if ((mysocket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in creating socket.\n";
    
  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(7123);
  bcopy((char *)s->h_addr, 
	(char *)&server.sin_addr.s_addr,
	s->h_length);
      
  for (int i=0; i<5; i++) {
    cout << "Sending packet " << i << endl;
    cout << payload << endl;
    if (sendto(mysocket, payload, 8, 0, (struct sockaddr *)&server, slen)==-1)
      cout << "Error in sendto function.\n";
  }
  recvfrom(mysocket, payload, 512, 0, (struct sockaddr *)&server, &slen); 
  cout << payload << endl;
  close(mysocket);
  return 0;
}