%% 清除
clc;close all;clear;
tic

%% 载入数据
load init_data/bad;
load init_data/good;
% total = [good,bad]; %将1000个好的和1000个坏的放在一起
fs = 48000;

%% 选训练集和测试集
[M, N] = size(good);
num = 600;      % 600个好瓶和600个坏瓶进行训练，400个好的和400个坏的用于测试
[train_sig, test_sig] = divide_byTime(good,bad,num);

trainl = [ones(num,1);zeros(num,1)];
testl = [ones(N-num,1);zeros(N-num,1)];

%% 保存数据集
rootPath = './development_splitByTime/';
isFoldExist(rootPath);
isFoldExist([rootPath, 'developemt/']);

save([rootPath, 'developemt/train_sig.mat'],'train_sig');
save([rootPath, 'trainl.mat'], 'trainl');
save([rootPath, 'developemt/test_sig.mat'],'test_sig');
save([rootPath, 'testl.mat'], 'testl');