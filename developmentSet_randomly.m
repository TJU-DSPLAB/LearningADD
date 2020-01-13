%% ���
clc;close all;clear;
tic

%% ��������
load init_data/bad;
load init_data/good;
fs = 48000;

%% ѡѵ�����Ͳ��Լ�
[M, N] = size(good);
num = 600;      % 600����ƿ��600����ƿ����ѵ����400���õĺ�400���������ڲ���
[train_sig, test_sig] = divide_byTime(good,bad,num);

trainl = [ones(num,1);zeros(num,1)];
testl = [ones(N-num,1);zeros(N-num,1)];

%% �������ݼ�
rootPath = './development_splitRandomly/';
isFoldExist(rootPath);
isFoldExist([rootPath, 'developemt/']);

save([rootPath, 'developemt/sig_train.mat'],'train_sig');
save([rootPath, 'trainl.mat'], 'trainl');
save([rootPath, 'developemt/sig_test.mat'],'test_sig');
save([rootPath, 'testl.mat'], 'testl');