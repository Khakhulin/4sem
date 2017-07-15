%Return the solve of equation if format:
%X - matrix that contatins in raw solve of corresponding solve
function [t, x] = implicit_rk (func, ro, initial)
t = ro;
N = 100;
h_old = (ro(2) - ro(1))/(N)
h = h_old;
h_new = h/10;
ro_mid = ro(2)/10;
t_1 = ro(1):h_new:ro_mid;
t_2 = ro_mid:h:ro(2);
x = zeros(3,length(ro));
x(:,1) = initial;
a22 = 1/2 + 1/(2*sqrt(3));
a21 = -1/sqrt(3);
a11 = a22;
c1 = 1/2 + 1/(2*sqrt(3));
c2 = 1/2 - 1/(2*sqrt(3));
t = [t_1, t_2];
for i=1:(length(t)-1) 
  if i < length(t_1)
    h = h_new;
  else
    h = h_old;
  end 
   %options = optimoptions('fsolve','Display','iter','UseParallel', 'true');
   func1 = @(k) k - func(t(i)+c1*h,x(:,i) + h*a11*k);  
   k1 = fsolve(func1, func(t(i),x(:,i)));
   %k1  = solver_eq_hord(func1, func(t(i),x(:,i)))
   func2 = @(k) k - func(t(i)+c2*h,x(:,i) + h*a21*k1 + h*a22*k);  
   %k2 = solver_eq_hord(func2, func(t(i),x(:,i)))
   k2 = fsolve(func2, func(t(i),x(:,i)));
   x(:,i+1) = x(:,i) + h/2*(real(k1) + real(k2));
   end
end
