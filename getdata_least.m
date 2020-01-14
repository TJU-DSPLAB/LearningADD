function [traindata, B] = getdata_least(traind, m)
% 相比于原始的getdata函数，因为增加了基于HHT-WPT的42个特征，要修改一下策略
% traindata为从已有的(800*816)的testd.mat数据中选取m为维特征的样本数据
% m选n，m是初始特征集的维度
N = length(traind(1,:));
num = N - 735;  % 整个信号的特征有89个，分别包括HHT-WPT特征42个和常规特征47
if m<num
   % 必选的特征，一共9个
   A = [[736 741 771] [778:783]];
   a = randperm(num);
   a = delete_same(a,A-735);
   B = [A 735+a(1:m-9)];
   traindata = traind(:,B);   % 取后面78个特征中的m个特征
else 
   a = randperm(735);
   B = [a(1:m-num) [736:N]];
   traindata = traind(:,B);   % 取后面89个特征中的m个特征    
end

end

function data = delete_same(arr1,arr2)
data = [];
length1 = length(arr1);
length2 = length(arr2);
C = [];
for i = 1:length1
    for j = 1:length2
        if arr1(i)==arr2(j)
            C = [C i];
            break;
        end
    end
end
for k = 1:length1
    if ~ismember(k,C)
        data = [data arr1(k)];
    end
end
    
end