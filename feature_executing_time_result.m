%% ��������
% �����������е�������ȡ
load time/efficiency_performance1
% �ʼǱ������е�������ȡ
load time/efficiency_performance2

y1 = efficiency_performance1(9:11,:)';
y2 = efficiency_performance2(9:11,:)';
x = [1; 2; 3; 4];

figure(1)
bar(x,y1)
xlabel('strategy'); %����x y������
ylabel('executing time(s)'); 
legend('trainiing time','executing time', 'Total time');
% grid on;

figure(2)
bar(x,y2)
xlabel('strategy'); %����x y������
ylabel('executing time'); 
legend('trainiing time','executing time', 'Total time');
% grid on;

% figure
% bar(x,[y1,y2])
% xlabel('strategy'); %����x y������
% ylabel('executing time'); 
% legend('trainiing time','executing time', 'Total time','trainiing time','executing time', 'Total time');

