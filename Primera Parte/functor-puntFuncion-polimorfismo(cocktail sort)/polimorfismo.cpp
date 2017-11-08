#include <iostream>
#include <time.h>
#include <random>
#define size 1000000
#define tam_rand 1000
using namespace std;

int* GenerarArray(){
	srand (time(NULL));
	int* head=new int[size];
	int*temp=head;
	
	for(int i=0;i<size;i++){
		temp[i] = rand() % tam_rand;
	}
	
	return head;
}
void BorrarArray(int* head){
	delete[] head;
}

class cocktailsort_
{
public:
	virtual bool tipoOrdenacion(int *p,int *q)=0;
	
	void swap(int *p, int *q){
		int temp=*p;
		*p=*q;
		*q=temp;
	}

	cocktailsort(int*p,int*s )
	{
		int *temp2,*temp;
		bool cambio = true;
		while(cambio){
			cambio = false;
			while(p<s)
			{
				temp = p;
				while(temp<s){
					if(tipoOrdenacion(temp,temp+1)){
						swap(temp,temp+1);
						cambio=true;
					}
					temp++;
				}
				temp2 = s;
				while(temp2>p){
					if(tipoOrdenacion(temp2-1,temp2)){
						swap(temp2-1,temp2);
						cambio=true;
					}
					temp2--;
				}
				++p;
				--s;
			}
		}
	}
};

class menorAmayor: public  cocktailsort_
{
public:
	bool tipoOrdenacion (int *p1, int *q){
		return *p1>*q;
	}
};

class mayorAmenor: public  cocktailsort_
{
public:
	bool tipoOrdenacion (int *p1, int *q){
		return *p1<*q;
	}
};

int main()
{
	int* a= GenerarArray();
	int *p=a+size-1;
	/*for(int i=0;i<tam;i++){
		cout<< a[i]<<" ";
	}*/
	
	menorAmayor b;
	b.cocktailsort(a,p);
	
	for(int i=0;i<size;i++){
		cout<< a[i]<<" ";
	}
	BorrarArray(a);
}
