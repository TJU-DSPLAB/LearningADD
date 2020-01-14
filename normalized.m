function data = normalized(data_original)
% measure:���ã�ͨ��ѵ���Ͳ��Ե�����������ǵ�׼ȷ�ʣ���ȷ�ʣ��ٻ��ʣ�F-ֵ����ʵ���Ի�ƿ��Ϊ����
% ���룺output�������δ���ֵ�0��1��
% �����A,׼ȷ��(accuracy),P,��ȷ��(percision)��R,�ٻ���(recall),F(F-measure)

% �����ݳ�ʼ��
[m,n] = size(data_original);
for i = 1:n
    x = data_original(:,i);
    x=x-min(x);
    x=x*(1-eps)/max(x);
    data(:,i) = x;
end


end

