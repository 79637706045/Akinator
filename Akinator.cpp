#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct my_strucy1{
	string text;
	my_strucy1* left, right;
}tree_el;


void info();
tree_el* zapolnenye();
tree_el* dobav_el();
void chitat_elementy(tree_el* current, int* n);
void viz(root, int n);
void print_tree(tree_element* root);

/*Funksia naxodit adress elementa po nomery lista sprava*/
tree_el* nomer_v_obxode(root, rechen);

int main(){
	info();
	tree_el* root = zapolnenye();


	return 0;
}


/*************************************************/
tree_el* zapolnenye(){
	tree_el* root = dobav_el();
	printf("Vvedite nomer, znachenie kornevogo elementa\n");
	scanf("%s\n", root->value);
	while(1){
	printf("Vvodite nomer lista sprava, kotorui xochete ydlinit\n");
	printf("Vvedite "0", esli xotite zavechit process\n");
	print_tree(root);
	int rechen = 0;
	scanf("%d", &rechen);

	if(rechen <= 0){
		break;}

	else{
	tree_el* des = NULL;
	des = nomer_v_obxode(root, rechen);//yznayot kakoy element zadymal polzovatel i vosvrachaet ego adress
	print("Vvedite dsnnyi elementa sleva\n");
	tree_el* newL = NULL;
	newL = dobav_el();
	scanf("%s\n", newL->value);
	print("Vvedite dsnnyi elementa sprava\n");
	tree_el* newR = NULL;
	newR = dobav_el();
	scanf("%s\n", newR->value);
	des->left = newL;
	des->right = newR;
	}
	}
	return root;
}

tree_el* nomer_v_obxode(root, rechen){
	/*polyschili koren i nomer, lista, nayti adress lista
	chtoby ne zamorachivatca s vozvratom v rekursii, primenit adresnye sposoby*/
	int kol_el = 0;
	chitat_elementy(root, &kol_el);

	int kol_yrov = 1;
	int kol_list = kol_el - 1;
	while(1){
		kol_list -= pow(2,kol_yrov);
		if(kol_list == 0){break;}
		kol_yrov++;}
	/*rasschitaem koichestvo listev*/
	kol_list = kol_yrov;
	for(int i = 0; i < kol_yrov; ++i){
		kol_list -= pow(2, i);
	}
	/*ostalos yznat adress lista s nujnym nomerom */

}

/****************************************************************/
void print_tree(tree_element* root){/*v postfiksnoy forme*/
	int kol_el = 0;
	chitat_elementy(root, &kol_el);

	int kol_yrov = 1;
	temp1 = kol_el - 1;
	while(1){
		temp1 -= pow(2,kol_yrov);
		if(temp1 == 0){break;}
		kol_yrov++;}

	temp1 = kol_yrov;
	for(int i = 1; i <= temp1; ++i){
		int p = 0;
		viz(root, i, p);
		puts("");
	}
}

void viz(current, n, p){
	if ((n != p) && (current != NULL)){
		 n++;
	   viz(current->left, n+1, p);
	   viz(current->right, n+1, p);
	}
	if(n == i){
		printf("%s	", current->value);
	}
}

void chitat_elementy(tree_element* current, int* adr){
	if (current != NULL)	{
	   chitat_elementy(current->left, adr);
	   chitat_elementy(current->right, adr);
	   (*adr)++;}
}
/***************************************/


tree_el* new = dobav_el(){
	tree_el* elem = (elem*)malloc(sizeof(tree_el));
	elem->left = NULL;
	elem->right = NULL;
	elem->value = printf("Vvedite text.");
	return elem;
}

void info(){
	printf("Dobro pojalovat!\n");
	printf("Vam neobxodimo zagadat jivotnoye\n")
	printf("A my popytaemsya otgadat ego.\n");
	puts("No snachala Vam nyjno bydet zapolnit akinatora");
}
