clear

x_0 = 0;
x_1 = 2;

h = 2;

x = x_0 : 0.0001 : x_1;
f = exp(x);
phi_L = (x - x_1)./(x_0 - x_1);
phi_R = (x - x_0)./(x_1 - x_0);
    
P = f(1)*phi_L + f(end)*phi_R;

E(1) = sqrt((sum((f - P).^2)));
disp(E(1))

%%%%%%%%%%%%%%
%E = zeros([1 n]);   

x = x_0 : 0.0001 : x_1/2;
f = exp(x);
phi_L = 1-x ;
phi_R = x;
    
P = exp(0)*phi_L + exp(1)*phi_R;

E1 = sqrt((sum((f - P).^2)));


x = (x_1)/2: 0.0001 : x_1;
f = exp(x);
phi_L = 2-x;
phi_R = x-1;
    
P = exp(1)*phi_L + f(end)*phi_R;

E2 = sqrt((sum((f - P).^2)));

E(2) = E1 + E2;
disp(E(2))

%%%%%%%%%%%%%%

x = 0 : 0.0001 : 0.5;
f = exp(x);
phi_L = 1-2*x ;
phi_R = 2*x;
    
P = exp(0)*phi_L + exp(0.5)*phi_R;

E1 = sqrt((sum((f - P).^2)));


x = 0.5: 0.0001 : 1;
f = exp(x);
phi_L = 2-2*x;
phi_R = 2*x-1;
    
P = exp(0.5)*phi_L + exp(1)*phi_R;

E2 = sqrt((sum((f - P).^2)));


x = 1 : 0.0001 : 1.5;
f = exp(x);
phi_L = 3-2*x;
phi_R = 2*x-2;
    
P = exp(1)*phi_L + exp(1.5)*phi_R;

E3 = sqrt((sum((f - P).^2)));


x = 1.5: 0.0001 : 2;
f = exp(x);
phi_L = 4-2*x;
phi_R = 2*x-3;
    
P = exp(1.5)*phi_L + exp(2)*phi_R;

E4 = sqrt((sum((f - P).^2)));

E(3) = E1+E2+E3+E4;

disp(E(3))

disp(E(1:end-1)./E(2:end))

%% 
clear

x_0 = 0;
x_1 = 2;

h = 0.001;
m = 1;
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
        x = Puntos(j) : h : Puntos(j+1); 
        f = exp(x); 

        phi_L = (x - Puntos(j+1))/(Puntos(j) - Puntos(j+1)); 
        phi_R = (x - Puntos(j))/(Puntos(j+1) - Puntos(j)); 

        P = f(1)*phi_L + f(end)*phi_R; 
        EI(j) = sqrt(sum((f - P).^2)); 
    end
    
    E(i+1) = sum(EI); 
end

A = E(1:end - 1)./E(2:end) 

disp(A(end))
