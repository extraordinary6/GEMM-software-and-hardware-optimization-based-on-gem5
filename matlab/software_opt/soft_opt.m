load('soft_opt.mat');

% % 创建图形并绘制柱状图
% figure;
% bar(run_time, 'FaceColor', [0.2 0.4 0.6]); % 创建柱状图并设置柱子颜色
% 
% % 设置标题和标签
% title('运行时间', 'FontSize', 14); % 标题
% xlabel('方法', 'FontSize', 12);    % x轴标签
% ylabel('时间 (s)', 'FontSize', 12);% y轴标签
% xticks(1:length(methods));         % 设置x轴刻度
% xticklabels(methods);              % 设置x轴刻度标签
% xtickangle(45);                    % 旋转x轴标签避免重叠
% 
% % 限制纵轴范围
% ylim([0.15, 0.55]);                % 设置y轴范围
% 
% % 在柱子上方显示数值
% hold on;
% for i = 1:length(run_time)
%     text(i, run_time(i) + 0.02, sprintf('%.6f', run_time(i)), ...
%          'HorizontalAlignment', 'center', 'FontSize', 10, 'Color', 'k');
% end
% hold off;
% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'runtime_bar_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式


% % 创建图形并绘制柱状图
% figure;
% bar(num_branch, 'FaceColor', [0.8 0.3 0.4]); % 更换柱子的颜色为红色调
% 
% % 设置标题和标签
% title('分支数量', 'FontSize', 14); % 设置标题
% xlabel('方法', 'FontSize', 12);    % 设置x轴标签
% ylabel('分支数量', 'FontSize', 12);% 设置y轴标签
% xticks(1:length(methods));         % 设置x轴刻度
% xticklabels(methods);              % 设置x轴刻度标签
% xtickangle(45);                    % 旋转x轴标签避免重叠
% 
% % 限制纵轴范围（根据需要可调整或移除）
% ylim([200000, 5000000]);                   % 设置y轴范围（根据数据调整）
% 
% % 在柱子上方显示数值
% hold on;
% for i = 1:length(num_branch)
%     text(i, num_branch(i) + 200000, sprintf('%.4g', num_branch(i)), ...
%          'HorizontalAlignment', 'center', 'FontSize', 10, 'Color', 'k');
% end
% hold off;
% 
% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'num_branch_bar_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式

% % 创建图形
% figure;
% 
% % 设置两个y轴
% yyaxis left
% bar(dcache_access_num, 'FaceColor', '#B8DBB3'); % 设置柱子颜色
% ylabel('DCACHE Access Number');
% ylim([33000000, 47000000]);
% 
% % 在柱子上方显示数值
% for i = 1:length(dcache_access_num)
%     text(i, dcache_access_num(i) + 500000, num2str(dcache_access_num(i)), 'HorizontalAlignment', 'center');
% end
% 
% % 设置右侧y轴
% yyaxis right
% plot(dcache_miss_rate, '-o', 'Color', '#E29135', 'LineWidth', 2); % 设置折线颜色
% ylabel('DCACHE Miss Rate');
% ylim([0, 0.1]);
% 
% % 在折线图上方显示数值
% for i = 1:length(dcache_miss_rate)
%     text(i, dcache_miss_rate(i) + 0.006, num2str(dcache_miss_rate(i), '%.6f'), 'Color', '#E29135', 'HorizontalAlignment', 'center');
% end
% 
% % 设置坐标轴标签和标题
% xticks(1:5);
% xticklabels(methods);
% xlabel('Methods');
% title('DCACHE Access Number and Miss Rate');
% 
% % 显示图形
% grid on;
% 
% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'dcache_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式

% 创建图形
figure;

% 设置两个y轴
yyaxis left
bar(l2cache_access_num, 'FaceColor', '#7E99F4'); % 设置柱子颜色
ylabel('L2CACHE Access Number');
ylim([0, 2500000]);

% 在柱子上方显示数值
for i = 1:length(l2cache_access_num)
    text(i, l2cache_access_num(i) + 100000, num2str(l2cache_access_num(i)), 'HorizontalAlignment', 'center', 'Color', '#7E99F4');
end

% 设置右侧y轴
yyaxis right
plot(l2cache_miss_rate, '-o', 'Color', '#F09BA0', 'LineWidth', 2); % 设置折线颜色
ylabel('L2CACHE Miss Rate');
ylim([0, 1.2]);

% 在折线图上方显示数值
for i = 1:length(l2cache_miss_rate)
    text(i, l2cache_miss_rate(i) + 0.05, num2str(l2cache_miss_rate(i), '%.5f'), 'Color', '#F09BA0', 'HorizontalAlignment', 'center');
end

% 设置坐标轴标签和标题
xticks(1:5);
xticklabels(methods);
xlabel('Methods');
title('L2CACHE Access Number and Miss Rate');

% 显示图形
grid on;

% output_folder = '../../../picture';
% output_file = fullfile(output_folder, 'l2cache_chart.png');
% saveas(gcf, output_file);          % 保存图像为PNG格式

