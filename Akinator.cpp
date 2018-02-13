#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct my_strucy1{
	string text;
	my_strucy1* left, right;
}tree_el;


void info();
tree_el* zapolnenye();
dobav_el();

int main(){
	info();
	tree_el* root = zapolnenye();


	return 0;
}

tree_el* zapolnenye(){
	tree_el* root;

	tree_el* new = dobav_el();

	return root;
}

void info(){
	printf("Dobro pojalovat!\n");
	printf("Vam neobxodimo zagadat jivotnoye\n")
	printf("A my popytaemsya otgadat ego.\n");
	puts("No snachala Vam nyjno bydet zapolnit akinatora");
}
