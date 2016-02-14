% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 29 Nov 2015

% Problem 3C
%This code generates the histograms of 4 images using the bag of words
% model
%Extract SIFT features of school bus 1, sedan and bus
I = imread('School_bus1.jpg');
I = single(rgb2gray(I));
[f1,d1] = vl_sift(I);
I = imread('Bus.jpg');
I = single(rgb2gray(I));
[f2,d2] = vl_sift(I);
I = imread('Sedan.jpg');
I = single(rgb2gray(I));
[f3,d3] = vl_sift(I);
% Concatenate all the descriptors
d = cat(2,d1,d2,d3);
% Apply kmeans clustering
[centers, assignments] = vl_kmeans(double(d), 8);
figure;
% Create codeword for school bus 1
k = zeros(1,242);
for i = 1:1:242
[~, k(i)] = min(vl_alldist(double(d1(:,i)), centers)) ;
end
histogram(k);
title('school bus 1');
% Create codeword for bus
figure;
k = zeros(1,412);
for i = 1:1:412
[~, k(i)] = min(vl_alldist(double(d2(:,i)), centers)) ;
end
histogram(k);
title('Bus');
% Create codeword for sedan
figure;
k = zeros(1,269);
for i = 1:1:269
[~, k(i)] = min(vl_alldist(double(d3(:,i)), centers)) ;
end
histogram(k);
title('sedan');

 %Testing phase
 % Extract SIFT features from school bus 2
I = imread('School_bus2.jpg');
I = single(rgb2gray(I));
[f4,d4] = vl_sift(I);
% Codeword
figure;
k = zeros(1,215);
for i = 1:1:215
[~, k(i)] = min(vl_alldist(double(d4(:,i)), centers)) ;
end
histogram(k);
title('school bus 2');

