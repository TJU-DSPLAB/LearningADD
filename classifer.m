function [sig_a,sig_p,sig_r,sig_f] = classifer(traind, trainl, testd, testl)
% ʹ��BP�����繹�ɵķ�����

dim = length(traind(1,:));

%% ��������
net = feedforwardnet(2*dim+1);
net.trainFcn = 'trainbfg';
net.trainParam.epochs=1000;%�������ѵ������1000��
net.trainParam.max_fail = 10;
% view(net);

%% ѵ������
net = train(net,traind',trainl');

%% ����
test_out=sim(net,testd');

%% ʵ������ͼ
% N = length(testd(:,1));
% plot([1:N],testl,'r.',[1:N],test_out,'b.');
% xlabel('samples');
% ylabel('predicting value');
% legend('label','prediction');
% grid on;

%% �������
% ȡ��
test_out(test_out>=0.5)=1;
test_out(test_out<0.5)=0;
% �������
[sig_a,sig_p,sig_r,sig_f] = measure_new(test_out, testl);
% [sig_a,sig_p,sig_r,sig_f] = measure(test_out);

end