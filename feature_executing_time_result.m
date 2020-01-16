%% 加载数据
% 服务器上运行的特征提取
load time/efficiency_performance1
% 笔记本上运行的特征提取
load time/efficiency_performance2

y1 = efficiency_performance1(9:11,:)';
y2 = efficiency_performance2(9:11,:)';
x = [1; 2; 3; 4];

figure(1)
bar(x,y1)
xlabel('strategy'); %设置x y轴名称
ylabel('executing time(s)'); 
legend('trainiing time','executing time', 'Total time');
% grid on;

figure(2)
bar(x,y2)
xlabel('strategy'); %设置x y轴名称
ylabel('executing time'); 
legend('trainiing time','executing time', 'Total time');
% grid on;

% figure
% bar(x,[y1,y2])
% xlabel('strategy'); %设置x y轴名称
% ylabel('executing time'); 
% legend('trainiing time','executing time', 'Total time','trainiing time','executing time', 'Total time');

