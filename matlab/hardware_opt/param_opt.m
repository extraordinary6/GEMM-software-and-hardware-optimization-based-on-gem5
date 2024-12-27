load('param.mat');

% % 创建图形
% figure;
% 
% % 绘制柱状图
% bar(run_time, 'FaceColor', '#94C6CD'); % 设置柱子颜色
% ylabel('运行时间 (s)');
% title('运行时间');
% 
% % 设置x轴
% xticks(1:8);
% xticklabels(methods);
% xlabel('方法');
% 
% % 在柱子上方显示数值
% for i = 1:length(run_time)
%     text(i, run_time(i) + 0.05, num2str(run_time(i), '%.6f'), 'HorizontalAlignment', 'center', 'Color', 'k', 'FontSize', 7);
% end
% 
% % 调整y轴范围
% ylim([0, max(run_time) + 0.1]);
% 
% % 显示网格
% grid on;
% 
% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'runtime_param_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式

% % 创建图形
% figure;
% 
% % 绘制折线图
% plot(l2cache_miss_rate1, '-o', 'Color', '#E29135', 'LineWidth', 2); % 设置折线颜色
% ylabel('L2CACHE Miss Rate');
% xlabel('Methods');
% title('L2CACHE Miss Rate for Different Methods');
% 
% % 在折线图上方显示数值
% for i = 1:length(l2cache_miss_rate1)
%     text(i, l2cache_miss_rate1(i) + 0.05, num2str(l2cache_miss_rate1(i), '%.6f'), 'Color', '#E29135', 'HorizontalAlignment', 'center');
% end
% 
% ylim([0, max(l2cache_miss_rate1) + 0.1]);
% 
% % 设置x轴
% xticks(1:4);
% xticklabels(methods_1);
% 
% % 显示网格
% grid on;
% 
% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'l2cache_param_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式

% 创建图形
figure;

% 绘制折线图
plot(l1cache_miss_rate, '-o', 'Color', '#F09BA0', 'LineWidth', 2); % 设置折线颜色
ylabel('L1CACHE Miss Rate');
xlabel('Methods');
title('L1CACHE Miss Rate for Different Methods');

% 在折线图上方显示数值
for i = 1:length(l1cache_miss_rate)
    text(i, l1cache_miss_rate(i) + 0.002, num2str(l1cache_miss_rate(i), '%.6f'), 'Color', '#F09BA0', 'HorizontalAlignment', 'center');
end

% 设置x轴
xticks(1:5);
xticklabels(methods_2);

% 显示网格
grid on;

output_folder = '../../../picture';
output_file = fullfile(output_folder, 'l1dcache_param_chart.png');
saveas(gcf, output_file);          % 保存图像为PNG格式


