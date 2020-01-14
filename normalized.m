function data = normalized(data_original)
% measure:作用，通过训练和测试的输出计算他们的准确率，精确率，召回率，F-值，本实验以坏瓶子为正例
% 输入：output输出（均未划分到0，1）
% 输出：A,准确率(accuracy),P,精确率(percision)，R,召回率(recall),F(F-measure)

% 对数据初始化
[m,n] = size(data_original);
for i = 1:n
    x = data_original(:,i);
    x=x-min(x);
    x=x*(1-eps)/max(x);
    data(:,i) = x;
end


end

