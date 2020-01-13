function [ train,test ] = divide(good,bad,num)
% divide_new:从total中随机选取num个好和num个坏作为训练集，剩下的作为测试集
% 输入参数：good，bad分别是好瓶子和坏瓶子的全部敲击信号；num,训练集信号个数
% 输出参数：train:用于训练的信号;test，用于测试的信号

sig_num = length(good(1,:));   % 获取好瓶/坏瓶信号个数，好瓶和坏瓶信号各占一半

% 生成随机数
r = randperm(sig_num);

% 取出随机数组r对应的好瓶和坏瓶组成训练集
train = good(:,r(1:num));      %从好瓶中取数据
train = [train,bad(:,r(1:num))];      %从坏瓶中取数据
test = good(:,r(num+1:sig_num));  %从好瓶中取数据
test = [test,bad(:,r(num+1:sig_num))];      %从坏瓶中取数据

end

