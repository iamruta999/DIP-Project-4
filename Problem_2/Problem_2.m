% NAME: Amruta Kulkarni
% USC ID: 6914970827
% USC Email: arkulkar@usc.edu
% Submission date: 29 Nov 2015

% Problem 2
%This code extracts level set contours from 4 images
% Level set for spine image
I = imread('spine.pgm');
u = demo_acwe(I, 400);
% Level set for blood_cells image
I = imread('blood_cells.pgm');
u = demo_acwe(I, 600);
% Level set for coronary image
I = imread('coronary.pgm');
u = demo_acwe(I, 600);
% Level set for brain image
I = imread('brian.pgm');
u = demo_acwe(I, 400);
