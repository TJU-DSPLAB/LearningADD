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
ԭevaluation.h
*/
#define EPS 1e-38
#define DATA_NUM 800		// ������������
#define bins 11				// bins = floor(1 + (log(DATA_NUM) / log(2)) + 0.5)���˴�DATA_NUM=800����bins��ֵΪ����11
#define FEATURE_NUM 200		// ������ʼ���ĸ���
#define FEATURE_SUB_NUM 10	// �����Ӽ��ĸ���

/*
ԭtext2array.h�еĺ��������ͳ�������
*/
float** text2array(char* path, int colnum);	// ����text2array����
float* text2array(char* path);


// ������������
float evaluation_scheme(int* scheme, float** traindata, float* label);


typedef struct
{
	int pos[FEATURE_SUB_NUM];
	float eva;
}frog;

typedef struct
{
	int length;	// �˴�length��ʾ�������鲻ͬԪ�صĸ�������Ȼ���������Ҳ����������ʾ����ĳ��ȣ����������new����������
	int arr[FEATURE_SUB_NUM];
}array;

frog max_in_group[GROUP_NUM];			//the worst
frog min_in_group[GROUP_NUM];			//the best
frog global_max;						//the best in global
frog allfrog[FROG_NUM];						//all the frog
frog grouped[GROUP_NUM][FROG_IN_GROUP];		//grouped group

// ����ʵ�����ݣ�������ǩ������������
char* path = "normalized_data_txt/traind.txt";
float** traindata = text2array(path, FEATURE_NUM);
float* label = text2array("normalized_data_txt/trainl.txt");

// ��������
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

	// srand�������ڲ��������
	srand(time(NULL));
	init();

	sort();

	for (i = 0; i<REPEAT_NUM; i++) {
		update();
		delete_group();
		sort();
	}
	// ������յı��뷽��
	FILE *fouttxt;
	char t[50];
	sprintf_s(t, "result/result_FS.txt");
	fopen_s(&fouttxt, t, "at+");
	for (int i = 0; i < FEATURE_SUB_NUM; i++) {
		fprintf(fouttxt, "%d ", global_max.pos[i]);
	}
	fprintf(fouttxt, "\n");
	fclose(fouttxt);

	// ������յı��뷽����Ӧ������ֵ
	FILE *fouttxteva;
	char ct[50];
	sprintf_s(ct, "result/FJ_%d_%d_eva.txt", FEATURE_NUM, FEATURE_SUB_NUM);
	fopen_s(&fouttxteva, ct, "at+");
	fprintf(fouttxteva, "%f ", global_max.eva);
	fprintf(fouttxteva, "\n");
	fclose(fouttxteva);

}

// ����n�����ظ������������ÿ�β�������������ǲ�ͬ��
int* randnum() {
	int* a = new int[FEATURE_NUM];
	//srand((unsigned)time(NULL));	//srand()��������һ���Ե�ǰʱ�俪ʼ���������.Ӧ�÷���for��ѭ�����ǰ�� ��ȻҪ�ܳ�ʱ��ȴ�
	for (int i = 0; i <= FEATURE_NUM - 1; ++i) a[i] = i;
	for (int i = FEATURE_NUM - 1; i >= 1; --i) swap(a[i], a[rand() % FEATURE_NUM]);
	return a;
}


//������Լ������������£�����ֲ��������ܵ�λ��
void init() {
	int i, j;
	int* data_temp;

	for (i = 0; i<FROG_NUM; i++) {
		data_temp = randnum();
		for (j = 0; j<FEATURE_SUB_NUM; j++) {
			// �˴���Ҫ��50������ȡ�����5������Ϊ��ʼ�ķ���
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

	// ���������������ܵ�eva
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
	for (j = 0; j<FROG_IN_GROUP; j++) {//���·��� 
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


array setdiff(int* array1, int* array2){	// ������1��������2�еĲ�ͬԪ�ط�����ǰ�棬��ͬ��Ԫ�ط��ں��棬����������飨��������1�е�����������򣬷���ֵ���в�ͬԪ�صĸ�����
	int i, j;
	int r = 0;
	int k = 0;
	int flag = 0;	// flagΪ0��ʾû����ͬ��Ԫ��
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
			A_diff.arr[i] = B_diff.arr[i];	//��Ϊ��ͬ�ı��
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
		new_pos = updated_pos(temp.pos, max_in_group[i].pos);	//���������ŷ�����
		for (int i = 0; i < FEATURE_SUB_NUM; i++) {	// ���·���
			temp.pos[i] = new_pos[i];
		}
		temp.eva = evaluation_scheme(temp.pos, traindata, label);
		if (temp.eva > min_in_group[i].eva)	{	// ��Ծ�ɹ�
			grouped[i][FROG_IN_GROUP - 1] = temp;
		}
		else {	//û���ҵ����Ž���߲�����Լ�����������¸��£���ȫ��������
			temp = min_in_group[i];
			new_pos = updated_pos(temp.pos, global_max.pos);	//��ȫ�����ŷ�����
			for (int i = 0; i < FEATURE_SUB_NUM; i++) {	// ���·���
				temp.pos[i] = new_pos[i];
			}
			temp.eva = evaluation_scheme(temp.pos, traindata, label);
			if (temp.eva > min_in_group[i].eva) {// ��Ծ�ɹ�
				grouped[i][FROG_IN_GROUP - 1] = temp;
			}
			else {	//������Լ����������û���Ż��ɹ������¸��£��������һ��λ��,�����
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

void delete_group()//���ҷ���
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
ԭevaluation.cpp
*/
// ��һ��һά��������ֵ
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


// ��һ��һά�������Сֵ
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


// ʹ��new��������ʼ����ά����
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


// ��ʼ����ά����
template<typename T>
void init_array(T&& arr, int row, int col){
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			arr[i][j] = 0;
		}
	}
}

// �˴���Ե�������������ͬ�������������ߵ�ƽ������Ϣ��
float ami(float* x, float* y){

	// int bins = floor(1 + (log(DATA_NUM) / log(2)) + 0.5);  // ������Ϊ�͵Ķ�����log2(count)=log(count)/log(2);
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

	// ��ʼ��binx,biny
	for (int i = 0; i < DATA_NUM; ++i) {
		*(binx + i) = floor(*(x + i) * bins);
		*(biny + i) = floor(*(y + i) * bins);
		if ((binx[i] > bins) || (binx[i] == bins)) {
			*(binx + i) = bins - 1;	// �ų�biny��ֵ������������ֵ
		}
		if ((biny[i] > bins) || (biny[i] == bins)) {
			*(biny + i) = bins - 1;	// �ų�biny��ֵ������������ֵ
		}
	}

	// �����ϸ���Pxy
	for (int i = 0; i < DATA_NUM; ++i) {
		Pxy[binx[i]][biny[i]] = (Pxy[binx[i]][biny[i]] + 1);
	}

	for (int i = 0; i < bins; ++i) {
		for (int j = 0; j < bins; ++j) {
			Pxy[i][j] = (Pxy[i][j] / DATA_NUM) + EPS;
		}
	}

	// ��Px��Py
	for (int i = 0; i < bins; ++i) {
		for (int j = 0; j < bins; ++j) {
			Px[i] = Px[i] + Pxy[i][j];	// �������
			Py[i] = Py[i] + Pxy[j][i];	// �������
		}
	}

	// ��x��y��ƽ������Ϣ��
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


// �����������ݣ���ǩ����Ӧ�ķ��������������������ֵ��
float evaluation_scheme(int* scheme, float** traindata, float* label){
	// �жϷ������Ƿ�����ظ������
	for (int i = 0; i < FEATURE_SUB_NUM; i++) {
		for (int j = 0; j < i; j++) {
			if (scheme[i] == scheme[j]){
				return -1;
			}
		}
	}

	// ���ݶ���
	float sum_MI = 0;
	float sum_mi = 0;
	// float ave_mi = 0;
	// float evalutation = 0;
	float data[FEATURE_SUB_NUM][DATA_NUM];

	// ���ݸ����ķ�������traindata��ѡ����Ӧ�����ݣ���ֵ��data���飬�˴���dataת��һ�£������5*800�ľ���
	// ����traindata���Ƿ��и�ֵ

	for (int i = 0; i < FEATURE_SUB_NUM; ++i) {
		for (int j = 0; j < DATA_NUM; ++j) {
			// int aa = scheme[i];
			data[i][j] = traindata[j][scheme[i]];
		}
	}

	// ���������ǩ�Լ���ͬ������Ļ���Ϣ��
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
ԭtxt2array.h�еĶ���ĺ���
��ȡTXT�ļ�������ȡ������ת��Ϊ��ά���顣����pathΪtxt�洢�����·����colnumΪ��ʼ�����������������һ����ά���飬�ж�Ӧ���������ж�Ӧ������
*/
float** text2array(char* path, int colnum){
	int rownum = 800, i = 0, j = 0;
	float **p = new float*[rownum];	//����ָ������
	for (i = 0; i< rownum; i++)
		p[i] = new float[colnum];

	float temp;

	FILE *fp;
	if (fopen_s(&fp, path, "r") == 0){

		// ����ȡ�����ݴ��뵽��ά������
		for (i = 0; i < rownum; i++) {
			for (j = 0; j < colnum; j++) {
				if (!feof(fp)) {
					fscanf_s(fp, "%f,", &temp);
					p[i][j] = temp; // ��ȡtxtÿ��Ԫ�أ������ά������
				}
			}
		}
	}
	else {
		printf("Can not open input file.\n");
		return 0;
	}

	fclose(fp);               // �ر��ļ�
	return p;
}

// ����text2array������ʹ��Ҳ���Խ�txt�ļ��е����ݴ洢��һά������
float* text2array(char* path){
	int rownum = 800, i = 0;
	float *p = new float[rownum];	//����ָ������
	for (i = 0; i< rownum; i++)
		p[i] = 0;

	float temp;

	FILE *fp;
	if (fopen_s(&fp, path, "r") == 0){

		// ����ȡ�����ݴ��뵽һά������
		for (i = 0; i < rownum; i++) {
			if (!feof(fp)) {
				fscanf_s(fp, "%f,", &temp);
				p[i] = temp; // ��ȡtxtÿ��Ԫ�أ�����һά������
			}
		}
	}
	else {
		printf("Can not open input file.\n");
		return 0;
	}

	fclose(fp);               // �ر��ļ�
	return p;
}


