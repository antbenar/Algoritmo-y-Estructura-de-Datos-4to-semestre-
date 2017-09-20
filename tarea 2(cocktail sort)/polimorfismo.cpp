#include <iostream>
#include <time.h>
#include <random>
using namespace std;

int* GenerarArray(int tam){
	srand (time(NULL));
	int temp[10];
	int* head=temp;
	for(int i=0;i<tam;i++){
		temp[i] = rand() % 1000;
	}
	return head;
}
void BorrarArray(int* head, int tam){
	for(int i=0;i<tam;i++){
		delete (head+i);
	}
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
	int tam=5;
	int* a= GenerarArray(tam);
	int *p=a+tam-1;
	/*cout<<"ahlkjh";
	for(int i=0;i<tam;i++){
		cout<< a[i]<<" ";
	}*/
	
	mayorAmenor b;
	b.cocktailsort(a,p);
	
	for(int i=0;i<tam;i++){
		cout<< a[i]<<" ";
	}
	BorrarArray(a,tam);
}
