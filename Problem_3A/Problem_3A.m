% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 29 Nov 2015

% Problem 3A
%This code extracts SIFT and SURF features from bus and sedan images
clear all;
clc;
% Extract SIFT features of sedan
I = imread('Sedan.jpg');
figure;
image(I);
I = single(rgb2gray(I));
[f,d] = vl_sift(I);
h1 = vl_plotframe(f(:,:));
h2 = vl_plotframe(f(:,:));
set(h1,'color','k','linewidth',3);
set(h2,'color','y','linewidth',2);
% Extract SIFT features of Bus
I = imread('Bus.jpg');
figure;
image(I);
I = single(rgb2gray(I));
[f,d] = vl_sift(I);
h1 = vl_plotframe(f(:,:));
h2 = vl_plotframe(f(:,:));
set(h1,'color','k','linewidth',3);
set(h2,'color','y','linewidth',2);

% Extract SURF features for sedan
I=imread('Sedan.jpg');
Options.verbose=false; 
Ipts=OpenSurf(I,Options);
PaintSURF(I, Ipts);

% Extract SURF features for bus
I=imread('Bus.jpg');
Options.verbose=false; 
Ipts=OpenSurf(I,Options);
PaintSURF(I, Ipts);

