clear

x_0 = 0;
x_1 = 2;

points = 1001;
m = 15;
E = zeros(1, m); 

for i = 0:m
    Puntos = zeros([1 2^i+1]);
    Puntos(1) = x_0; 
    
    for j = 2:2^i
        Puntos(j) = Puntos(j-1) + (x_1 - x_0)/(2^i);
    end
    
    Puntos(end) = x_1; 
    EI = zeros([1 2^i]); 
    
    for j = 1:2^i
        x = linspace(Puntos(j), Puntos(j+1), points); 
        f = exp(x); 

        phi_L = (x - Puntos(j+1))/(Puntos(j) - Puntos(j+1)); 
        phi_R = (x - Puntos(j))/(Puntos(j+1) - Puntos(j)); 

        P = f(1)*phi_L + f(end)*phi_R; 
        EI(j) = sqrt(sum((f - P).^2)); 
    end
    
    E(i+1) = (sum(EI))^2; 
end

A = E(1:end - 1)./E(2:end) 

disp(A(end))