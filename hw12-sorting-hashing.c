/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);    //배열에 랜덤한 key값 저장
int freeArray(int *a);      //할당된 메모리 해제
void printArray(int *a);    //배열 출력

int selectionSort(int *a);  //선택 정렬
int insertionSort(int *a);  //삽입 정렬
int bubbleSort(int *a);     //버블 정렬
int shellSort(int *a);      //셸 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n);   //퀵 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);      //해시 함수(제산 함수)

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);  //해시 테이블 생성

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));  //시드 값을 현재시각으로 조정

	do{
		printf("----------------------------------------------------------------\n");       //메뉴 출력
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");  
		scanf(" %c", &command);     //메뉴 입력

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);     //배열에 랜덤한 key값 저장
			break;
		case 'q': case 'Q':
			freeArray(array);       //할당된 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array);   //선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array);   //삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array);      //버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array);       //셸 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);   //퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);     //해싱
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);      //검색
			printArray(hashtable);
			index = search(hashtable, key);     //해싱 테이블에서 인덱스 값을 찾아옴
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);      //배열 출력
			break;
		default:        //이외의 값 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //q 입력시 반복문 종료

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);    //배열a에 할당된 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {    //배열 a가 NULL이면
		printf("nothing to print.\n");	//에러문구 출력
		return;	//함수 종료
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);	//배열 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);	//배열의 key값 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])	//최소값 찾기
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];	//a[i]의 값과 최솟값 교환
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)	//배열의 처음이나 a[i]의 값보다 작은 값을 만나면 반복문 종료
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;	//a[j]에 a[i]의 값 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE-1; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	//큰 값을 다음 인덱스로 이동하며 배열의 끝까지 이동
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //전체 길이의 1/2로 줄여가며 h를 간격으로 설정
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//삽입 정렬 사용
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	//피봇을 n-1로 설정
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);	//피봇보다 큰값이 있으면 반복문 종료
			while(a[--j] > v);	//피봇보다 작은값이 있으면 반복문 종료

			if (i >= j) break;	//i와 j가 같거나 i가 인덱스 j를 넘어가면 반복문 종료
			//자리 교환
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		//i와 n-1의 값 교환
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);	//i와 i의 앞쪽 배열을 정렬하기위해 재귀 호출
		quickSort(a+i+1, n-i-1);	//i의 뒤쪽 배열을 정렬하기위해 재귀 호출
	}


	return 0;
}

int hashCode(int key) {     //해시 함수 (제산 함수)
   return key % MAX_HASH_TABLE_SIZE;    //배열의 크기(홀수)로 나눈 나머지를 홈 버킷으로 사용
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;	//헤시 테이블 초기화

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);	//홈 버킷을 받아옴
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)	//버킷에 초기값이 저장되어있다면(충돌 X)
		{
			hashtable[hashcode] = key;	//버킷의 위치에 key값 저장
		} else 	{	//버킷에 초기값이 아니라면(충돌 O)

			index = hashcode;

			while(hashtable[index] != -1)	//값이 -1인 버킷이 나올때까지 인덱스를 바꿈
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;	//값이 -1인 버킷에 key값 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);	//key의 홈버킷을 받고

	if(ht[index] == key)	//해시 테이블의 index값과 key값이 같다면 index 리턴
		return index;

	while(ht[++index] != key)	//같지않다면 key값과 같아질때까지 index 값을 변경
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;	//index 리턴
}