function plots = draw_plot_velocity(rk_s, ro, V, po, x_0)
plots = plot(rk_s, log10(ro), V(1,:), log10(po));
xlabel('V/V_0');
ylabel('log(ro)');
set(plots(1), 'LineWidth', 2, 'Color', 'b', 'LineStyle', '-');
set(plots(2), 'LineWidth', 2, 'Color', 'b', 'LineStyle', '--');
legend ('rk method ','analitic', 'location', 'NorthEastOutside');
axis ij;
grid on;
velocity_title = [' Velocity dependence for (V,M,A) = (', num2str(x_0(1)/10e5), ' km/s, ',...
    num2str(x_0(2), '%1.0e'), ' g, pi/', num2str(pi/x_0(3)), ')'];
title(velocity_title)
end