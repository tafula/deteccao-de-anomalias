#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char** argv){
  /**************************************************/	
  /*** Setta o num de imagens que ele vai receber ***/
  /**************************************************/
  FILE* setter = fopen("settings.txt", "r");
  if(setter == NULL) cout << "Problema lendo settings.txt!";
	
  int nOfImages = 0; //NUMERO DE IMAGENS QUE ELE RECEBE
  char c;
  while ((c = fgetc(setter)) != EOF){
    if (c == ' ' || c == '\n' || c == '\t') nOfImages += 1;
    if (nOfImages == 3){
      fscanf(setter, "%d", &nOfImages);
      break;
    }
  }
  fclose(setter);
  /**************************************************/
  /**************************************************/  

  cv::VideoCapture cap(0);
  Ptr<BackgroundSubtractorMOG2> bg = createBackgroundSubtractorMOG2();
  int i = 0;
  int swap = 0; //swapper de pastas

  //gather the input images and their foreground masks
  while(i < nOfImages){
    cv::Mat image, bw; //frame to be saved
    cap >> image;
    cv::resize(image, image, cv::Size(238, 158), 0, 0, CV_INTER_CUBIC);

    cv::Mat frame = image.clone(); //frame to be modified and obtain foreground mask

    cv::cvtColor(image, bw, CV_RGB2GRAY);
    cv::cvtColor(frame, frame, CV_RGB2GRAY);
	  
    cv::blur(frame, frame, cv::Size(5,5));
	  
    cv::Mat morphologicalKernel= cv::getStructuringElement(cv::MORPH_RECT,
							   cv::Size(7,7),
							   cv::Point(3,3));

    cv::dilate(frame, frame, morphologicalKernel);
    cv::erode(frame, frame, morphologicalKernel);

    cv::erode(frame, frame, morphologicalKernel);
    cv::dilate(frame, frame, morphologicalKernel);

    cv::Mat foreground; //foreground mask
    bg->apply(frame, foreground, 0.0001); //removes background

    cv::threshold(foreground, foreground, 125, 255, CV_THRESH_BINARY); //gets foreground mask
    
    double min, max;
    minMaxLoc(foreground, &min, &max);

    if(min == 255 or max == 0)
      continue;

    //saves image
    char filename[64];
    sprintf(filename, "test/img/f%d/%03d.tif", swap, i);
    imwrite(filename, bw); //writes image to file

    char maskname[64];
    sprintf(maskname, "test/mask/f%d/%03d.png", swap, i);
    imwrite(maskname, foreground);
    
    if(i % 10 == 9) cout << i+1 << "\n";  
    i++;

	//faz o swap
	if(i == nOfImages){
		swap = 1-swap;
		i = 0;
	}

    imshow("Feed", image);
  }
}
