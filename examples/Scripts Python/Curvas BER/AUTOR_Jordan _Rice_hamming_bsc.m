% Jordan Rice
% ELEC 476 (Random Signals and Noise)
% Hamming (7,4) Code Simulation 


%Defining Variables for Hamming (7,4) simulation

k = 4;		                % Number of message bits per block
n = 7;		                % Number of codeword bits per block
p_vector = 0.14:0.001:0.15;          % Vector of p values; probability of bit error for BSC
N = length(p_vector);           % Length of p_vector
RUNS = 500;                    % Number of runs


% Codeword Table

xtable =    [0 0 0 0 0 0 0; ...
             1 1 0 1 0 0 0; ...
             0 1 1 0 1 0 0; ...
             1 0 1 1 1 0 0; ...
             1 1 1 0 0 1 0; ...
             0 0 1 1 0 1 0; ...
             1 0 0 0 1 1 0; ...
             0 1 0 1 1 1 0; ...
             1 0 1 0 0 0 1; ...
             0 1 1 1 0 0 1; ...
             1 1 0 0 1 0 1; ...
             0 0 0 1 1 0 1; ...
             0 1 0 0 0 1 1; ...
             1 0 0 1 0 1 1; ...
             0 0 1 0 1 1 1; ...
             1 1 1 1 1 1 1;];

     
for (p_i=1:N)
    
    error = 0;                    % Count the number of errors
    p=p_vector(p_i);
    
    for (r=1:RUNS)           %Generate a block of 4 message bits

        
    z = unifrnd(0, 1, 1, 4);    %Random 4 bit string of 0's and 1's
    w = round(z);               %Round the value of z

        
%Locate the row index, binary to dec. conversion:

    m = w(1) + w(2)*2 + w(3)*4 + w(4)*8;
    x = xtable(m + 1, :);
    z = unifrnd(0, 1, 1, 7);    % Random 7 bit string of 0's and 1's
    zi = find(z <= p);          % Error locations

% Error Vector

    e = zeros(1,7);             % Creates a 7 bit string of 0's
    e(zi) = ones(size(zi));     % Creates a string of 1's the size of z
    y = xor(x,e);               % Exclusive OR your x value and e value 
    
% Approximate the code word

        for(q=1:16)    
        dH(q) = sum(xor(y, xtable(q,:)));   % Compare codeword to received vector
            
            if(dH(q)<=1)      
            wh = xtable(q, 4:7); % wh matches with distance of 1 or less
            end
        end

% Count the number of Errors
        dHw = sum(xor(w,wh));
        error = error + dHw;
    end
    BER(p_i) = error/(RUNS*4);    % Calculate the Bit Error Rate
    P(p_i)=p;                   % Store the value of p 
end



Ps=logspace(-4,0,200);
Pb_high = 1 - ((1-Ps).^7 + 7.*(1-Ps).^6.*Ps);    
Pb_low = (1 - ((1-Ps).^7 + 7.*(1-Ps).^6.*Ps))/k;    



figure(1)
plot(P, BER, 'bx', Ps, Pb_high, 'k-', Ps, Pb_low, 'k-')
legend('Simulated','Analytical')
xlabel('Probability of Error for BSC (p)')
ylabel('BER')
title('Figure 1 - Bit Error Rate for Hamming code over BSC')


figure(2)
loglog(P, BER, 'bx', Ps, Pb_high, 'k-', Ps, Pb_low, 'k-')
legend('Simulated','Analytical')
xlabel('Probability of Error for  BSC (p)')
ylabel('BER')
title('Figure 2 - Bit Error Rate for Hamming code over BSC')