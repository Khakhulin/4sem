%{
Function to solve non-linear by using hord's method
very slow to find direct root.
%}
function [root] = solver_eq_hord (func, x0)
%func = @(k) k - f(t,x + h*a*k);
%x0 = f(t,x);
root = x0;
%old_root = f(t,x0 + h*a);
old_root = x0*3;
eps = 10e-7;
i = 0;
while (norm((old_root) - (root),2) > 2 * eps)
  i = i + 1;
  if func(root) - func(old_root) ~= 0
    new_root = root - (root - old_root).* func(root)./(func(root) - func(old_root))
    old_root = root;
    root = new_root;
  end
  if i == 50
    break
  end
end
end
