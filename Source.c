#include<stdio.h>
#include<string.h>

void main(){
	char num[10][200];
	char s[200], cal[10];
	int re[10][100], size[100];//전체식넣을곳
	int i, j = 0, k = 0, a = 0, b = 0, c = 0, max, maxx, result[200];

	fgets(s, sizeof(s) - 1, stdin); //입력받기

	for (i = 0; s[i] != '='; i++){
		if ('0' <= s[i] <= '9')  //숫자라면
			num[a][b] = s[i];
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
			cal[j] = s[i];
			size[a] = b;
			j++;
			a++;
			b = 0;
			continue;
		}
		if (s[i + 1] == '='){
			size[a] = ++b;
			continue;
		}
		b++;
	}   //cal and num separation

	for (i = 0; i <= a; i++){
		int t = size[i];
		for (j = t; j > 0; j--)
			re[i][t - j] = num[i][j - 1] - '0';
		//printf("%d", re[i][t - j]);
	}   //rearrange

	max = size[0];
	int largest2 = size[1];

	if (max<largest2)
		max = largest2;

	for (i = 2; i <= 10; i++) {
		if (size[i] >= max)
			max = size[i];
	}//max 구하기

	for (i = 0; i <= a; i++) {
		int p = size[i];
		if (p <= max) {
			for (j = p; j <= max; j++) {
				re[i][j] = 0;

			}
		}
	}//쓰레기값에 0넣기



	///////////////////////////////////////////연산자판별////////////////////////////////////////////////////////////////////////////////////////////////////////



	for (i = 0; i < a; i++){
		if (cal[i] == '*' || cal[i] == '/') {
			///////////////////////////////////////////////////*///////////////////////////
			if (cal[i] == '*') {

				maxx = size[i] + size[i + 1];

				for (int p = i; p < i + 2; p++) {
					//int p = size[i];
					for (j = max; j < maxx; j++)
						re[p][j] = 0;
				}


				for (j = 0; j < maxx; j++)
					result[j] = 0;

				for (j = 0; j < size[i]; j++){
					for (k = 0; k < size[i + 1]; k++){
						result[j + k] += re[i][j] * re[i + 1][k];
						if (result[j + k]>9){
							result[j + k + 1] += result[j + k] / 10;
							result[j + k] -= (result[j + k] / 10) * 10;
						}

					}		//re[i][j] = result[i][j];

				}

				for (j = 0; j <= maxx; j++){
					re[i][j] = result[j];//결과넣기
					if (re[i][j] < 0 || re[i][j]>9)
						re[i][j] = 0;
				}		//check!


				for (int j = i; j < a; j++) {
					cal[j] = cal[j + 1];
					for (int k = 0; k < size[j + 2]; k++)
						re[j + 1][k] = re[j + 2][k];
				}	//밀기
				for (k = maxx; re[i][k] == 0; k--);
				size[i] = ++k;
				//printf("%d\n", k);
				//printf("%d", k);
				for (k = i + 1; k < a; k++)
					size[k] = size[k + 1];	 //size바꾸기

				a--;
				i--;
			}
			else {

				if (size[i] < size[i + 1]){
					re[0][0] = 0;
					size[0] = 0;
				}
				else if (size[i] == size[i + 1]){
					int h = size[i] - 1;
					for (k = 0; k < h; k++)
						result[k] = 0;
					if (re[i][h] < re[i + 1][h]){
						re[0][0] = 0;
						size[0] = 0;
					}
					else{
						//result;
					}
				}

				a--;
				i--;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < a; i++) {
		if (cal[i] == '+') {

			if (size[i] >= size[i + 1])
				maxx = size[i];
			else
				maxx = size[i + 1];

			for (j = 0; j <= maxx; j++)
				result[j] = 0;

			for (j = 0; j <= maxx; j++){
				result[j] += re[i][j] + re[i + 1][j];

				if (result[j]>9){
					result[j] -= 10;
					result[j + 1] += 1;
				}
				re[i][j] = result[j];
			}
			result[maxx] += re[i][maxx] + re[i + 1][maxx];

			re[i][maxx + 1] = result[maxx + 1];

			for (k = maxx; re[i][k] == 0; k--);
			size[i] = ++k; 

			for (k = i; k < a; k++)
				size[k] = size[k + 1]; //size바꾸기

			for (int j = i; j < maxx; j++) {
				cal[j] = cal[j + 1];
				for (int k = 0; k < size[j + 2]; k++)
					re[j + 1][k] = re[j + 2][k];
			}   //하나씩 땡기기

			a--;
			i--;
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < a; i++) {
		if (cal[i] == '-'){

			int i1, i2;

			if (size[i] >= size[i + 1]){
				maxx = size[i];
				i1 = i, i2 = i + 1;
			}
			else if (size[i] < size[i + 1]){
				maxx = size[i + 1];
				i1 = i + 1, i2 = i;
			}

			for (j = 0; j <= maxx; j++)
				result[j] = 0;

			for (j = 0; j <= maxx; j++){

				result[j] += re[i1][j] - re[i2][j];

				if (result[j] < 0){
					result[j] += 10;
					re[i1][j + 1] -= 1;
				}
				re[i][j] = result[j];

			}


			for (k = maxx; re[i][k] == 0; k--);
			size[i] = ++k;
			for (k = i; k < a; k++)
				size[k] = size[k + 1]; //size바꾸기

			for (int j = i; j < maxx; j++) {
				cal[j] = cal[j + 1];
				for (int k = 0; k < size[j + 2]; k++)
					re[j + 1][k] = re[j + 2][k];
			}   //하나씩 땡기기
			a--;
			i--;
		}
	}
	for (int good = 100; good >= 0; good--){
		if (re[0][good] < 0 || re[0][good]>9)
			re[0][good] = 0;
		printf("%d", re[0][good]);
	}
	system("pause");
}