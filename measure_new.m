function [ A,P,R,F ] = measure_new(output, label)
% measure:���ã�ͨ��ѵ���Ͳ��Ե�����������ǵ�׼ȷ�ʣ���ȷ�ʣ��ٻ��ʣ�F-ֵ����ʵ���Ի�ƿ��Ϊ����
% ���룺output�������δ���ֵ�0��1��
%       label,Ϊ�����ı�ǩ�����ݸ�ʽ��[������]*[1]
% �����A,׼ȷ��(accuracy),P,��ȷ��(percision)��R,�ٻ���(recall),F(F-measure)

% pre = output;
%% ������0��1
output(output >= 0.5) = 1;
output(output < 0.5) = 0;

%% ����TP,FP,TN,FN
N = length(output); %������������ƿ����Ϊl/2����ƿ����Ϊl/2
TN = 0;   % ����ĺ�ƿ����ģ��Ԥ��Ϊ���ĸ�������
TP = 0;   % ����Ļ�ƿ����ģ��Ԥ��Ϊ������������
FN = 0;   % ��Ϊ��ƿ�Ļ�ƿ����ģ��Ԥ��Ϊ������������
FP = 0;   % ��Ϊ��ƿ�ĺ�ƿ����ģ��Ԥ��Ϊ���ĸ�������

for i=1:N
    % ���Ϊ��ƿ
    if output(i)==1
        if label(i,1)==1
            TN = TN + 1;
        else
            FN = FN + 1;
%             fprintf('��%d���������ݣ�Ԥ��ֵ %f\n',i,pre(i));
        end
    else
        if label(i,1)==0
            TP = TP + 1;
        else
            FP = FP + 1;
%             fprintf('��%d���������ݣ�Ԥ��ֵ %f\n',i,pre(i));
        end    
    end
end

% fprintf('======================================================');

%% ����A,P,R,F,�ٷֱ���
A = (TP+TN)*100/(TP+TN+FN+FP);
P = TP*100/(TP+FP);
R = TP*100/(TP+FN);
F = 2*TP*100/(2*TP+FN+FP);

end