function sigma = sigma_interpolate (x)
data_x = [15, 21, 26, 30, 35, 43, 55,64];
data_y = [-11.17,-11.2,-11.24,-11.265, -11.285, -11.29, -11.3,-11.3];
x_d = linspace(15,70,20);
x_d = x_d.*1e5;
data_x = data_x.*1e5;
if x < 15
    y = -12;
else
    y = spline(data_x, data_y, x);
end;
sigma = 10.^y;

end