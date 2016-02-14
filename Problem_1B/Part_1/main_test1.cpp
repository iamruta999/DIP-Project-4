//NAME: Amruta Kulkarni
//USC ID: 6914970827
//USC Email: arkulkar@usc.edu
//Submission date: 29 Nov 2015

//Problem 1B_Part1
// This code tests the optical character recognition (OCR) system using for test image 1
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
RNG rng(12345);

int main()
{
    FILE *file;
    int width = 620;
    int height = 759;
    int bytesPerPixel = 3;
    char *argv[] = {"Test_ideal1.raw","preProcessedImage.raw","segment1.raw","segment2.raw","segment3.raw","segment4.raw","segment5.raw","segment6.raw","segment7.raw","segment8.raw","segment9.raw","segment10.raw","segment11.raw","segment12.raw"};

    // Read the image
    unsigned char imageData[height][width][bytesPerPixel];
    if (!(file=fopen(argv[0],"rb")))
    {
		cout << "Cannot open file: " << argv[0] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), height*width*bytesPerPixel, file);
	fclose(file);
    
    // PRE-PROCESSING
    // Convert the image to gray scale
    unsigned char grayImageData[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            grayImageData[row][column] = ((0.21 * imageData[row][column][0]) +
                                          (0.72 * imageData[row][column][1]) +
                                          (0.07 * imageData[row][column][2]));
        }
    }
    
    // Create Mat to store the image and operate on it
    Mat gray = Mat(height, width, CV_8UC1, grayImageData);
    // Perform thresholding
    Mat thresholdedImage(height, width, CV_8UC1);
    Mat thresholdedColor, thresholdedImage1;
    threshold(gray, thresholdedImage, 50, 255, THRESH_BINARY_INV);
    
    
    // Create vectors to hold the contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat duplicateThresholdedImage;
    thresholdedImage.copyTo(duplicateThresholdedImage);
    findContours(duplicateThresholdedImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    Rect boundary;
    double areaOfcontour;
    double largestArea = 0;
    for( int i = 0; i< contours.size(); i++ )
    {
        areaOfcontour=contourArea( contours[i],false);
        if( areaOfcontour > largestArea)
        {
            largestArea = areaOfcontour;
            boundary = boundingRect(contours[i]);
        }
    }
    rectangle(thresholdedColor, boundary, Scalar(255,0,0),2,8,0);
    
    // Remove the boundary
    // Upper part
    for (int row = boundary.y; row < boundary.y + 25; row++)
    {
        for (int column = boundary.x; column < boundary.x + boundary.width; column++ )
        {
            thresholdedImage.at<int>(row,column) = 0;
        }
    }
    // lower part
    for (int row = boundary.y + boundary.height; row > boundary.y + boundary.height - 25; row--)
    {
        for (int column = boundary.x; column < boundary.x + boundary.width; column++ )
        {
            thresholdedImage.at<int>(row,column) = 0;
        }
    }
    // Left part
    for (int row = boundary.y; row < boundary.y + boundary.height; row++)
    {
        for (int column = 0; column < 16; column++ )
        {
            thresholdedImage.at<int>(row,column) = 0;
        }
    }
    
    // right part
    for (int row = boundary.y; row < boundary.y + boundary.height; row++)
    {
        for (int column = width-1; column > width - 17; column-- )
        {
            thresholdedImage.at<int>(row,column) = 0;
        }
    }
    

    // Perform closing to remove holes of the image
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(thresholdedImage, thresholdedImage, MORPH_CLOSE, element);
    imshow("thresholded gray", thresholdedImage);
    
    thresholdedImage1 = 255 - thresholdedImage;
    // Convert the gray image back to RGB to get the original image
    cvtColor(thresholdedImage1, thresholdedColor, COLOR_GRAY2BGR);
    
    //Draw contours
    thresholdedImage.copyTo(duplicateThresholdedImage);
    findContours(duplicateThresholdedImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    // Draw rectangular boundaries around each segment of the image and also store the x,y,width,height of every ROI
    int ROILocations[contours.size()][4];//To store x,y,height and width
    for (int i = 0; i < contours.size(); i++)
    {
        boundary = boundingRect(contours[i]);
        //areaOfBoundingBox[i] = boundary.width * boundary.height;
        //perimeterOfBoundingBox[i] = 2 * (boundary.width + boundary.height);
        rectangle(thresholdedColor, boundary, Scalar(255,0,0),2,8,0);
        ROILocations[i][0] = boundary.x;
        ROILocations[i][1] = boundary.y;
        ROILocations[i][2] = boundary.width;
        ROILocations[i][3] = boundary.height;
    }
    namedWindow("Display window", CV_WINDOW_AUTOSIZE);
    imshow("Display window", thresholdedColor);
    waitKey(0);
    destroyAllWindows();
    
    
    //FEATURE EXTRACTION
    int x, y, newHeight, newWidth;
    int verticalCenter, countVertical, horizontalCenter, countHorizontal, bottom, countBottom;
    int verticalIntersections[contours.size()];
    int horizontalIntersections[contours.size()];
    int bottomIntersections[contours.size()];
    double symmetry[contours.size()];
    double objectPixelsFirst10Rows[contours.size()];
    double objectPixelsLast10Rows[contours.size()];
    double objectPixelsFirst10Columns[contours.size()];
    int eulerNumber[12] = {1,0,1,1,1,1,1,0,0,1,1,1};
    int eulerCalculated[contours.size()];
    int equal, objectPixels;
    
    for (int index = 0; index < contours.size(); index++)
    {
        x = ROILocations[index][0];
        y = ROILocations[index][1];
        newWidth = ROILocations[index][2];
        newHeight = ROILocations[index][3];
        unsigned char segment[newHeight][newWidth];
        int i = y;
        for (int row = 0; row < newHeight; row++)
        {
            int j = x;
            for (int column = 0; column < newWidth; column++)
            {
                segment[row][column] = 255 - thresholdedImage.at<uchar>(i,j);
                j = j + 1;
            }
            i = i + 1;
        }
        
        Mat segmentedImage = Mat(newHeight, newWidth, CV_8UC1, segment);
        for (int row = 0; row < newHeight; row++)
        {
            for (int column = 0; column < newWidth; column++)
            {
                segment[row][column] = segmentedImage.at<uchar>(row,column);//Now store the thresholded image
            }
        }
        if (!(file=fopen(argv[index + 2],"wb")))
        {
            cout << "Cannot open file: " << argv[index + 2] << endl;
            exit(1);
        }
        fwrite(segment, sizeof(unsigned char), newHeight*newWidth, file);
        fclose(file);
        //Convert it to 0 and 1
        int binarySegment[newHeight][newWidth];
        for (int row = 0; row < newHeight; row++)
        {
            for (int column = 0; column < newWidth; column++)
            {
                if (segment[row][column] == 255)
                    binarySegment[row][column] = 1;
                else if (segment[row][column] == 0)
                    binarySegment[row][column] = 0;
            }
        }
        
        //Euler number calculation
        int newHeight1 = newHeight + 2;
        int newWidth1 = newWidth + 2;
        int imageData[newHeight1][newWidth1];
        for (int row = 0; row < newHeight1; row++)
        {
            for(int column = 0; column < newWidth1; column++)
            {
                imageData[row][column] = 0;
            }
        }
        for (int row = 1; row < newHeight1-1; row++)
        {
            for (int column = 1; column < newWidth1-1; column++)
            {
                imageData[row][column] = 1-binarySegment[row-1][column-1];
            }
        }
        int currentWindow[4];
        int count1 = 0;
        int count3 = 0;
        int countd = 0;
        for (int row = 0; row < newHeight1-1; row++)
        {
            for (int column = 0; column < newWidth1-1; column++)
            {
                currentWindow[0] = imageData[row][column];
                currentWindow[1] = imageData[row][column+1];
                currentWindow[2] = imageData[row+1][column];
                currentWindow[3] = imageData[row+1][column+1];
                int count = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (currentWindow[i] == 1)
                        count = count + 1;
                }
                if (count == 1)
                    count1=count1+1;
                
                if (count == 3)
                    count3=count3+1;
                
                if ((currentWindow[0]==1 && currentWindow[1]==0 && currentWindow[2]==0 && currentWindow[3]==1) || (currentWindow[0]==0 && currentWindow[1]==1 && currentWindow[2]==1 && currentWindow[3]==0))
                    countd=countd+1;
            }
        }
        eulerCalculated[index] = 0.25*(count1-count3-2*countd);
        
        // Draw a vertical line dividing the image and count the number of intersactions
        verticalCenter = newWidth/2;
        if (binarySegment[0][verticalCenter] == 0)
            countVertical = 1; //Starts with a black object
        else
            countVertical = 0; // Starts with the white background
        for (int row = 1; row < newHeight; row++)
        {
            if (binarySegment[row][verticalCenter] == 0 & binarySegment[row-1][verticalCenter] == 1)
                countVertical = countVertical + 1;
        }
        verticalIntersections[index] = countVertical;
        
        // Draw a horizontal line dividing tha image and count the number of intersections
        horizontalCenter = newHeight/2;
        if (binarySegment[horizontalCenter][0] == 0)
            countHorizontal = 1;
        else
            countHorizontal = 0;
        for (int column = 1; column < newWidth; column++)
        {
            if (binarySegment[horizontalCenter][column] == 0 & binarySegment[horizontalCenter][column-1] == 1)
                countHorizontal = countHorizontal + 1;
        }
        horizontalIntersections[index] = countHorizontal;
        
        //Draw a horizontal line at the bottom to count the number of intersections
        bottom = newHeight-1;
        if (binarySegment[bottom][0] == 0)
            countBottom = 1;
        else
            countBottom = 0;
        for (int column = 1; column < newWidth; column++)
        {
            if (binarySegment[bottom][column] == 0 & binarySegment[bottom][column-1] == 1)
                countBottom = countBottom + 1;
        }
        bottomIntersections[index] = countBottom;

        
        // Check if the object is symmetric aling the horizontal axis of symmetry
        equal = 0;
        for (int row = 0; row < horizontalCenter; row ++)
        {
            for (int column = 0; column < newWidth; column++)
            {
                if (binarySegment[horizontalCenter-row][column] == binarySegment[horizontalCenter+row][column])
                    equal = equal + 1;
            }
        }
        symmetry[index] = (double(equal)/double((newWidth * newHeight)/2)) * 100;
        
        // Count the number of object pixels in the first 10 rows of the images and compare the count with the width
        objectPixels = 0;
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < newWidth; column++)
            {
                if (binarySegment[row][column] == 0)
                    objectPixels = objectPixels + 1;
            }
        }
        objectPixelsFirst10Rows[index] = (double(objectPixels)/double(10*newWidth)) * 100;
        
        // Count the number of object pixels in the last 10 rows of the images and compare the count with the width
        objectPixels = 0;
        for (int row = newHeight-10; row < newHeight; row++)
        {
            for (int column = 0; column < newWidth; column++)
            {
                if (binarySegment[row][column] == 0)
                    objectPixels = objectPixels + 1;
            }
        }
        objectPixelsLast10Rows[index] = (double(objectPixels)/double(10*newWidth)) * 100;
                
        // Count the number of object pixels in the first 10 columns of the images and compare the count with the height
        objectPixels = 0;
        for (int row = 0; row < newHeight; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (binarySegment[row][column] == 0)
                    objectPixels = objectPixels + 1;
            }
        }
        objectPixelsFirst10Columns[index] = (double(objectPixels)/double(10*newHeight)) * 100;
    }
    
    // DECISION TREE
    char label[contours.size()];
    //FOR EULER NUMBER
    for (int index = 0; index < contours.size(); index++)
    {
        if (eulerNumber[index] == -1)
            label[index] = 'i'; //FINAL------------------------------
        else if (eulerNumber[index] == 0)
            label[index] = 0;
        else if (eulerNumber[index] == 1)
            label[index] = 1;
    }
    //FOR VERTICAL INTERSECTIONS
    for (int index = 0; index < contours.size(); index++)
    {
        if (label[index] == 0)
        {
            if (verticalIntersections[index] == 2)
                label[index] = 2;
            else if (verticalIntersections[index] == 3)
                label[index] = 3;
        }
        
        else if (label[index] == 1)
        {
            if (verticalIntersections[index] == 1)
                label[index] = 4;
            else if (verticalIntersections[index] == 2)
                label[index] = 'h'; //FINAL--------------------------
            else if (verticalIntersections[index] == 3)
                label[index] = 5;
        }
    }
    //FOR HORIZONTAL INTERSECTIONS AND FIRST 10 COLUMNS
    for (int index = 0; index < contours.size(); index++)
    {
        if (label[index] == 2)
        {
            if (horizontalIntersections[index] == 1)
                label[index] = 'l'; //FINAL-------------------------
            else if (horizontalIntersections[index] == 2)
                label[index] = 6;
        }
        else if (label[index] == 3)
        {
            if (objectPixelsFirst10Columns[index] > 60)
                label[index] = 'g'; //FINAL-------------------------
            else if (objectPixelsFirst10Columns[index] < 60)
                label[index] = 'j'; //FINAL-------------------------
        }
        else if (label[index] == 4)
        {
            if (horizontalIntersections[index] == 1)
                label[index] = 7;
            else if (horizontalIntersections[index] == 4)
                label[index] = 'q'; //FINAL-------------------------
            
        }
        else if (label[index] == 5)
        {
            if (horizontalIntersections[index] == 1)
                label[index] = 8;
            else if (horizontalIntersections[index] == 2)
                label[index] = 'f'; //FINAL-------------------------
        }
    }
    //FOR SYMMETRY AND BOTTOM INTERSECTIONS COUNT
    for (int index = 0; index < contours.size(); index++)
    {
        if (label[index] == 6)
        {
            if (symmetry[index] > 95.5)
                label[index] = 'a'; //FINAL-------------------------
            else if (symmetry[index] < 95.5)
                label[index] = 9;
        }
        else if (label[index] == 7)
        {
            if (symmetry[index] > 90)
                label[index] = 'p'; //FINAL-------------------------
            else if (symmetry[index] < 90)
                label[index] = 10;
            if (bottomIntersections[index] != 1)
                label[index] = 'q'; //second case FINAL-------------
        }
        else if (label[index] == 8)
        {
            if (symmetry[index] > 75)
                label[index] = 11;
            else if (symmetry[index] < 75)
                label[index] = 13;
        }
        
    }
    //FOR FIRST 10 ROWS
    for (int index = 0; index < contours.size(); index++)
    {
        if (label[index] == 9)
        {
            if (objectPixelsFirst10Rows[index] > 50)
                label[index] = 'n'; //FINAL-------------------------
            else if (objectPixelsFirst10Rows[index] < 50)
                label[index] = 'e'; //FINAL-------------------------
        }
        else if (label[index] == 10)
        {
            if (objectPixelsFirst10Rows[index] > 50)
                label[index] = 'r'; //FINAL------------------------
            else if (objectPixelsFirst10Rows[index] < 50)
                label[index] = 12;
        }
        else if (label[index] == 11)
        {
            if (objectPixelsFirst10Rows[index] > 65)
                label[index] = 'm'; //FINAL------------------------
            else if (objectPixelsFirst10Rows[index] < 65)
                label[index] = 'd'; //FINAL------------------------
        }
    }
    //FOR LAST 10 ROWS
    for (int index = 0; index < contours.size(); index++)
    {
        if (label[index] == 12)
        {
            if (objectPixelsLast10Rows[index] > 50)
                label[index] = 'o'; //FINAL-----------------------
            else if (objectPixelsLast10Rows[index] < 50)
                label[index] = 'b'; //FINAL-----------------------
        }
        else if (label[index] == 13)
        {
            if (objectPixelsLast10Rows[index] > 75)
                label[index] = 'c'; //FINAL-----------------------
            else if (objectPixelsLast10Rows[index] < 75)
                label[index] = 'k'; //FINAL-----------------------
        }
        
    }
    cout << "THE EXTRACTED FEATURES ARE SHOWN BELOW" << endl;
    for (int index = 0; index < contours.size(); index++)
    {
        cout << eulerNumber [index] <<"\t" <<  verticalIntersections[index] <<"\t" <<  horizontalIntersections[index] << "\t" << symmetry[index] << "\t" << objectPixelsFirst10Rows[index] <<"\t" <<  objectPixelsLast10Rows[index] <<"\t" <<  objectPixelsFirst10Columns [index] <<"\t" <<  label[index] << endl;
    }

    
    

    
    return 0;
}
