function generateFakeData(nbSignals, amplitudeSignal, freqSignal, duration, samplingFreq, outFilename, plt)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function generateFakeData(nbSignals, amplitudeSignal, freqSignal, duration, samplingFreq, outFilename, plt)
%ex.: generateFakeData(5, [1 1 1 1 1], [0.5 1 2 3 4], 2, 10, '../data/fakeData.txt', 1)
%
% Aim: To generate fake data for the Arduino Simulator
%
% Inputs:
%	- nbSignals : filter order
%	- amplitudeSignal: amplitude of the signals
%	- freqSignal: frequency of the signals (in Hz)
%	- duration: duration of the signals (in seconds)
%	- samplingFreq: sampling frequency (in Hz)
%	- outFilename: filename where to store the fake data
%	- plt: if set to 1 display the generated signals
%
% Ouput: None
%
% Guillaume Gibert 
% 09/04/2020
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% generates a series of  timestamps
t=0:1/samplingFreq:duration;

% generates the signals
generatedSignals = [];
for l_signal=1:nbSignals
	generatedSignals = [generatedSignals; amplitudeSignal(l_signal)*sin(2*pi*freqSignal(l_signal)*t)];
end

% saves the fake data as a text file
fid = fopen(outFilename, 'w');
if (fid)
	fprintf(fid, 'fps: %d\n', samplingFreq);
	
	for (l_sample = 1:size(generatedSignals,2))
		fprintf(fid, 'data: Sensor:|');
		for (l_signal = 1:size(generatedSignals,1))
			fprintf(fid, '%2.4f|', generatedSignals(l_signal, l_sample));
		end
		fprintf(fid, '\n');
	end
		
	fclose(fid);
end

% plots the fake data
if (plt)
	figure;

	plot(t, generatedSignals); 
end


 
 
 
 
 
  