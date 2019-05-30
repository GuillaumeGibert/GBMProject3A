function generateLowPassFilterCoefficients(order, cutoffFreq, samplingFreq, outFilename, plt)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function generateLowPassFilterCoefficients(order, cutoffFreq, samplingFreq, outFilename, plt)
%ex.: generateLowPassFilterCoefficients(6, 3, 100, 'coef.txt', 1)
%
% Aim: To generate the coefficients of a low-pass Butterworth filter
%
% Inputs:
%	- order : filter order
%	- cutoffFreq: cutoff frequency of the low pass filter (Hz)
%	- samplingFreq: sampling frequency (Hz)
%	- outFilename: filename where to store the coefficients
%	- plt: if set to 1 below/above frequency sine signals will be displayed and their associated filtered signals 
%
% Ouput: None
%
% Guillaume Gibert 
% 27/05/2019
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% loads signal package (for octave)
pkg load signal;

% generates the filter coefficients
[b, a] = butter(order, cutoffFreq/(samplingFreq/2));

% saves the coeffcients
fid = fopen(outFilename, 'w');
if (fid)
	fprintf(fid, 'l_aFilterCoefs = {');
	for (l_coef = 1:length(a))
		fprintf(fid, '%2.40ff,\t', a(l_coef));
	end
	fprintf(fid, ']\n');
	
	fprintf(fid, 'l_bFilterCoefs = {');
	for (l_coef = 1:length(b))
		fprintf(fid, '%2.40ff,\t', b(l_coef));
	end
	fprintf(fid, '};\n');
	
	fclose(fid);
end


if (plt)
	figure;

	% generates a series of  timestamps
	t=0:1/samplingFreq:2;
	
	% generates a sine signal below the cutoff frequency
	fsin = cutoffFreq / 2;
	x = 50*sin(2*pi*fsin*t);
	
	% filters it
	y = filter (b, a, x);
	
	% plots it
	subplot(1,3,1);
	plot(x, 'b'); hold on;
	plot(y, 'r');
	
	% generates a sine signal above the cutoff frequency
	fsin = cutoffFreq;
	x = 50*sin(2*pi*fsin*t);
	
	% filters it
	y = filter (b, a, x);
	
	% plots it
	subplot(1,3,2);
	plot(x, 'b'); hold on;
	plot(y, 'r');
	
	% generates a sine signal above the cutoff frequency
	fsin = cutoffFreq + (cutoffFreq + samplingFreq/2) / 2 ;
	x = 50*sin(2*pi*fsin*t);
	
	% filters it
	y = filter (b, a, x);
	
	% plots it
	subplot(1,3,3);
	plot(x, 'b'); hold on;
	plot(y, 'r');
	
end


 
 
 
 
 
  