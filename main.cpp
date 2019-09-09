#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int send_data(Mat img)
{
	//img = (img.reshape(0,1));
	int  imgSize = img.total()*img.elemSize();
	printf("size = %d\n", imgSize);
	int send_sock;
	struct sockaddr_un client;
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
	write(send_sock, &imgSize, sizeof imgSize);
	write(send_sock, img.data, imgSize);
	close(send_sock);
	unlink("/tmp/tmp");	
}

int main( int argc, char** argv )
{
	String imageName( "img.jpg" ); // by default
	Mat image;
	image = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Read the file
	if(image.empty())                      // Check for invalid input
	{
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	if(! image.data ) {
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	send_data(image);
	namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
	imshow( "Display window", image );                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}
