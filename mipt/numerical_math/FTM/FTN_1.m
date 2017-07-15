%Module to use methods to solve the system
V_0_1 = 20*1e5;
M_0_1 = 1;
theta_0_1 = pi/12;
V_0_2 = 30*1e5;
M_0_2 = 10^6;
M_0_3 = 10^12;
V_0_3 = 70*1e5;
theta_0_2 = pi/6;
x_0 = [V_0_1, M_0_1, theta_0_1];
[d_ro, d_X] =ode23tb(@right_f_de, [10^-8, 1.225e-3], x_0);
%[ro, X] = implicit_rk(@right_f_de, [10^-8, 1.225e-3], x_0);

sigma = 1e-12;
H = 7*10^5;
delta = 3.5;
c_d = 1;
f = 1.21;
M_0 = x_0(2);
V_0 = x_0(1);
theta_0 = x_0(3);
po = linspace(1e-8, 1.225e-3, 10000); 
M = zeros(4,length(po));
V = zeros(4,length(po));
theta = zeros(4,length(po));

for i = 1:4
    sigma = sigma /i;
    A_0 = f*(M_0/delta)^(2/3);
    betta = M_0/(A_0*c_d);
    p = po.*H/(betta*sin(theta_0));
    V_t = V_0*exp(-p./2);
    Me = M_0;
    angle = theta_0_1;
    M_t = M_0*exp(sigma/2*(V_t.^2 - V_0^2));
    V(i,:) = V_t;
    M(i,:) = M_t;
end
draw_plot_velocity(d_X(:,1)./V_0, d_ro, V./V_0, po, x_0)
%draw_plot_angle(X(3,:)./x_0(3), ro, x_0)
return
  
    

    