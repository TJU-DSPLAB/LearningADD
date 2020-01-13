function [ train,test ] = divide_byTime(g_sig,b_sig,num )
% divide_new:从total中随机选取num个好和num个坏作为训练集，剩下的作为测试集
% 输入参数：total，全部信号；num,训练集信号个数
% 输出参数：train:用于训练的信号;test，用于测试的信号

N = length(g_sig(1,:));

% 根据时间批次选取时间
train = g_sig(:,[1:num]);
train = [train, b_sig(:,[1:num])];

test = g_sig(:,[num+1:N]);
test = [test, b_sig(:,[num+1:N])];

end

