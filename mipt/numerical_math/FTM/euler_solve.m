function  [t, y] = euler_solve (func, ro, y_0)
t(1) = ro(1);
N = 5000;
h = (ro(2) - ro(1))/N
y = zeros(3);
y(:,1) = y_0;
for n = 1:N
  t(n+1) = t(n) + h;
  d = func(t(n), y(:,n));
  y(:,n+1) = y(:,n) + h*d;
endfor

endfunction
