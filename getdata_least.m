function [traindata, B] = getdata_least(traind, m)
% �����ԭʼ��getdata��������Ϊ�����˻���HHT-WPT��42��������Ҫ�޸�һ�²���
% traindataΪ�����е�(800*816)��testd.mat������ѡȡmΪά��������������
% mѡn��m�ǳ�ʼ��������ά��
N = length(traind(1,:));
num = N - 735;  % �����źŵ�������89�����ֱ����HHT-WPT����42���ͳ�������47
if m<num
   % ��ѡ��������һ��9��
   A = [[736 741 771] [778:783]];
   a = randperm(num);
   a = delete_same(a,A-735);
   B = [A 735+a(1:m-9)];
   traindata = traind(:,B);   % ȡ����78�������е�m������
else 
   a = randperm(735);
   B = [a(1:m-num) [736:N]];
   traindata = traind(:,B);   % ȡ����89�������е�m������    
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