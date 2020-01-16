% EMD_TRIANG.M
%
% P. Flandrin, Mar. 13, 2003
%
% computes and displays EMD for the sum of 2 triangular 
% waveforms + 1 tone 
%
% produces Figure 2 in
%
% G. Rilling, P. Flandrin and P. Gon�alv�s
% "On Empirical Mode Decomposition and its algorithms"
% IEEE-EURASIP Workshop on Nonlinear Signal and Image Processing
% NSIP-03, Grado (I), June 2003

N = 1024;% # of data samples
t = 1:N;

% triangular waveform 1
p1 = fix(N/6);% period
x1 = triang(N,p1);

% tone
f0 = 0.03;% frequency
x2 = real(fmconst(N,f0));

% triangular waveform 2
p3 = 5;% period
x3 = triang(N,p3);

x = x1 + 0.4*x2' + .4*x3;

[imf,ort,nbits] = emd(x,t,[0.05,0.5,0.05]);

emd_visu(x,t,imf,1);

figure(1)
