%% ���
clc;close all;clear;
result = []; 
result1 = [];   % FJ��������
tic
% FEATURE_NUM = 200;
% FEATURE_SUB_NUM = 10;

%% ��������
% data_path = './development_splitByTime/';
% root_path = './normalized_data_txt_200_time/';

data_path = './development_splitRandomly/';
root_path = './normalized_data_txt_200_randomly/';

load([data_path 'traind'])
load([data_path 'trainl'])
load([data_path 'testd'])
load([data_path 'testl'])

load([root_path 'B.mat']);
load([root_path '2000/FJ_200_10.txt']);

%% ���������Ӽ��ķ�������

for i = 1:10
    A1 = FJ_200_10(i,:)+1;
    selected1(i,:) = B(:,A1);
     for l = 1:10
        x = traind(:,selected1(i,:));
        y = testd(:,selected1(i,:));
        % ���ڴ�ѭ���Ľ��
        [sig_a1,sig_p1,sig_r1,sig_f1] = classifer(x, trainl, y, testl);
        classifer_training(x, trainl);
        result1 = [result1; sig_a1,sig_p1,sig_r1,sig_f1];

%         % ���ȡ���������
%         % �˴����ص�������./data_features_824
%         FEATURE_NUM = 200;
%         FEATURE_SUB_NUM = 10;
%         % ���ȡǰ200��
%         B = randperm(length(traind(1,:)));
%         B = B(1:FEATURE_NUM);
%         % ���ȡB��ǰ10��
%         a = randperm(FEATURE_NUM);   
%         selected2(i,:) = B(:,a(1:FEATURE_SUB_NUM));
%         x = traind(:,selected2(i,:));
%         y = testd(:,selected2(i,:));
%         [sig_a2,sig_p2,sig_r2,sig_f2] = classifer(x, trainl, y, testl);
%         result = [result; sig_a2,sig_p2,sig_r2,sig_f2];
        
        fprintf('��%d��ʵ�飬��%d��ѭ��\n',i,l);
     end
 
 end
[A, P, R, F] = mean(result1);
F

