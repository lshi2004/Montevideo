#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void print_cont_sequence (int small, int big)
{
	printf("New Sequence: ");

	while (small <= big) {
		printf("%d \t", small++);
	}
	printf("\n");
}

void find_cont_sequence(int sum)
{
	if (sum < 3) {
		return;
	}

	int small = 1;
	int big = 2;
	int middle = (1 + sum) / 2;

	int cur_sum = small + big;

	while (small < middle) {
		if (cur_sum == sum) {
			print_cont_sequence(small, big);

		}

		while (cur_sum > sum && small < middle) {
			cur_sum -= small;
			++small;

			if (cur_sum == sum) {
				print_cont_sequence(small, big);
			}
		}

		++big;
		cur_sum += big;
	}
}

void reverse_string (char *pBegin, char *pEnd)
{
	if (!pBegin || !pEnd) {
		return;
	}

	while (pBegin < pEnd) {
		char tmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = tmp;
		pBegin++;
		pEnd--;
	}

}


void reserse_sentence (char *pData)
{
	if (!pData) {
		return;
	}

	char *pBegin = pData;
	char *pEnd = pData;

	while (*pEnd != '\0') {
		pEnd++;
	}
	pEnd--;

	reverse_string(pBegin, pEnd);

	printf("inside reverse sentence %s \n\n", pData);

	pBegin = pEnd = pData;
	while (*pBegin != '\0') {
		if (*pBegin == ' ') {
			pBegin++;
			pEnd++;
		} else if (*pEnd == ' ' || *pEnd == '\0') {
			reverse_string(pBegin, pEnd-1);
			pBegin = pEnd;
		} else {
			pEnd++;
		}
	}


}

int main()
{

	char *ptr = malloc(100*sizeof(char));
	strcpy(ptr, "Hello World China");

#if  0
	printf("hello World %d %s \n",
			strlen(ptr), ptr);

	reverse_string(ptr, ptr+strlen(ptr)-1);

	printf("after hello World %d %s \n",
				strlen(ptr), ptr);

#endif

	reserse_sentence(ptr);

	printf(" The result is: \n %s \n", ptr);

	// find_cont_sequence(60);
	return 0;
}


