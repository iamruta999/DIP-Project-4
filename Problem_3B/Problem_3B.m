% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 29 Nov 2015

% Problem 3B
%This code performs image matching between:
% 1. Schoolbus 1 and schoolbus 2
% 2. Schoolbus 1 and sedan
% 3. Schoolbus 1 and bus
image_1 = imread('School_bus1.jpg');
image_2 = imread('School_bus2.jpg');
[feature_1,d1] = vl_sift(single(rgb2gray(image_1)));
[feature_2,d2] = vl_sift(single(rgb2gray(image_2)));
[matches1, score1] = vl_ubcmatch(d1,d2);
if (size(image_1,1) > size(image_2,1))
    longestWidth = size(image_1,1);       
else
    longestWidth = size(image_2,1);
end
if (size(image_1,2) > size(image_2,2))
    longestHeight = size(image_1,2);
else
    longestHeight = size(image_2,2);
end
% create new matrices with longest width and longest height
newim = uint8(zeros(longestWidth, longestHeight, 3)); 
newim2 = uint8(zeros(longestWidth, longestHeight, 3));
% transfer both images to the new matrices respectively.
newim(1:size(image_1,1), 1:size(image_1,2), 1:3) = image_1;
newim2(1:size(image_2,1), 1:size(image_2,2), 1:3) = image_2;
% with the same proportion and dimension, we can now show both
% images. Parts that are not used in the matrices will be black.
figure;
imshow([newim newim2]);
hold on;
    X = zeros(2,1);
    Y = zeros(2,1);
    % draw line from the matched point in one image to the respective matched point in another image.
    for k=1:numel(matches1(1,:))
        X(1) = feature_1(1, matches1(1, k));
        Y(1) = feature_1(2, matches1(1, k));
        X(2) = feature_2(1, matches1(2, k)) + longestHeight; % for placing matched point of 2nd image correctly.
        Y(2) = feature_2(2, matches1(2, k));
        line(X,Y);
        plot (X(1), Y(1), 'b*');
        plot (X(2), Y(2), 'r*');
    end
    
%Image matching for school bus 1 and sedan
image_1 = imread('School_bus1.jpg');
image_2 = imread('Sedan.jpg');
[feature_1,d1] = vl_sift(single(rgb2gray(image_1)));
[feature_2,d2] = vl_sift(single(rgb2gray(image_2)));
[matches2, score2] = vl_ubcmatch(d1,d2);
if (size(image_1,1) > size(image_2,1))
    longestWidth = size(image_1,1);       
else
    longestWidth = size(image_2,1);
end
if (size(image_1,2) > size(image_2,2))
    longestHeight = size(image_1,2);
else
    longestHeight = size(image_2,2);
end
% create new matrices with longest width and longest height
newim = uint8(zeros(longestWidth, longestHeight, 3)); 
newim2 = uint8(zeros(longestWidth, longestHeight, 3));
% transfer both images to the new matrices respectively.
newim(1:size(image_1,1), 1:size(image_1,2), 1:3) = image_1;
newim2(1:size(image_2,1), 1:size(image_2,2), 1:3) = image_2;
% with the same proportion and dimension, we can now show both
% images. Parts that are not used in the matrices will be black.
figure;
imshow([newim newim2]);
hold on;
    X = zeros(2,1);
    Y = zeros(2,1);
    % draw line from the matched point in one image to the respective matched point in another image.
    for k=1:numel(matches2(1,:))
        X(1) = feature_1(1, matches2(1, k));
        Y(1) = feature_1(2, matches2(1, k));
        X(2) = feature_2(1, matches2(2, k)) + longestHeight; % for placing matched point of 2nd image correctly.
        Y(2) = feature_2(2, matches2(2, k));
        line(X,Y);
        plot (X(1), Y(1), 'b*');
        plot (X(2), Y(2), 'r*');
    end

    %Image matching for school bus 1 and bus
image_1 = imread('School_bus1.jpg');
image_2 = imread('Bus.jpg');
[feature_1,d1] = vl_sift(single(rgb2gray(image_1)));
[feature_2,d2] = vl_sift(single(rgb2gray(image_2)));
[matches3, score3] = vl_ubcmatch(d1,d2);
if (size(image_1,1) > size(image_2,1))
    longestWidth = size(image_1,1);       
else
    longestWidth = size(image_2,1);
end
if (size(image_1,2) > size(image_2,2))
    longestHeight = size(image_1,2);
else
    longestHeight = size(image_2,2);
end
% create new matrices with longest width and longest height
newim = uint8(zeros(longestWidth, longestHeight, 3)); 
newim2 = uint8(zeros(longestWidth, longestHeight, 3));
% transfer both images to the new matrices respectively.
newim(1:size(image_1,1), 1:size(image_1,2), 1:3) = image_1;
newim2(1:size(image_2,1), 1:size(image_2,2), 1:3) = image_2;
% with the same proportion and dimension, we can now show both
% images. Parts that are not used in the matrices will be black.
figure;
imshow([newim newim2]);
hold on;
    X = zeros(2,1);
    Y = zeros(2,1);
    % draw line from the matched point in one image to the respective matched point in another image.
    for k=1:numel(matches3(1,:))
        X(1) = feature_1(1, matches3(1, k));
        Y(1) = feature_1(2, matches3(1, k));
        X(2) = feature_2(1, matches3(2, k)) + longestHeight; % for placing matched point of 2nd image correctly.
        Y(2) = feature_2(2, matches3(2, k));
        line(X,Y);
        plot (X(1), Y(1), 'b*');
        plot (X(2), Y(2), 'r*');
    end


