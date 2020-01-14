function save2txt_2d(arr, path)
% 将二维数组arr保存到txt文件中，并以空格隔开
fid=fopen(path,'wt'); %新建文件,你要保存到的文件路径,该路径的最后为'\变量名.txt'路径,该路径的最后为'\变量名.txt'
M = length(arr(:,1));
N = length(arr(1,:));
for i=1:M
    for j = 1:N
        fprintf(fid,'%g ',arr(i,j)'); %一行一行的写入数据，以空格隔开，到该行的最后一个数据，回车
    end
    fprintf(fid,'\r\n');
end
fclose(fid);
end