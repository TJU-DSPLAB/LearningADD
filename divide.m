function [ train,test ] = divide(good,bad,num)
% divide_new:��total�����ѡȡnum���ú�num������Ϊѵ������ʣ�µ���Ϊ���Լ�
% ���������good��bad�ֱ��Ǻ�ƿ�Ӻͻ�ƿ�ӵ�ȫ���û��źţ�num,ѵ�����źŸ���
% ���������train:����ѵ�����ź�;test�����ڲ��Ե��ź�

sig_num = length(good(1,:));   % ��ȡ��ƿ/��ƿ�źŸ�������ƿ�ͻ�ƿ�źŸ�ռһ��

% ���������
r = randperm(sig_num);

% ȡ���������r��Ӧ�ĺ�ƿ�ͻ�ƿ���ѵ����
train = good(:,r(1:num));      %�Ӻ�ƿ��ȡ����
train = [train,bad(:,r(1:num))];      %�ӻ�ƿ��ȡ����
test = good(:,r(num+1:sig_num));  %�Ӻ�ƿ��ȡ����
test = [test,bad(:,r(num+1:sig_num))];      %�ӻ�ƿ��ȡ����

end

