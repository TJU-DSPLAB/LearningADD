%% ���
clc;close all;clear;
tic

%% �����ص����ݱ���Ϊtxt��ʽ�ļ�
rootPath = './development_splitByTime/';
load([rootPath 'traind.mat'])
load([rootPath 'trainl.mat'])

% ����ʼ��������ά��
FEATURE_NUM = 200;

% save_path = './normalized_data_txt_89/';
save_path = ['./normalized_data_txt_' num2str(FEATURE_NUM) '_time/'];
isFoldExist(save_path);

[traind,B] = getdata_least(traind, FEATURE_NUM);
save2txt_1d(B, [save_path, 'B.txt']);

%% ���ݴ���1200������
traind = normalized(traind);
trainl = trainl*(1-eps);

%% ����txt�ļ�
%�½��ļ�,��Ҫ���浽���ļ�·��,��·�������Ϊ'\������.txt'
save2txt_2d(traind, [save_path, 'traind.txt'])
save2txt_1d(trainl, [save_path, 'trainl.txt'])
toc
