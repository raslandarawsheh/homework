#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
	int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
	portno = 5001;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		cout << "err in opening socket";
	
        server = gethostbyname("localhost");
	if (server == NULL) {
		cout << "ERROR, no such host\n";
	        exit(-1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	      (char *)&serv_addr.sin_addr.s_addr,
	              server->h_length);
		      serv_addr.sin_port = htons(portno);
       if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		cout<< "ERROR connecting";


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
       	n = write(sockfd,image.data,image.total()*image.channels());
	if (n < 0) 
		cout << "ERROR writing to socket";
	close(sockfd);          
	namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
	imshow( "Display window", image );                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}
