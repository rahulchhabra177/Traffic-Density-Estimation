//Designed by Shrey Patel 2019CS10400 
// and Rahul Chhabra 2019CS11016

#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace cv;

//External Data Structure to store user inputs
struct img_points{
    Mat img;
    vector<Point2f> points;
};

//Function of handling mouse clicks
void handle_clicks(int event,int x,int y,int flags,void* data){

	Scalar color=Scalar(0,255,0);
	
	//User selected point
	Point selected=Point(x,y);
    
    	//Detecting left mouse click
   	if (event==EVENT_LBUTTONDOWN){
   	
   		cout<<x<<" "<<y<<endl;
        	img_points* cur_data=(img_points*) data; 
        	
        	//Circle to be displayed at the selected point
        	circle((cur_data->img),selected,4,color,-1,FILLED);
        	
        	//Displaying updated image
        	imshow("Image",cur_data->img);
        	int sz=(cur_data->points).size();

		//Checking for number of user clicks
        	if (sz>0){
        	
        		//Displaying line to show the bounding box
            		line( cur_data->img,(cur_data->points)[sz-1],selected,Scalar(255,255,255),1,LINE_8);
            		imshow("Image",cur_data->img);
        	}
        	if (sz<4){
            		(cur_data->points).push_back(selected);
            		sz++;
        	}
         	if (sz==4){
            		line( cur_data->img,(cur_data->points)[0],selected,Scalar(255,255,255),1,LINE_8);
            		imshow("Image",cur_data->img);
                }
    	}
}

//Checking file format for valid images
bool check_format(string image){
	int n= image.length();
	if(n<=4){
		return false;
	}else if(image.substr(n-4,4)==".jpg" || image.substr(n-4,4)==".png"){
		return true;
	}else if(n<=5){
		return false;
	}else if(image.substr(n-5,5)==".jpeg"){
		return true;
	}else{
		return false;
	}
}

int main(int argc, char** argv)
{

	//Checking number of arguments
	if(argc == 2){
	
		//Initializing Image
		Mat imgsrc = imread(string(argv[1]),IMREAD_GRAYSCALE);
	
		//Checking valid image
		if(imgsrc.data == NULL){
			cerr<<"Please provide a correct image. Check if the image is present in specified path."<<endl;
		}
		else{
			if(!check_format(argv[1])){
				cerr<<"Incorrect image format. Please provide a correct image file format. Accepted file formats: .jpg, .jpeg and .png"<<endl;
			}
			else{
				//Resizing Image
				Mat resized_img;
				resize(imgsrc,resized_img, Size(imgsrc.cols*1.5,imgsrc.rows*1.5));
	
	
				//These values depend upon the display resolution of the machine used 
				Size cropped_size(600,800);
				Size img_size=resized_img.size();
	
	
				//Destination images initialized as blank/empty canvas i.e. a black screen	
				Mat img_dst = Mat::zeros(img_size,CV_32F);
				Mat img_dst2 = Mat::zeros(img_size,CV_32F);
	
	
				//Cloning original image to avoid mouse clicks and bounding box in warped and cropped images
				Mat to_be_displayed = resized_img.clone();
				img_points userdata;
				userdata.img=to_be_displayed;
				imshow("Image",to_be_displayed);
	
	
	
				//Calling procedure to take input mouse clicks
				setMouseCallback("Image",handle_clicks,&userdata);
				waitKey(0);
	
	
	
				//A vector of points of derived points on img_dst for displaying the warped image
				vector<Point2f> pts_dst;
				float x1 = (userdata.points[0].x+userdata.points[1].x)/2;
				float y2 = (userdata.points[1].y+userdata.points[2].y)/2;
				float x2 = (userdata.points[2].x+userdata.points[3].x)/2;
				float y1 = y2-3*(x2-x1)/2;
				//Generalisation for point selection
				if (y1<0){
					y2+=abs(y1);
					y1=0.0;
					if (y2>img_size.height){
						float dif=y2-img_size.height;
						y2=img_size.height;
						dif*=0.67;
						x1+=dif/2;
						x2-=dif/2;
					}
				}
				pts_dst.push_back(Point2f(x1,y1));
				pts_dst.push_back(Point2f(x1,y2));
				pts_dst.push_back(Point2f(x2,y2));							
				pts_dst.push_back(Point2f(x2,y1));

	

				//A vector of pre-defined points
				vector<Point2f> pts_dst2;
				pts_dst2.push_back(Point2f(0,0));
				pts_dst2.push_back(Point2f(0,cropped_size.height-1));
				pts_dst2.push_back(Point2f(cropped_size.width-1,cropped_size.height-1));
				pts_dst2.push_back(Point2f(cropped_size.width-1,0));
	

				//Obtaining warped image
				Mat h1 = findHomography(userdata.points,pts_dst);
				warpPerspective(resized_img,img_dst,h1,img_size);
	
				//Obtaining cropped image
				Mat h2 = findHomography(userdata.points,pts_dst2);
				warpPerspective(resized_img,img_dst2,h2,cropped_size);

				//Displaying image(s)
				imshow("Warped Image",img_dst);
				waitKey(0);
				imshow("Cropped Image",img_dst2);
				waitKey(0);

				//Saving the image in the directory
				imwrite("resized.jpg",resized_img);
				imwrite("warped.jpg",img_dst);
				imwrite("cropped.jpg",img_dst2);
			}
		}
	}
	else{
		cerr<<"Only two arguments are acceptable. The correct input format on the command line should be ./img sample_img.jpg"<<endl;
	}
	return 0;
}
