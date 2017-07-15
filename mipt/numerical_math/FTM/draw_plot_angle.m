function plots = draw_plot_angle(rk_s, ro, x_0)
plots = plot(rk_s,log10(ro));
set(plots(1), 'LineWidth', 2, 'Color', 'b', 'LineStyle', '-');
xlabel('Theta_0');
ylabel('log(ro)');
axis ij;
grid on;
legend ('rk method ', 'location', 'NorthEastOutside');
angle_title = [' Angle dependence for (V,M,A) =  ', num2str(x_0(1)/10000), ' km/s, ',...
    num2str(x_0(2), '%1.0e'), ' g, pi/', num2str(pi/x_0(3)), ')'];
title(angle_title);
end