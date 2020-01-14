#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import random as rd
import math as mt
import copy


EPS = 2.2204e-16
# DATA_NUM = 800


def load_2d_txt1(filename, row=None, col=None):
    # filename = 'test_data.txt'  # txt文件和当前脚本在同一目录下，所以不用写具体路径
    f = open(filename, 'r')
    result = list()
    for line in open(filename):
        for i in line.split():
            result.append(i)

    f.close()

    if row and col:
        data = np.zeros((row, col), float)
        k = 0
        for i in range(row):
            for j in range(col):
                data[i][j] = result[k]
                k = k + 1
        return data
    else:
        data = np.zeros(len(result), float)
        for ind, val in enumerate(result):
            data[ind] = val

    return data


def load_2d_txt(filename, row=None, col=None):
    # filename = 'test_data.txt'  # txt文件和当前脚本在同一目录下，所以不用写具体路径
    f = open(filename, 'r')
    result = list()
    for line in open(filename):
        for i in line.split():
            result.append(i)

    f.close()

    res = result[0].split(',')

    if row and col:
        data = np.zeros((row, col), float)
        k = 0
        for i in range(row):
            for j in range(col):
                data[i][j] = float(res[k])
                k = k + 1
        return data
    else:
        data = np.zeros(len(res)-1, float)
        # 打印出来发现len(res)的长度为1201，最后一个字符为空，所以需要去掉最后一个
        res = res[0:1200]
        for ind, val in enumerate(res):
            # print(ind, val)
            data[ind] = float(val)

    return data


def ami(x, y):
    """
    Calculates the mutual average information of x ang y with a possible lag.
    :param x: the time series.
    :param y: the time series.
    :return: the normalized average mutual information, it means how many bit x and y has in common relative to
             how many bits is needed for the internally binned representation of x or y.
    """
    # 验证输入参数的有效性
    # print("输出x，y的长度：", len(x), len(y))
    try:
        (len(x) == len(y))
    except Exception as e:
        print("输入的两个变量的长度不一致！")

    summ = 0
    data_num = len(x)
    for i, val in enumerate(y):
        y[i] = val * (1 - EPS)

    # 初始化binx，biny
    bins = mt.floor(1 + mt.log(data_num, 2) + 0.5)

    binx = [mt.floor(x[0] * bins)]
    biny = [mt.floor(y[0] * bins)]

    for i in range(data_num):
        if i > 0:
            binx.append(mt.floor(x[i] * bins))
            biny.append(mt.floor(y[i] * bins))

        if (binx[i] > bins) or (binx[i] == bins):
            binx[i] = bins - 1

        if (biny[i] > bins) or (biny[i] == bins):
            biny[i] = bins - 1

    # 求联合概率pxy
    pxy = np.zeros((bins, bins), float)
    px = np.zeros(bins, float)
    py = np.zeros(bins, float)

    for i in range(data_num):
        pxy[binx[i]][biny[i]] = (pxy[binx[i]][biny[i]] + 1)
        # print(pxy[binx[i]][biny[i]])

    for i in range(len(pxy[0])):
        for j in range(len(pxy[0])):
            pxy[i][j] = (pxy[i][j] / data_num) + EPS

    # 求px，py
    for i in range(len(pxy[0])):
        for j in range(len(pxy[0])):
            px[i] = px[i] + pxy[i][j]   # 对行求和
            py[i] = py[i] + pxy[j][i]   # 对列求和

    # 求x与y的平均互信息量
    for i in range(len(pxy[0])):
        for j in range(len(pxy[0])):
            summ = summ + (pxy[i][j] * (mt.log((pxy[i][j] / (px[i] * py[j] + EPS)), 2)))

    return summ / mt.log(bins, 2)


def evaluation(data, label, B):
    """
    calculate evaluation value of feature subset.
    :param data: numpy array, sample data, the rows represent the samples and the columns represent features.
    :param label:numpy array, the class label of samples.
    :param B: the scheme of feature subset.
    :return: eva, the evaluation value of feature subset.
    """
    data = np.array(data)
    label = np.array(label)
    #
    x = data[:, B]
    [m, n] = x.shape     # 此处m为样本个数，n对应特征的个数
    fmi_num = sum(range(1, n))

    sum_lmi = 0
    sum_fmi = 0

    # 求互信息量
    for i in range(n):
        sum_lmi = sum_lmi + ami(x[:, i], label)
        for j in range(n):
            if i > j:
                sum_fmi = sum_fmi + ami(x[:, i], x[:, j])
            else:
                break

    ave_mi = sum_fmi / fmi_num
    # eva = sum_lmi - ave_mi
    # print(eva)
    return sum_lmi - ave_mi


def maxminnorm(array):
    maxcols = array.max(axis=0)
    mincols = array.min(axis=0)
    data_shape = array.shape
    data_rows = data_shape[0]
    data_cols = data_shape[1]
    t = np.empty((data_rows, data_cols))
    for i in range(0, data_cols):
        t[:, i] = (array[:, i]-mincols[i])/(maxcols[i]-mincols[i])
    return t


# 群智能特征选择算法参数设置
FROG_NUM = 20
GROUP_NUM = 4
FROG_IN_GROUP = (FROG_NUM//GROUP_NUM)
REPEAT_NUM = 2000
FEATURE_NUM = 200		# 特征初始集的个数
FEATURE_SUB_NUM = 10    # 特征子集的个数
data = load_2d_txt('./normalized_data_txt_824/traind.txt', row=1200, col=FEATURE_NUM)
label = load_2d_txt('./normalized_data_txt_824/trainl.txt')
# data = maxminnorm(data)
# print(len(data))


class Frog(object):
    def __init__(self):
        self.pos = rd.sample(range(FEATURE_NUM), FEATURE_SUB_NUM)  # 随机从初始特征集中随机选取一个特征子集
        self.eva = evaluation(data, label, self.pos)

    # @property
    def set(self, arr):
        self.pos = arr
        self.eva = evaluation(data, label, arr)


def init_frogs(length):
    arr = []
    for i in range(length):
        arr.append(Frog())

    return arr


# init frog group
allfrog = init_frogs(FROG_NUM)
global_max = allfrog[0]                                 # the best in global
grouped = np.zeros((GROUP_NUM, FROG_IN_GROUP), Frog)    # grouped group
max_in_group = np.zeros(GROUP_NUM, Frog)                # the worst
min_in_group = np.zeros(GROUP_NUM, Frog)                # the best


def sort():
    global allfrog
    global global_max
    global grouped
    global max_in_group
    global min_in_group

    # 降序排列所有青蛙的eva
    for i in range(FROG_NUM):
        for j in range(i, FROG_NUM):
            if allfrog[i].eva < allfrog[j].eva:
                temp = allfrog[i]
                allfrog[i] = allfrog[j]
                allfrog[j] = temp

    k = 0
    # 进行分组
    for j in range(FROG_IN_GROUP):
        for i in range(GROUP_NUM):
            grouped[i][j] = allfrog[k]
            k = k + 1

    global_max = allfrog[0]
    print(global_max.eva, global_max.pos)

    for i in range(GROUP_NUM):
        max_in_group[i] = grouped[i][0]
        min_in_group[i] = grouped[i][FROG_IN_GROUP - 1]


def update():
    global grouped

    for i in range(GROUP_NUM):
        temp = copy.deepcopy(min_in_group[i])
        new_pos = updated_pos(temp.pos, max_in_group[i].pos)    # 往组内最优方向跳
        temp.set(new_pos)
        if temp.eva > min_in_group[i].eva:  # 跳跃成功
            grouped[i][FROG_IN_GROUP - 1] = copy.deepcopy(temp)
        else:
            temp = copy.deepcopy(min_in_group[i])
            new_pos = updated_pos(temp.pos, global_max.pos)  # 往全局最优方向跳
            temp.set(new_pos)
            if temp.eva > min_in_group[i].eva:  # 跳跃成功
                grouped[i][FROG_IN_GROUP - 1] = copy.deepcopy(temp)
            else:
                grouped[i][FROG_IN_GROUP - 1].set(rd.sample(range(FEATURE_NUM), FEATURE_SUB_NUM))


def updated_pos(pos, dir_pos):
    same = list(set(pos).intersection(set(dir_pos)))
    diff1 = list(set(pos).difference(set(dir_pos)))
    diff2 = list(set(dir_pos).difference(set(pos)))

    for index, val in enumerate(diff2):
        if rd.random() > 0.5:
            diff1[index] = val

    new_pos = list(set(same).union(diff1))

    return new_pos


def shuffle():
    k = 0
    for i in range(0, FROG_IN_GROUP):
        for j in range(0, GROUP_NUM):
            allfrog[k] = grouped[j][i]
            k = k + 1


def select():
    sort()
    for ite in range(REPEAT_NUM):
        update()
        shuffle()
        sort()

    return global_max.pos, global_max.eva


# 写入txt文件中
def write_txt(filename, data):
    file_handle = open(filename, mode='a')

    print(data, '\n', file=file_handle)
    file_handle.close()


def delete_contentOfTxt(filename):
    with open(filename, 'r') as fpr:
        content = fpr.read()
    content = content.replace('[', '')
    content = content.replace(']', '')
    with open(filename, 'w') as fpw:
        fpw.write(content)

pos, eva = select()
pos_path = 'result/result_FS.txt'
eva_path = 'result/result_FS_eva.txt'
write_txt(filename=pos_path, data=pos)
delete_contentOfTxt(filename=pos_path)
# write_txt(filename=eva_path, data=eva)
# print(pos, eva)
