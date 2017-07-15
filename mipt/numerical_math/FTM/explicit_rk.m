function [t, x] = explicit_rk (func,ro, initial)
N = 100;
h = (ro(2) - ro(1))/(2*N);
t = ro(1):h:ro(2);
x = zeros(3,length(t));
x(:,1) = initial;
for i=1:(length(t)-1)                          
    k1 = func(t(i),x(:,i));
    k2 = func(t(i)+h,x(:,i)+h*k1);
    x(:,i+1) = x(:,i) + h/2*(k1 + k2);
end
end