/*
 ============================================================================
 Name        : CP1.c
 Author      : HS
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse_single(char *start, char *end)
{
	char tmp;

	while (start < end) {
		tmp = *end;
		*end-- = *start;
		*start++ = tmp;
	}

	return 0;
}

char* find_next_token(char *start)
{
	while (*start != ' ' &&  *start != '\0')
		start++;


	return start;
}

int reverse_string(char * str)
{
	char *start = str;
	char *end;

	// reverse the whole string
	reverse_single(str, str + strlen(str) -1);


	// find next token
	// reverse each string
	do {
		end = find_next_token(start);
		reverse_single(start, end - 1);
		start = end + 1 ;
	} while (*end);

	return 0;
}


void permutation_core(char *orig_str, char *work_str)
{
	char *p_ch = NULL;
	char tmp;
	static int p_counter = 0;

	if (*work_str == '\0') {
		printf("one more string: %s %d \n", orig_str, p_counter++);
	} else {
		for (p_ch = work_str; *p_ch != '\0'; p_ch++) {
			tmp = *p_ch;
			*p_ch = *work_str;
			*work_str = tmp;

			permutation_core(orig_str, work_str+1);

			tmp = *p_ch;
			*p_ch = *work_str;
			*work_str = tmp;
		}

	}

}

int getGreatestSumOfSubArray(int *numbers, int length) {
	int curSum = 0;

	int greatestSum = 0;

	for (int i = 0; i < length; ++i) {
		printf("the number is %d\n", numbers[i]);
		if (curSum <= 0) {
			curSum = numbers[i];
		} else {
			curSum += numbers[i];
		}

		if (curSum > greatestSum)
			greatestSum = curSum;
	}

	return greatestSum;
}


int main(void) {
	char str[20];
	char *ptr = "0123456789";
	int num[] = {1, -2, 3, 10, -4, 7, 2, -5};

	printf("ptr length is %d \n", strlen(ptr));




	strcpy(str, "  the sky is blue");

	//reverse_single(str, str+strlen(str)-1);
	reverse_string(str);

	printf("ptr length is %d string %s\n", strlen(ptr), str);

	//printf("the length is %d \n", strlen(str));

	//permutation_core(str, str);

	int sum = getGreatestSumOfSubArray(num, 8);

	printf("the sum is %d \n\n", sum);

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
