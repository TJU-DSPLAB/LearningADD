%% 清除
clc;close all;clear;
tic

%% 将加载的数据保存为txt格式文件
rootPath = './development_splitByTime/';
load([rootPath 'traind.mat'])
load([rootPath 'trainl.mat'])

% 初初始特征集的维度
FEATURE_NUM = 200;

% save_path = './normalized_data_txt_89/';
save_path = ['./normalized_data_txt_' num2str(FEATURE_NUM) '_time/'];
isFoldExist(save_path);

[traind,B] = getdata_least(traind, FEATURE_NUM);
save2txt_1d(B, [save_path, 'B.txt']);

%% 数据处理（1200样本）
traind = normalized(traind);
trainl = trainl*(1-eps);

%% 生成txt文件
%新建文件,你要保存到的文件路径,该路径的最后为'\变量名.txt'
save2txt_2d(traind, [save_path, 'traind.txt'])
save2txt_1d(trainl, [save_path, 'trainl.txt'])
toc
