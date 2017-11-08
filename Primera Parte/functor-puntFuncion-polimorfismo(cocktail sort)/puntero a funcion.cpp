#include <iostream>
using namespace std;

void swap(int *p, int *q){
	int temp=*p;
	*p=*q;
	*q=temp;
}

bool menorAmayor_(int *p1, int *q){
	return *p1>*q;
}

bool mayorAmenor_(int *p1, int *q){
	return *p1<*q;
}

typedef bool (*firma)(int *p, int *q);
firma mayorAmenor=mayorAmenor_;
firma menorAmayor=menorAmayor_;

void cocktailsort(int*p,int*s,(*tipoOrdenacion)(int *p, int *q) )
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

int main(int argc, char *argv[]) {
	int a[]={4,8,2,3,1};
	int tam=sizeof(a)/sizeof(a[0]);//cout<<tam<<endl;
	int *p=a+tam-1;
	
	cocktailsort(a,p,mayorAmenor);
	
	for(int i=0;i<tam;i++){
		cout<< a[i]<<" ";
	}
}

