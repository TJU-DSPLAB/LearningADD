function isFoldExist(path)
% 判断文件夹不存在，若不存在则新建
% path 需要判断的路径

% path = './result';
if ~exist(path)
    mkdir(path);
end

end