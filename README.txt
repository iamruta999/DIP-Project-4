NAME: Amruta Kulkarni
USC ID: 6914-9708-27
E-mail: arkulkar@usc.edu

The following steps will guide you to execute the files that are contained in this folder.

For problem_1A, problem_1B and Problem1_C

1. Create a new project in Xcode, add the path of this project in the custom directory and copy the contents of main_filename.cpp to the main.cpp of that project 
2. Add opencv libraries
3. Copy the respective images in the same folder, for e.g. Problem_1A will need the training.raw image in the same folder as that of the main.cpp file
4. Run the project and then a segmented image will be displayed automatically.
5. Hit enter to get the final results table that contains the OCR labels and the extracted features of the characters
6. Repeat the same process for both the parts of Problem_1B and Problem_1C separately

For Problem2

First convert and save the gray scale images, in MATLAB, to imagename.pgm format using imageJ

Part 1: Snake algorithm

1. Download the source code from the following link:
http://www.mathworks.com/matlabcentral/fileexchange/28109-snakes--active-contour-models
and copy this folder into MATLAB and the add its path
2. Open Matlab and type guide
3. Click on "Go to Existing GUI" 
4. Select the snk.fig file in the same directory as this file 
5. Click the green arrow at the top to launch the GUI
6.  Click on "New Image" and load an input image
7. Set the smoothing parameter "sigma" or leave it at its default value and click "Filter". This will smooth the image. 
8. As soon as you click "Filter", cross hairs would appear and using them and left click of you mouse you can pick initial contour location on the image. A red circle would appear everywhere you click and in most cases you should click all the way around the object you want to segment. The last point must be picked using a right-click in order to stop matlab for asking for more points. 
9.  Set the various snake parameters (relative weights of energy terms in the snake objective function) or leave them with their default value and click "Iterate" button. The snake would appear and move as it converges to its low energy state.

Part 2: Level set algorithm

1. Download the source code from the following link:
http://www.mathworks.com/matlabcentral/fileexchange/34548-active-contour-without-edge
2.Copy this folder into MATLAB and the add its path to the current directory
3. Run the problem_2.m file

For Problem_3A, Problem_3B and Problem_3C

1. Download the VLFEAT library from the following link:
http://www.vlfeat.org/download.html
2. Save this folder on Desktop and name it VLFEATROOT
3. Open MATLAB and type the following command:
run('Add_Your_Path_To_Desktop/VLFEATROOT/toolbox/vl_setup');
4. Now download the SURF source code from the following link:
http://www.mathworks.com/matlabcentral/fileexchange/28300-opensurf--including-image-warp-
5. Add this folder to Matlab and add its path to the current directory
6. Run the files Problem_3A.m, Problem_3B and Problem_3C to get the required results


