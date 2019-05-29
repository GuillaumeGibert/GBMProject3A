order = 6;
cutoffFreq = 3;
samplingFreq = 100;



% loads signal package (for octave)
pkg load signal;

% generates the filter coefficients
[b, a] = butter(order, cutoffFreq/(samplingFreq/2));


% generates a series of  timestamps
t=0:1/samplingFreq:10;

% generates a sine signal below the cutoff frequency
fsin =1;
%x = 50*sin(2*pi*fsin*t);
x = [-0.5 -0.4 0.3 -0.2 -0.1 0 0.1 0.2 0.3 0.4 0.5 ]
	
% filters it
y = filter (b, a, x)


% plots it
subplot(1,3,1);
plot(x, 'b'); hold on;
plot(y, 'r');
	
	
	
	