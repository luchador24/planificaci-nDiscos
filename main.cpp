#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <vector>
#include <stdlib.h>		//Funcion necesaria para NEW y DELETE
using namespace std;

void pedirDatos();
bool verificarRepetidos();
void mostrarDatos(int&);
void mostrarMovimientos();
void planificacionSSTF();
void reiniciarProg();

int nCabezal , num , *datos , nCilindros , n=0;
float promedio=0;

int main(){

	int opc;

	do{

	cout<<"---PLANIFICACION DISCO---\n\n";
	cout<<"1. Planificacion FCFS"<<endl;
	cout<<"2. Planificacion LIFO"<<endl;
	cout<<"3. Planificiacion SSTF"<<endl;
	cout<<"4. Salir"<<endl;
	cout<<"\nIngrese opcion: "; cin>>opc;

	switch(opc){

				//FCFS
		case 1: system("cls");
				pedirDatos();
				cout<<"\nCola ordenada (FCFS): ";
				mostrarDatos(opc);
				mostrarMovimientos();
				cout<<"\nEl promedio es: "<<promedio/n<<endl;
				break;

				//LIFO
		case 2: system("cls");
				pedirDatos();
				cout<<"\nPila ordenada (LIFO): ";
				mostrarDatos(opc);
				mostrarMovimientos();
				cout<<"\nEl promedio es: "<<promedio/n<<endl;
				break;

				//SSTF
		case 3: system("cls");
				pedirDatos();
				planificacionSSTF();
				cout<<"\nEl promedio es: "<<promedio/n<<endl;
				break;

		case 4: break;

		default: cout<<"\nOpcion no valida, intente de nuevo...";
				 break;
	}

	getch();
	reiniciarProg();
	system("cls");

	}while(opc!=4);

	delete[] datos; //liberando el espacio en bytes del datos Datos

	return 0;
}

//Funcion para pedir datos
void pedirDatos(){
	cout<<"Ingrese numero de cilindros: "; cin>>nCilindros;
	datos = new int[nCilindros]; //Creando el datos;

	do{
		cout<<"Posicion incial de cabezal: "; cin>>nCabezal;
		if(nCabezal>nCilindros){
			cout<<"El cabezal no puede ser mayor al numero de cilindros!\n\n";
		}else if(nCabezal<0){
			cout<<"El cabezal no puede ser un numero negativo!\n\n";
		}else{
			datos[n]=nCabezal;
			promedio += nCabezal;
			n++;
		}
	}while(datos[n]>nCilindros);

	char respuesta;
	do{
		cout<<"Ingrese un numero: "; cin>>num;
		if(num>nCilindros){
			cout<<"\nEl numero no puede ser mayor al numero de cilindros"<<endl;
		}else if(num<0){
			cout<<"\nEl numero no puede ser negativo"<<endl;
		}else if(verificarRepetidos()==true){
			cout<<"\nNo se puede repetir numeros"<<endl;
		}else{
			datos[n] = num;
			promedio += num;
			n++;
			if(n==nCilindros){
				cout<<"Se alcanzo el numero de cilindros"<<endl;
				respuesta = 'n';
			}else{
				cout<<"Desea ingresar otro numero? (S/N): "; cin>>respuesta;
			}
		}
	}while( respuesta=='s' || respuesta=='S' || num>nCilindros || verificarRepetidos()==false || num<0);
}

//Funcion para verificar que no se repitan los numeros
bool verificarRepetidos(){
	for(int i=0;i<n;i++){
		if(datos[i] == num){
			return true;
		}
	}
	return false;
}

void mostrarDatos(int& opc){
	if(opc==2){
		int aux;							//Si la opc es 2, convierte a pila
		for(int i=0,e=n-1;i<e;i++,e--){
			aux = datos[i];
			datos[i] = datos[e];
			datos[e] = aux;
		}
	}

	for(int i=0;i<n;i++){					//Muestra el arreglo ya sea cola o pila
		cout<<datos[i]<<" ";
		}

	cout<<"\tPosicion inicial: "<<nCabezal<<"\n\n";
	}

void mostrarMovimientos(){

	//Imprimiendo recorrido
	int n1,n2,resul=0;
		for(int e=0,i=1;i<n;i++,e++){
			n1 = datos[e];
			n2 = datos[i];
			cout<<"Movimiento "<<i<<": "<<n1<<" a "<<n2<<", posiciones recorridas: ";
			if(n1>n2){
				resul = n1-n2;
			}else{
				resul = n2-n1;
			}
			cout<<resul<<endl;
		}

	int datos1[n];
	int i,j,aux;
	int mayor=0;

	n1=0;
	n2=0;

	//Asignandole valores al arreglo 'datos1'
	for(i=0;i<n;i++){
		datos1[i] = datos[i];
	}

	//Ordenando de menor a mayor el arreglo 'datos1' con metodo burbuja
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(datos1[j] > datos1[j+1]){
				aux = datos1[j];
				datos1[j] = datos1[j+1];
				datos1[j+1] = aux;
			}
		}
	}

	//Generando grafico
	cout<<"\n";
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){

		n1 = datos[i];
		n2 = datos[i+1];

		if(n1>n2){
			mayor = 1;
		}else if(n2>n1){
			mayor = 2;
		}

		if(mayor==1){
			if(datos1[j]==n2){
				cout<<datos1[j]<<" <";
			}else if(datos1[j]>n2 && datos1[j]<n1){
				cout<<"---";
			}else if(datos1[j]==n1){
				cout<<"   "<<datos1[j]<<"   ";
			}else if(n1!=n2){
				cout<<datos1[j]<<"   ";
			}
		}else if(mayor==2){
			if(datos1[j]==n1){
				cout<<datos1[j]<<" ";
			}else if(datos1[j]>n1 && datos1[j]<n2){
				cout<<"---";
			}else if(datos1[j]==n2){
				cout<<"> "<<datos1[j]<<"   ";
			}else if(n1!=n2){
				cout<<datos1[j]<<"   ";
			}
		}
		}
	cout<<"\n\n";
	}

}

void planificacionSSTF(){
	// Tamaño de la cola de peticiones
    const int tamanoCola = n;

    // Cola de peticiones
    vector<int> colaPeticiones;
		for (int i = 0; i < tamanoCola; ++i) {
    	colaPeticiones.push_back(datos[i]);
		}

    // Posición inicial del cabezal de lectura/escritura
    int posicionInicial = 0;

    // Imprimiendo la cola de peticiones
    cout << "\nCola de peticiones: ";
    for (int i = 0; i < tamanoCola; ++i) {
        cout<<colaPeticiones[i] << " ";
    }

    // Imprimiendo la posición inicial del cabezal
    cout<<"\tPosicion inicial: "<<nCabezal<<endl;

    // Calculando el SSTF (Shortest Seek Time First)
    vector<int> colaOrdenada;
    colaOrdenada.push_back(nCabezal);

    for (int i = 0; i < tamanoCola; ++i) {
        int distanciaMinima = INT_MAX;
        int indiceMinimo = -1;

        for (int j = 0; j < tamanoCola; ++j) {
            if (colaPeticiones[j] != -1) {
                int distanciaActual = abs(colaPeticiones[j] - colaOrdenada.back());
                if (distanciaActual < distanciaMinima) {
                    distanciaMinima = distanciaActual;
                    indiceMinimo = j;
                }
            }
        }

        colaOrdenada.push_back(colaPeticiones[indiceMinimo]);
        colaPeticiones[indiceMinimo] = -1;
    }

    // Imprimiendo la cola ordenada según SSTF
    cout<<"\nCola ordenada (SSTF): ";
    for (int i = 1; i <= tamanoCola; ++i) {
		cout<<colaOrdenada[i]<<" ";
    }
    cout<<"\n\n";

    // Imprimiendo recorrido
    int n1,n2,resul=0;
		for(int e=1,i=2;i<=n;i++,e++){
			n1 = colaOrdenada[e];
			n2 = colaOrdenada[i];
			cout<<"Movimiento "<<e<<": "<<n1<<" a "<<n2<<", posiciones recorridas: ";
			if(n1>n2){
				resul = n1-n2;
			}else{
				resul = n2-n1;
			}
			cout<<resul<<endl;
		}
    cout<<"\n";

    //Imprimiendo grafico
    for(int i=0;i<n-1;i++){
			for(int j=1;j<=n;j++){
				if(i+1==j){
					cout<<colaOrdenada[j]<<" -> ";
				}else{
					cout<<colaOrdenada[j]<<"    ";
				}

			}
		cout<<"\n";
		}
}

void reiniciarProg(){
	nCabezal=0;
	num=0;
	nCilindros=0;
	n=0;
	promedio = 0;
	delete[] datos;
}
