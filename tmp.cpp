#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

static int connFd;

int main(int argc, char* argv[])
{
	int recv_sock, send_sock;

  struct sockaddr_un server, client;

  ///////////////////////////////////////////
  //
  // setup send
  //
  ///////////////////////////////////////////

  /* Create socket on which to send. */
  send_sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (send_sock < 0) {
    perror("opening unix socket");
    exit(1);
  }

  /* Construct name of socket to send to. */
  client.sun_family = AF_UNIX;

  strcpy(client.sun_path, "/tmp/tmp");

  if (connect(send_sock, (struct sockaddr *)&client,
              sizeof(struct sockaddr_un)) < 0) {
    close(send_sock);
    perror("connecting stream socket");
    exit(1);
  }

  ///////////////////////////////////////////
  //
  // setup recv
  //
  ///////////////////////////////////////////

  recv_sock = socket(AF_UNIX, SOCK_STREAM, 0);

  if (recv_sock < 0) {
    cerr << "Cannot open socket" << endl;
    return 0;
  }

  bzero((char *)&server, sizeof(server));

  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, "/tmp/tmp1");

  // bind socket
  if (::bind(recv_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    cerr << "Cannot bind" << endl;
    return 0;
  }

  listen(recv_sock, 10);
  connFd = accept(recv_sock, 0, 0);
  if (connFd < 0) {
    cerr << "Cannot accept connection" << endl;
    return 0;
  } else {
    cout << "Connection successful" << endl;
  }

  int X;
  for (int i = 0; i < 10; i++) {
    write(send_sock, &i, sizeof(i));
    cout << "sent " << i << endl;
    cout << "Listening" << endl;
    read(connFd, &X, sizeof(X));
    cout << "received " << X << endl;
    usleep(2000000);
  }

  close(send_sock);
  close(recv_sock);
  unlink(argv[2]);
  unlink(argv[1]);

  return 0;
}


