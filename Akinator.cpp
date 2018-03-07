#include<iostream>//otvechaet za potokovyi vvod i vyvod
#include<fstream>//fyalovyi vvod i vyvod
#include<string>//rabota so strokami
//#include<STL>//chablony dlya raznyx struktur dannyx, rabotaychix s etimi dannymi
#include<algorithm>//sortyrovka i td

/* eche mojno dobavlyat starye faily 

V ci stdio.h
C ci++ cstdio	*/

#include<cmath>

/**********************************************/
/* scoro sdacha */
/*pechat dereva cherez dot
 qut*/

class tree{
	public:
		/*v classax tolko te, kto yje v sozdannom dereve*/
		std::string s;
		tree* da_right;
		tree* net_left;
		
		
		//tree dobav(tree* temp, tree* sa, int flag);
		
	private:
		
		
};
tree* game(tree* head);//vozvrachaet na chem conchili
tree* create_basic_tree();
void otchistka(tree* head);
tree* create_new_element();
void raspechatka(tree* head);
/*********************************************/


int main(){
	//info();
	std::cout<<"0 -- da"<<"1 -- net"<<std::endl;
	tree* head = create_basic_tree();
	puts("m1");
	tree* temp = game(head);
	
	raspechatka(head);
	otchistka(head);
	return 0;
}

void otchistka(tree* head){
	if(head){
		otchistka(head->da_right);
		otchistka(head->net_left);
		free(head);
	}
}

tree* game(tree* head){
	tree* temp = head;
	int n;
	
	while((temp->da_right)&&(temp->net_left)){
		std::cout<<temp->s<<std::endl;
		std::cin>>n;
		if(n > 0){temp = temp->da_right;}
		else{temp = temp->net_left;}}
	
	std::cout<<"Eto: "<<temp->s<<"!"<<std::endl;
	std::cout<<"Ya ygadal?"<<"\n"<<"0 -- NET	1 -- DA"<<std::endl;
	if(n <= 1){
		/*n = 0;
		tree* sa = temp;
		tree* prev = NULL;
		n = 0;
		dobav(head, &sa, &n, &prev);
		/*teper v sa prev elem*/
		std::cout<<"Kogo Vy xoteli?"<<std::endl;
		tree* new1 =  create_new_element();
		std::cin>>new1->s;
		tree* new2 =  create_new_element();
		new2->s = temp->s;
		std::cout<<"V chem raslichie?"<<std::endl;
		std::cin>>temp->s;
		std::cout<<"Y novogo chlena eto est?\n da -- 0	net -- 1"<<std::endl;
		std::cin>>n;
		temp->s = "Eto" + temp->s + "?";
		if(n == 0){
			temp->da_right = new1;
			temp->net_left = new2;
		}
		else{
			temp->da_right = new2;
			temp->net_left = new1;
		}
		
	}

}

/*yznaet predydych elem
tree dobav(tree* temp, tree* sa, int flag, tree* prev){
	/*poisk adresa elementa, vyzov doav 1 s voprosami
	tree* prev = temp;
	if(temp){
		dobav(temp->net_left, *sa, *flag, *prev);
		dobav(temp->da_right, *sa, *flag, *prev);
		if(temp == *sa) && (*flag == 0)){
			*flag = 1;
			*sa = *prev;
		}
	}
	
}*/


void raspechatka(tree* head){
	if (head != NULL) { 
    raspechatka(head->da_right);
    raspechatka(head->net_left); 
    std::cout << head->s; 
  }
}

/***********************************************/

tree* create_basic_tree(){
	tree*  head = create_new_element();
	puts("cbt1");
	head->s = "Eto jivoe?";
	head->da_right = create_new_element();
	puts("cbt2");
	head->net_left = create_new_element();
	puts("cbt3");
	head->da_right->s = "Putin";
	head->net_left->s = "Vodka";
	puts("cbt4");
	return head;}

tree* create_new_element(){
	puts("cne1");
	tree* temp = (tree*)malloc(sizeof(tree));
	puts("cne2");
	temp->s = "Vsavte vach text suda";
	temp->da_right = NULL;
	temp->net_left = NULL;
	puts("		");
	std::cout<<temp<<std::endl;
	return temp;
}
			
/*			
void info(){
	std::cout<<0 -- da<<1 -- net<<std::endl;
}*/
