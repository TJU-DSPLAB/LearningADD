%% 将数据写入txt文件
function save2txt_1d(arr, path)
% 一维数组的数据存入到path路径对应的txt文件
fid=fopen(path,'wt'); %新建文件,你要保存到的文件路径,该路径的最后为'\变量名.txt'路径,该路径的最后为'\变量名.txt'
N = length(arr);
for i=1:N
    fprintf(fid,'%g ',arr(i)'); %一行一行的写入数据，以空格隔开，到该行的最后一个数据，回车
end
fclose(fid);

end