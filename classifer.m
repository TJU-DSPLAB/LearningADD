function [sig_a,sig_p,sig_r,sig_f] = classifer(traind, trainl, testd, testl)
% 使用BP神经网络构成的分类器

dim = length(traind(1,:));

%% 创建网络
net = feedforwardnet(2*dim+1);
net.trainFcn = 'trainbfg';
net.trainParam.epochs=1000;%允许最大训练步数1000步
net.trainParam.max_fail = 10;
% view(net);

%% 训练网络
net = train(net,traind',trainl');

%% 测试
test_out=sim(net,testd');

%% 实验结果画图
% N = length(testd(:,1));
% plot([1:N],testl,'r.',[1:N],test_out,'b.');
% xlabel('samples');
% ylabel('predicting value');
% legend('label','prediction');
% grid on;

%% 结果分析
% 取整
test_out(test_out>=0.5)=1;
test_out(test_out<0.5)=0;
% 评估结果
[sig_a,sig_p,sig_r,sig_f] = measure_new(test_out, testl);
% [sig_a,sig_p,sig_r,sig_f] = measure(test_out);

end