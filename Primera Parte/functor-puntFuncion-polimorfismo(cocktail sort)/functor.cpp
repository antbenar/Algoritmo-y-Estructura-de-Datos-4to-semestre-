#include <iostream>

using namespace std;

class menorAmayor
{
public:
	bool operator ()(int *p1, int *q){
		return *p1>*q;
	}
};

class mayorAmenor
{
public:
	bool operator ()(int *p1, int *q){
		return *p1<*q;
	}
};

template<typename T>
class cocktailsort
{
	T tipoOrdenacion;
	
	void swap(int *p, int *q){
		int temp=*p;
		*p=*q;
		*q=temp;
	}
public:
	int operator()(int*p,int*s )
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

int main()
{
	int a[]={4,8,2,3,1};
	int tam=sizeof(a)/sizeof(a[0]);//cout<<tam<<endl;
	int *p=a+tam-1;
	
	cocktailsort<mayorAmenor> b;
	b(a,p);
	
	for(int i=0;i<tam;i++){
		cout<< a[i]<<" ";
	}
}
