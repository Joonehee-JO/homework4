#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);              //동적할당을 통해 row x col 배열을 생성하는 함수 프로토타입
void print_matrix(int** matrix, int row, int col);  //행렬을 출력하는 함수 프로토타입
int free_matrix(int** matrix, int row, int col);    //할당받은 메모리를 해제하는 함수 프로토타입
int fill_data(int** matrix, int row, int col);      //생성한 행렬에 0~19의 수로 채워넣는 함수 프로토타입
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //행렬의 덧셈을 하는 함수 프로토타입
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //행렬의 뺄셈을 하는 함수 프로토타입
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //주어진 행렬의 전치행렬을 계산해주는 함수 프로토타입
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //행렬의 곱셈을 수행하는 함수 프로토타입

int main()
{

    char command;
    printf("[----- [Cho Joon Hee]  [2017038076] -----]\n");

    int row, col;
    srand(time(NULL));              //랜덤 난수를 생성토록함

    printf("Input row and col : "); //행과 열을 입력받음
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);   //A행렬 생성
    int** matrix_b = create_matrix(row, col);   //B행렬 생성
    int** matrix_a_t = create_matrix(col, row); //A_T 전치행렬 생성
    
    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //메모리를 할당받지 않았을 경우 비정상 종료

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");   //사용자로부터 커맨드 입력받음
        scanf(" %c", &command);

        switch(command) {       //입력한 문자에 따른 기능제공
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);  //A행렬에 0~19사이의 수로 채워넣음
            fill_data(matrix_b, row, col);  //B행렬에 0~19사이의 수로 채워넣음
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);   //A행렬을 출력하는 함수호출
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);   //B행렬을 출력하는 함수호출
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);  //A행렬과 B행렬을 더하는 함수호출
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);   //A행렬에서 B행렬을 빼는 함수호출
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   //A행렬의 전치행렬을 만드는 함수호출
            print_matrix(matrix_a_t, col, row);     //생성한 전치행렬을 출력하는 함수호출
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);   //A행렬의 전치행렬을 만드는 함수호출
            multiply_matrix(matrix_a, matrix_a_t, row, col);    //A행렬과 A행렬의 전치행렬의 곱셈을 계산하는 함수호출
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);          //할당받은 메모리를 해제하기위한 함수호출
            free_matrix(matrix_a, row, col);            //할당받은 메모리를 해제하기위한 함수호출
            free_matrix(matrix_b, row, col);            //할당받은 메모리를 해제하기위한 함수호출
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //정의된 문자를 입력하지않았을 때
            break;
        }

    }while(command != 'q' && command != 'Q');   //반복문 종료조건

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{   
    //전처리검사 
    if(row <= 0 || col <=0) {   //행과 열의 입력이 올바르지 않을 때 NULL리턴
        printf("Check the sizes of row and col!\n");

        return NULL;            
    }

    int** matrix_address = (int**)malloc(sizeof(int *)*row);     //주소를 담을 공간 * row만큼의 메모리를 할당받음

    for(int i=0; i<row; i++)
        matrix_address[i] = (int *)malloc(sizeof(int **)*col);  //값을 저장할 공간(int4바이트)*col만큼의 메모리를 할당받음

    //후처리검사
    if (matrix_address == NULL) {   //메모리를 할당받지 못했을 때 NULL리턴
		printf("Memory Allocation Failed.\n");

		return NULL;
	}

    return matrix_address;  //할당받은 메모리 주소를 반환시켜줌
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) { //행과 열의 입력이 올바르지 않을 때
		printf("Check the size of row and col!\n");
		return;
	}

    if (matrix == NULL) {   //메모리를 할당받지 못했을 때 함수종료
		printf("Matrix is not created\n");

		return;
	}

    for(int i=0; i<row; i++){       //row * col만큼 반복하면서 행렬 데이터값 출력
        for(int j=0; j<col; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) { //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");
		return -1;
	}

    if(matrix == NULL){         //메모리를 할당받지 못했을 때 비정상종료											
		printf("Matrix is not created\n");

        return -1;
	}

    for(int i=0; i<row; i++){   //동적으로 할당받았던 열메모리 해제
        free(matrix[i]);
    }
    free(matrix);               //행렬의 전체 할당받은 메모리를 해제

    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {     //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");

		return -1;
	}

    if(matrix == NULL){			    //메모리를 할당받지 못했을 때 비정상종료								
		printf("Matrix is not created\n");

		return -1;															
	}

    for(int i=0; i<row; i++){       //row*col 만큼 돌면서 행렬에 0~19사이의 수로 채워넣음
        for(int j=0; j<col; j++)
            matrix[i][j] = rand() % 20;
    }

    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{   
    if (row <= 0 || col <= 0) {     //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");

		return -1;
	}

    int **sum_matrix = create_matrix(row, col);     //행렬의 덧셈을 수행하기 위한 메모리를 할당받음

    if(matrix_a == NULL || matrix_b == NULL || sum_matrix == NULL){				//제대로 메모리를 할당받지 못했을 경우
		printf("Matrix is not created\n");										
		return -1;																// 비정상종료
	}

    for(int i=0; i<row; i++){       //row*col 만큼 돌면서 행렬의 덧셈을 수행
        for(int j=0; j<col; j++){
            sum_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];     //A행렬과 B행렬을 더하여 sum행렬에 저장
        }
    }  
    print_matrix(sum_matrix, row, col);     //덧셈연산을 수행한 sum행렬 출력
    free_matrix(sum_matrix, row, col);      //함수 종료 전 사용한 메모리 해제

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (row <= 0 || col <= 0) {         //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");
		return -1;
	}

    int **sub_matrix = create_matrix(row, col);   //행렬의 뺄셈연산을 수행할 sum_matrix생성

    if(matrix_a == NULL || matrix_b == NULL || sub_matrix == NULL){				//제대로 메모리를 할당받지 못했을 경우
		printf("Matrix is not created\n");										
		return -1;																//비정상 종료
	}

    for(int i=0; i<row; i++){       //row*col만큼 돌면서 뺄셈연산을 수행
        for(int j=0; j<col; j++){
            sub_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j]; //sub행렬 = A행렬 - B행렬
        }
    }
    print_matrix(sub_matrix, row, col); //결과확인을 위한 sub행렬 출력
    free_matrix(sub_matrix,row, col);   //함수 종료 전 사용한 메모리 반납    

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0) {         //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");
		return -1;
    }

    if(matrix == NULL || matrix_t == NULL){				//제대로 메모리를 할당받지 못했을 경우
		printf("Matrix is not created\n");										
		return -1;										//비정상 종료
	}

    for(int i=0; i<row; i++){       //row*col 만큼 돌면서 대상행렬의 전치행렬 생성
        for(int j=0; j<col; j++){
            matrix_t[i][j] = matrix[j][i];  //j행 i열의 값을 i행 j열에 저장
        }
    }
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{   
    int mul_result;     //행렬의 곱셈연산을 수행하여 값을 저장할 변수 

    if (row <= 0 || col <= 0) {         //행과 열의 입력이 올바르지 않을 때 비정상종료
		printf("Check the size of row and col!\n");
		return -1;
    }

    int **matrix_axt = create_matrix(row,row);  //행렬의 곱셈연산을 수행할 martix_axt생성
    
    if(matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL){ //메모리를 제대로 할당받지 못했다면
        printf("Matrix is not created\n");										
		return -1;										//비정상 종료
    }

    for(int i=0; i<row; i++){   //행렬의 곱셈을 수행하는 연산, row * col X col * row를 수행
        for(int j=0; j<row; j++){   
            mul_result = 0;     //곱셈을 수행한 데이터를 저장할 변수 0으로 초기화
            for(int k=0; k<col; k++){   //col만큼 돌면서 행렬곱셈을 수행하여 나오는 값을 더해감
                mul_result += matrix_a[i][k] * matrix_t[k][j];  
            }
            matrix_axt[i][j] = mul_result;  //수행결과를 저장
        }
    }

    print_matrix(matrix_axt, row, row); //행렬의 곱셈을 수행한 결과를 출력, A행렬과 그 전치행렬A_T의 곱셈
	free_matrix(matrix_axt, row, col);  //함수 종료 전 사용한 메모리 반납

	return 1;
}