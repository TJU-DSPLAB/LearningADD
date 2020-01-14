#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <memory.h>
#include <sys/timeb.h>  
#include <string.h>

#include <iostream>
using namespace std;


#define REPEAT_NUM 1000
#define FROG_NUM 20
#define GROUP_NUM 4
#define FROG_IN_GROUP (FROG_NUM/GROUP_NUM)

/*
原evaluation.h
*/
#define EPS 1e-38
#define DATA_NUM 800		// 数据样本数量
#define bins 11				// bins = floor(1 + (log(DATA_NUM) / log(2)) + 0.5)，此处DATA_NUM=800，故bins的值为常量11
#define FEATURE_NUM 200		// 特征初始集的个数
#define FEATURE_SUB_NUM 10	// 特征子集的个数

/*
原text2array.h中的函数声明和常量定义
*/
float** text2array(char* path, int colnum);	// 申明text2array函数
float* text2array(char* path);


// 声明评估函数
float evaluation_scheme(int* scheme, float** traindata, float* label);


typedef struct
{
	int pos[FEATURE_SUB_NUM];
	float eva;
}frog;

typedef struct
{
	int length;	// 此处length表示两个数组不同元素的个数，当然，这个变量也可以用来表示数组的长度，尤其是针对new创建的数组
	int arr[FEATURE_SUB_NUM];
}array;

frog max_in_group[GROUP_NUM];			//the worst
frog min_in_group[GROUP_NUM];			//the best
frog global_max;						//the best in global
frog allfrog[FROG_NUM];						//all the frog
frog grouped[GROUP_NUM][FROG_IN_GROUP];		//grouped group

// 加载实验数据，包括标签和特征集数据
char* path = "normalized_data_txt/traind.txt";
float** traindata = text2array(path, FEATURE_NUM);
float* label = text2array("normalized_data_txt/trainl.txt");

// 声明函数
void run(int repeatnum);
void init();
array setdiff(int* array1, int* array2);
int* updated_pos(int* array1, int* array2);
void sort_group(int group_index);
void update();
void delete_group();
void sort();

int main() {
	run(1);
	return 0;
}

void run(int repeatnum) {

	int i;

	// srand函数用于产生随机数
	srand(time(NULL));
	init();

	sort();

	for (i = 0; i<REPEAT_NUM; i++) {
		update();
		delete_group();
		sort();
	}
	// 存放最终的编码方案
	FILE *fouttxt;
	char t[50];
	sprintf_s(t, "result/result_FS.txt");
	fopen_s(&fouttxt, t, "at+");
	for (int i = 0; i < FEATURE_SUB_NUM; i++) {
		fprintf(fouttxt, "%d ", global_max.pos[i]);
	}
	fprintf(fouttxt, "\n");
	fclose(fouttxt);

	// 存放最终的编码方案对应的评估值
	FILE *fouttxteva;
	char ct[50];
	sprintf_s(ct, "result/FJ_%d_%d_eva.txt", FEATURE_NUM, FEATURE_SUB_NUM);
	fopen_s(&fouttxteva, ct, "at+");
	fprintf(fouttxteva, "%f ", global_max.eva);
	fprintf(fouttxteva, "\n");
	fclose(fouttxteva);

}

// 产生n个不重复的随机数，且每次产生的随机序列是不同的
int* randnum() {
	int* a = new int[FEATURE_NUM];
	//srand((unsigned)time(NULL));	//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待
	for (int i = 0; i <= FEATURE_NUM - 1; ++i) a[i] = i;
	for (int i = FEATURE_NUM - 1; i >= 1; --i) swap(a[i], a[rand() % FEATURE_NUM]);
	return a;
}


//在满足约束条件的情况下，随机分布各个青蛙的位置
void init() {
	int i, j;
	int* data_temp;

	for (i = 0; i<FROG_NUM; i++) {
		data_temp = randnum();
		for (j = 0; j<FEATURE_SUB_NUM; j++) {
			// 此处需要对50个序列取随机的5个，作为初始的方案
			// printf("%d\t", data_temp[j]);
			allfrog[i].pos[j] = data_temp[j];
			// printf("%d ", data_temp[j]);
		}
		delete[] data_temp;
		// printf("\n\n");
		allfrog[i].eva = evaluation_scheme(allfrog[i].pos, traindata, label);
		if (allfrog[i].eva < 0){
			i--;
		}
	}
	data_temp = NULL;
}

void sort() {
	int i, j, k;
	frog temp;

	// 降序排列所有青蛙的eva
	for (i = 0; i<FROG_NUM - 1; i++) {
		for (j = i; j<FROG_NUM; j++) {
			if (allfrog[i].eva < allfrog[j].eva) {
				temp = allfrog[i];
				allfrog[i] = allfrog[j];
				allfrog[j] = temp;
			}
		}
	}

	k = 0;
	for (j = 0; j<FROG_IN_GROUP; j++) {//重新分组 
		for (i = 0; i<GROUP_NUM; i++) {
			grouped[i][j] = allfrog[k];
			k++;
		}
	}

	global_max = allfrog[0];
	for (i = 0; i<GROUP_NUM; i++) {
		max_in_group[i] = grouped[i][0];
		min_in_group[i] = grouped[i][FROG_IN_GROUP - 1];
	}
}


array setdiff(int* array1, int* array2){	// 求数组1中与数组2中的不同元素放在最前面，相同的元素放在后面，返回组合数组（即对数组1中的序号重新排序，返回值还有不同元素的个数）
	int i, j;
	int r = 0;
	int k = 0;
	int flag = 0;	// flag为0表示没有相同的元素
	int same_array[FEATURE_SUB_NUM];
	for (i = 0; i < FEATURE_SUB_NUM; i++)
		same_array[i] = 0;

	array temp_array;
	for (i = 0; i < FEATURE_SUB_NUM; ++i) {
		for (j = 0; j < FEATURE_SUB_NUM; ++j) {
			if (array1[i] == array2[j]) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			*(temp_array.arr + r) = array1[i];
			r++;
		}
		else {
			*(same_array + k) = array1[i];
			k++;
			flag = 0;
		}
	}
	for (int i = r; i < FEATURE_SUB_NUM; i++) {
		temp_array.arr[i] = same_array[i - r];
	}
	temp_array.length = r;
	return temp_array;
}

int* updated_pos(int* array1, int* array2){
	int rand_data;
	array A_diff = setdiff(array1, array2);
	array B_diff = setdiff(array2, array1);
	for (int i = 0; i < A_diff.length; i++) {
		rand_data = rand() % 100;
		if (rand_data <= 49) {
			A_diff.arr[i] = B_diff.arr[i];	//改为不同的编号
		}
	}

	return  A_diff.arr;
}

void update() {
	int i, j;
	frog temp;
	int* new_pos;
	memset(&temp, 0, sizeof(frog));
	for (i = 0; i<GROUP_NUM; i++) {
		temp = min_in_group[i];
		new_pos = updated_pos(temp.pos, max_in_group[i].pos);	//往组内最优方向跳
		for (int i = 0; i < FEATURE_SUB_NUM; i++) {	// 更新方案
			temp.pos[i] = new_pos[i];
		}
		temp.eva = evaluation_scheme(temp.pos, traindata, label);
		if (temp.eva > min_in_group[i].eva)	{	// 跳跃成功
			grouped[i][FROG_IN_GROUP - 1] = temp;
		}
		else {	//没有找到更优解或者不满足约束条件，重新更新，向全局最优跳
			temp = min_in_group[i];
			new_pos = updated_pos(temp.pos, global_max.pos);	//往全局最优方向跳
			for (int i = 0; i < FEATURE_SUB_NUM; i++) {	// 更新方案
				temp.pos[i] = new_pos[i];
			}
			temp.eva = evaluation_scheme(temp.pos, traindata, label);
			if (temp.eva > min_in_group[i].eva) {// 跳跃成功
				grouped[i][FROG_IN_GROUP - 1] = temp;
			}
			else {	//不满足约束条件或者没有优化成功，重新更新，随机分配一个位置,随便跳
				int* rand_data = randnum();
				for (j = 0; j<FEATURE_SUB_NUM; j++) {
					temp.pos[j] = rand_data[j];
				}
				delete[] rand_data;
				rand_data = NULL;
				temp.eva = evaluation_scheme(temp.pos, traindata, label);
				grouped[i][FROG_IN_GROUP - 1] = temp;
			}
		}

	}
}

void delete_group()//打乱分组
{
	int i, j;
	int k = 0;
	for (i = 0; i<FROG_IN_GROUP; i++) {
		for (j = 0; j<GROUP_NUM; j++) {
			allfrog[k] = grouped[j][i];
			k++;
		}
	}
}


/*
原evaluation.cpp
*/
// 求一个一维数组的最大值
template<typename T>
T getMax(T* arr, int counter){
	T max = arr[0];
	for (int i = 1; i<counter; i++){
		if (max < arr[i]){
			max = arr[i];
		}
	}
	return max;
}


// 求一个一维数组的最小值
template<typename T>
T getMin(T* arr, int counter){
	T min = arr[0];
	for (int i = 1; i<counter; i++) {
		if (min>arr[i]){
			min = arr[i];
		}
	}
	return min;
}


// 使用new构建并初始化二维数组
float**  init_array(int row, int col){
	float** p = new float*[row];
	if (p != NULL) {
		for (int i = 0; i < row; ++i) {
			p[i] = new float[col];
			if (p[i] != NULL) {
				for (int j = 0; j < col; ++j) {
					p[i][j] = 0;
				}
			}
			else
			{
				return NULL;
			}
		}
		return p;
	}
	else {
		return NULL;
	}

}


// 初始化二维数组
template<typename T>
void init_array(T&& arr, int row, int col){
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			arr[i][j] = 0;
		}
	}
}

// 此处针对的是两个长度相同的向量，求两者的平均互信息量
float ami(float* x, float* y){

	// int bins = floor(1 + (log(DATA_NUM) / log(2)) + 0.5);  // 计算以为低的对数：log2(count)=log(count)/log(2);
	int binx[DATA_NUM];
	int biny[DATA_NUM];

	//float** Pxy = init_array(bins, bins);
	float Pxy[bins][bins];
	float Px[bins];
	float Py[bins];
	/*float** Pxy = new float*[bins];*/
	for (int i = 0; i < bins; ++i){
		Px[i] = 0;
		Py[i] = 0;
		for (int j = 0; j<bins; j++){
			Pxy[i][j] = 0;
		}
	}

	float sum = 0;

	// 初始化binx,biny
	for (int i = 0; i < DATA_NUM; ++i) {
		*(binx + i) = floor(*(x + i) * bins);
		*(biny + i) = floor(*(y + i) * bins);
		if ((binx[i] > bins) || (binx[i] == bins)) {
			*(binx + i) = bins - 1;	// 排除biny的值超出最大的数组值
		}
		if ((biny[i] > bins) || (biny[i] == bins)) {
			*(biny + i) = bins - 1;	// 排除biny的值超出最大的数组值
		}
	}

	// 求联合概率Pxy
	for (int i = 0; i < DATA_NUM; ++i) {
		Pxy[binx[i]][biny[i]] = (Pxy[binx[i]][biny[i]] + 1);
	}

	for (int i = 0; i < bins; ++i) {
		for (int j = 0; j < bins; ++j) {
			Pxy[i][j] = (Pxy[i][j] / DATA_NUM) + EPS;
		}
	}

	// 求Px，Py
	for (int i = 0; i < bins; ++i) {
		for (int j = 0; j < bins; ++j) {
			Px[i] = Px[i] + Pxy[i][j];	// 对行求和
			Py[i] = Py[i] + Pxy[j][i];	// 对列求和
		}
	}

	// 求x与y的平均互信息量
	for (int i = 0; i < bins; ++i) {
		for (int j = 0; j < bins; ++j) {
			sum = sum + (Pxy[i][j] * (log(Pxy[i][j] / (Px[i] * Py[j] + EPS)) / log(2)));
		}
	}

	//delete[] Px;
	//Px = NULL;
	//delete[] Py;
	//Py = NULL;
	//delete[] Pxy;
	//Pxy = NULL;
	return sum / (log(bins) / log(2));
}


// 根据输入数据，标签及对应的方案，求这个方案的评估值。
float evaluation_scheme(int* scheme, float** traindata, float* label){
	// 判断方案中是否存在重复的序号
	for (int i = 0; i < FEATURE_SUB_NUM; i++) {
		for (int j = 0; j < i; j++) {
			if (scheme[i] == scheme[j]){
				return -1;
			}
		}
	}

	// 数据定义
	float sum_MI = 0;
	float sum_mi = 0;
	// float ave_mi = 0;
	// float evalutation = 0;
	float data[FEATURE_SUB_NUM][DATA_NUM];

	// 根据给定的方案，从traindata中选出对应的数据，赋值给data数组，此处将data转置一下，变成如5*800的矩阵
	// 测试traindata中是否有负值

	for (int i = 0; i < FEATURE_SUB_NUM; ++i) {
		for (int j = 0; j < DATA_NUM; ++j) {
			// int aa = scheme[i];
			data[i][j] = traindata[j][scheme[i]];
		}
	}

	// 求特征与标签以及不同特征间的互信息量
	for (int i = 0; i < FEATURE_SUB_NUM; ++i) {
		sum_MI = sum_MI + ami(data[i], label);
		for (int j = 0; j < FEATURE_SUB_NUM; ++j) {
			if ((i != j)){
				sum_mi = sum_mi + ami(data[j], data[i]);
			}
			else break;
		}
	}
	int sum = (FEATURE_SUB_NUM *(FEATURE_SUB_NUM - 1)) / 2;
	// ave_mi = sum_mi / ((FEATURE_SUB_NUM *(FEATURE_SUB_NUM - 1)) / 2);
	return sum_MI - (sum_mi / sum);
}


/*
原txt2array.h中的定义的函数
读取TXT文件，将读取的数据转换为二维数组。输入path为txt存储的相对路径，colnum为初始特征集个数，输出是一个二维数组，行对应的样本，列对应的特征
*/
float** text2array(char* path, int colnum){
	int rownum = 800, i = 0, j = 0;
	float **p = new float*[rownum];	//定义指针数组
	for (i = 0; i< rownum; i++)
		p[i] = new float[colnum];

	float temp;

	FILE *fp;
	if (fopen_s(&fp, path, "r") == 0){

		// 将读取的数据存入到二维数组中
		for (i = 0; i < rownum; i++) {
			for (j = 0; j < colnum; j++) {
				if (!feof(fp)) {
					fscanf_s(fp, "%f,", &temp);
					p[i][j] = temp; // 读取txt每个元素，存入二维数组中
				}
			}
		}
	}
	else {
		printf("Can not open input file.\n");
		return 0;
	}

	fclose(fp);               // 关闭文件
	return p;
}

// 重载text2array函数，使其也可以将txt文件中的数据存储在一维数组中
float* text2array(char* path){
	int rownum = 800, i = 0;
	float *p = new float[rownum];	//定义指针数组
	for (i = 0; i< rownum; i++)
		p[i] = 0;

	float temp;

	FILE *fp;
	if (fopen_s(&fp, path, "r") == 0){

		// 将读取的数据存入到一维数组中
		for (i = 0; i < rownum; i++) {
			if (!feof(fp)) {
				fscanf_s(fp, "%f,", &temp);
				p[i] = temp; // 读取txt每个元素，存入一维数组中
			}
		}
	}
	else {
		printf("Can not open input file.\n");
		return 0;
	}

	fclose(fp);               // 关闭文件
	return p;
}


