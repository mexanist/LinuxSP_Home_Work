/* Программа принимает введенное пользователем число N и возвращает
 число 2 в степени N. Для вычисления даннго числа используется
 функция degree аргументы которой передаются по ссылке.
 Максимальное число равно 2 в степени 31, поэтому введенное пользователем
 число проходит проверку на максимальную степень двойки, которая является максимальным
 значением которое хранит тип unsigned int */

#include "degree.h"

int main() {
	unsigned int rat;
	printf("Input of ratio degree: ");
	if (scanf("%d", &rat) == 1){
		if (rat > MAX_ROT){
			puts("maximum ratio");
			exit(EXIT_SUCCESS);
		}	
		degree(&rat);
		printf("Degree of 2 %u\n", rat);
	} else {
		puts("Need to digit");
	}
}


