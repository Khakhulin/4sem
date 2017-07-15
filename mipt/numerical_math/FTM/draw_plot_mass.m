function plots = draw_plot_mass(rk_s, ro, M, po, x_0)
plots = plot(rk_s, log10(ro) , M(1,:),log10(po),M(2,:),log10(po),M(3,:), log10(po), M(4,:), log10(po) );
legend ('rk_method ','analitic', 'location', 'NorthEastOutside');
axis ij;
grid on;
xlabel('M/M_0');
ylabel('log(ro)');
%Settings for line on plot
set(plots(1), 'LineWidth', 2, 'Color', 'b', 'LineStyle', '-');
set(plots(2), 'LineWidth', 2, 'Color', 'b', 'LineStyle', '--');
set(plots(3), 'LineWidth', 2, 'Color', 'r', 'LineStyle', '--')
set(plots(4), 'LineWidth', 2, 'Color', 'r', 'LineStyle', '--')
set(plots(5), 'LineWidth', 2, 'Color', 'r', 'LineStyle', '--')
mass_title = [' Mass dependence for (V,M,A) = (', num2str(x_0(1)/10e5), ' km/s, ',...
    num2str(x_0(2), '%1.0e'), ' g, pi/', num2str(pi/x_0(3)), ')'];
title(mass_title);
end