function [ train,test ] = divide_byTime(g_sig,b_sig,num )
% divide_new:��total�����ѡȡnum���ú�num������Ϊѵ������ʣ�µ���Ϊ���Լ�
% ���������total��ȫ���źţ�num,ѵ�����źŸ���
% ���������train:����ѵ�����ź�;test�����ڲ��Ե��ź�

N = length(g_sig(1,:));

% ����ʱ������ѡȡʱ��
train = g_sig(:,[1:num]);
train = [train, b_sig(:,[1:num])];

test = g_sig(:,[num+1:N]);
test = [test, b_sig(:,[num+1:N])];

end

