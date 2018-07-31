#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

const int HEIGHT = 300;
const int WIDTH = 600;
const int SCALAR = 3;
const int TURNS_PER_FRAME = 500;

int main( void ) 
{
	std::cout << "Program started..." << std::endl;

	cv::Mat canvas = cv::Mat(HEIGHT, WIDTH, CV_8UC3);
	cv::Mat display = cv::Mat(HEIGHT*SCALAR, WIDTH*SCALAR, CV_8UC3);
	int *current_sandpile = (int*)malloc(HEIGHT*WIDTH*sizeof(int));
	int *next_sandpile = (int*)malloc(HEIGHT*WIDTH*sizeof(int));

	if(current_sandpile == nullptr){
		std::cerr << "Failed to allocate memory for sandpile 1" << std::endl;
		return -1;
	}
	
	if(next_sandpile == nullptr){
		std::cerr << "Failed to allocate memory for sandpile 2" << std::endl;
		return -1;
	}
	
	std::cout << "Starting window..." << std::endl;
	cv::namedWindow( "Sandpiles", cv::WINDOW_AUTOSIZE );
	cv::imshow( "Sandpiles", display );	
	std::cout << "Window done..." << std::endl;
	
	current_sandpile[(HEIGHT/2*WIDTH)+WIDTH/2] = 200000;
	
	std::cout << "Starting copy..." << std::endl;
	memcpy(next_sandpile, current_sandpile, HEIGHT*WIDTH*sizeof(int));
	std::cout << "Copy complete..." << std::endl;
	
	
	int frame_num = 0;
	
	while(1) {
		bool changed = false;
		for(int i = 0; i < HEIGHT; i++) {
			for(int j = 0; j < WIDTH; j++) {
				if( current_sandpile[i*WIDTH+j] > 3 ) {
					changed = true;
					next_sandpile[i*WIDTH+j] -= 4;
					if(i < (HEIGHT-1))
						next_sandpile[(i+1)*WIDTH +j]++;
					if(i > 0)
						next_sandpile[(i-1)*WIDTH+j]++;
					if(j > 0)
						next_sandpile[i*WIDTH+j-1]++;
					if(j < (WIDTH-1))
						next_sandpile[i*WIDTH+j+1]++;
				}
			}
			//std::cout << "Finished row " << i << std::endl;
		}
		if(++frame_num%TURNS_PER_FRAME == 0) {
			for(int i = 0; i < HEIGHT; i++) {
				cv::Vec3b* pixel = canvas.ptr<cv::Vec3b>(i);
				for(int j = 0; j < WIDTH; j++) {
					switch(current_sandpile[i*WIDTH+j]) {
						case 0:
							(*pixel)[0] = 0;
							(*pixel)[1] = 0;
							(*pixel)[2] = 0;
							break;
						case 1:
							(*pixel)[0] = 0;
							(*pixel)[1] = 0;
							(*pixel)[2] = 255;
							break;
						case 2:
							(*pixel)[0] = 255;
							(*pixel)[1] = 0;
							(*pixel)[2] = 255;
							break;
						case 3:
							(*pixel)[0] = 0;
							(*pixel)[1] = 255;
							(*pixel)[2] = 0;
							break;
						default:
							(*pixel)[0] = 255;
							(*pixel)[1] = 255;
							(*pixel)[2] = 255;
							break;
					}
					pixel++;
				}
			}

			std::cout << "Displaying frame " << frame_num++ << std::endl;
			cv::resize(canvas, display, cv::Size(), SCALAR, SCALAR, cv::INTER_NEAREST);
			cv::imshow( "Sandpiles", display );	
			cv::waitKey(1);
		}
		memcpy(current_sandpile, next_sandpile,  HEIGHT*WIDTH*sizeof(int));
		
		if( !changed )
			break;
	}
	
	cv::resize(canvas, display, cv::Size(), SCALAR, SCALAR, cv::INTER_NEAREST);
	cv::imshow( "Sandpiles", display );	
	std::cout << "Press 3 keys to close... (Its 3 because I need to screenshot, and 1 kills the window screenshot before I can get it, and I am not running it again....)" << std::endl;
	cv::waitKey(0);
	cv::waitKey(0);
	cv::waitKey(0);
	return 0;

}


