%% ������д��txt�ļ�
function save2txt_1d(arr, path)
% һά��������ݴ��뵽path·����Ӧ��txt�ļ�
fid=fopen(path,'wt'); %�½��ļ�,��Ҫ���浽���ļ�·��,��·�������Ϊ'\������.txt'·��,��·�������Ϊ'\������.txt'
N = length(arr);
for i=1:N
    fprintf(fid,'%g ',arr(i)'); %һ��һ�е�д�����ݣ��Կո�����������е����һ�����ݣ��س�
end
fclose(fid);

end