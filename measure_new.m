function [ A,P,R,F ] = measure_new(output, label)
% measure:作用，通过训练和测试的输出计算他们的准确率，精确率，召回率，F-值，本实验以坏瓶子为正例
% 输入：output输出（均未划分到0，1）
%       label,为样本的标签，数据格式：[样本量]*[1]
% 输出：A,准确率(accuracy),P,精确率(percision)，R,召回率(recall),F(F-measure)

% pre = output;
%% 划分至0和1
output(output >= 0.5) = 1;
output(output < 0.5) = 0;

%% 计算TP,FP,TN,FN
N = length(output); %总样本数，坏瓶子数为l/2，好瓶子数为l/2
TN = 0;   % 检出的好瓶，被模型预测为负的负样本。
TP = 0;   % 检出的坏瓶，被模型预测为正的正样本。
FN = 0;   % 检为好瓶的坏瓶，被模型预测为负的正样本。
FP = 0;   % 检为坏瓶的好瓶，被模型预测为正的负样本。

for i=1:N
    % 检测为好瓶
    if output(i)==1
        if label(i,1)==1
            TN = TN + 1;
        else
            FN = FN + 1;
%             fprintf('第%d个测试数据，预测值 %f\n',i,pre(i));
        end
    else
        if label(i,1)==0
            TP = TP + 1;
        else
            FP = FP + 1;
%             fprintf('第%d个测试数据，预测值 %f\n',i,pre(i));
        end    
    end
end

% fprintf('======================================================');

%% 计算A,P,R,F,百分比制
A = (TP+TN)*100/(TP+TN+FN+FP);
P = TP*100/(TP+FP);
R = TP*100/(TP+FN);
F = 2*TP*100/(2*TP+FN+FP);

end