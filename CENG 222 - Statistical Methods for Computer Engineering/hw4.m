numberOfRuns = 4148;
TotalWeight = zeros(numberOfRuns, 1);
lambdaAuto = 50;
lambdaTruck = 10;
a1 = 190;
a2 = 110;
l1 = 0.15;
l2 = 0.01;

for a = 1:numberOfRuns;
    // calculate the probability density function for the number of cars and trucks
    f1 = exp(-lambdaAuto);
    f2 = exp(-lambdaTruck);
    weightAuto = 0;
    weightTruck = 0;
    
    // calculate the number of cars and trucks
    i = 0;
    u = rand;
    while(u >= f1);
        i = i + 1;
        f1 = f1 + exp(-lambdaAuto) * (lambdaAuto^i / gamma(i+1)); 
    end;
    totalNoOfAuto = i;
    
    i = 0;
    % u = rand;
    while(u >= f2);
        i = i + 1;
        f2 = f2 + exp(-lambdaTruck) * (lambdaTruck^i / gamma(i+1)); 
    end;
    totalNoOfTruck = i;
    
    // calculate the weight of the cars and trucks
    for n = 1:totalNoOfAuto;
        weightAuto = weightAuto + sum(-1/l1 * log(rand(a1,1)));
    end;
    
    for m = 1:totalNoOfTruck;
        weightTruck = weightTruck + sum(-1/l2 * log(rand(a2,1)));
    end;
    TotalWeight(a) = weightAuto + weightTruck;
end;

// calculate the probability that the total weight is greater than 200000
p_est = mean(TotalWeight > 200000);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);

// print the results
fprintf('Estimated probability = %f\n', p_est);
fprintf('Expected weight = %f\n', expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight); 

