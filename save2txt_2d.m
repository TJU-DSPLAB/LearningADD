function save2txt_2d(arr, path)
% ����ά����arr���浽txt�ļ��У����Կո����
fid=fopen(path,'wt'); %�½��ļ�,��Ҫ���浽���ļ�·��,��·�������Ϊ'\������.txt'·��,��·�������Ϊ'\������.txt'
M = length(arr(:,1));
N = length(arr(1,:));
for i=1:M
    for j = 1:N
        fprintf(fid,'%g ',arr(i,j)'); %һ��һ�е�д�����ݣ��Կո�����������е����һ�����ݣ��س�
    end
    fprintf(fid,'\r\n');
end
fclose(fid);
end