/* Программа создает две структуры с одинаковыми полями,
 в структуре ComressedPerson структура занимает меньшее количество 
 машинных слов */
#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>

struct Person{
		char name[16];
		char surname[32];
		int age;
		int GPA;
	} person;

struct CompressedPerson{
	int age;
	int GPA;
	char name[16];
	char surname[32];
} compressedperson;

int main(){
	puts("for struct Person");
	printf("%ld ", offsetof(struct Person, age));
	printf("%ld ", offsetof(struct Person, GPA));
	printf("%ld ", offsetof(struct Person, name));
	printf("%ld\n", offsetof(struct Person, surname));
	puts("for struct CompressedPerson");
	printf("%ld ", offsetof(struct CompressedPerson, age));
	printf("%ld ", offsetof(struct CompressedPerson, GPA));
	printf("%ld ", offsetof(struct CompressedPerson, name));
	printf("%ld\n", offsetof(struct CompressedPerson, surname));
}

