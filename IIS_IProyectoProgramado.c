#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista Lista;
typedef struct Nodo Nodo;
typedef char string[300];

typedef struct{
    int estado;
}estadosDisponibles;

typedef struct{
    string infoExtra;
}informacionExtra;

typedef struct{
    string numeroPlaca;
    string marca;
    string modelo;
    int anno;
    string color;
    int cilindrada;
    string tipoCombustible;
    int capacidadPasajeros;
    int precioAlquiler;
    int cantvehiculos;
    string tipoArchivo;
	int tamanoListaV;
	informacionExtra extras;
	int cantInfoExtra;
    estadosDisponibles tipoEstado;
}informacionVehiculos;

struct Nodo
{
    informacionVehiculos dato; 
    Nodo *siguiente;
};

struct Lista
{
	Nodo *inicio;
};

Lista *listaNueva(void)
{
	Lista *L;
	L = (Lista *) malloc(sizeof(Lista));
	L->inicio = NULL;
	return L;
}

informacionVehiculos listaExtra[0];

void lecturaDatosVehiculos(informacionVehiculos *infoV)
{
	int respuesta, cantInfoExtra, indice = 0;
	
	printf("Informacion del vehiculo %d\n\n", infoV->cantvehiculos);

    printf("\nIngrese el numero de placa: ");
	gets(infoV->numeroPlaca);

    printf("\nIngrese la marca: ");
	gets(infoV->marca);

    printf("\nIngrese el modelo: ");
	gets(infoV->modelo);

    printf("\nIngrese el anno: ");
	scanf("%d", &infoV->anno);
    getchar();

    printf("\nIngrese el color: ");
	gets(infoV->color);

    printf("\nIngrese la cilindrada que posee: ");
	scanf("%d", &infoV->cilindrada);
	getchar();

    printf("\nIngrese el tipo de combustible que utiliza: ");
	gets(infoV->tipoCombustible);

    printf("\nIngrese la capacidad de pasajeros: ");
	scanf("%d", &infoV->capacidadPasajeros);

	printf("\nIngrese el precio de alquiler por dia: ");
	scanf("%d", &infoV->precioAlquiler);
	
	printf("Desea agregar informacion extra?\n1.Si\n2.No\nDigite el numero correspondiente a su respuesta: ");
	scanf("%d", &respuesta);
	
	if(respuesta == 1)
	{
		printf("\n");
		printf("Cuanta informacion extra desea agregar? ");
		printf("Hola");
		scanf("%d", &infoV->cantInfoExtra);
		getchar();
	}
	
	while(indice < infoV->cantInfoExtra)
	{
		printf("%d.", indice+1);
		gets(listaExtra[indice].extras.infoExtra);
		indice++;
	}

	printf("\nIngrese el numero correspondiente al estado del vehiculo: \n 1- Disponible \n 2- Alquilado \n 3- En reparacion \n 4- Fuera de circulacion\n");
	scanf("%d", &infoV->tipoEstado.estado);
	getchar();
}

void insercionArchivos(informacionVehiculos *infoV)
{
	int indice = 0;
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\");
	
	strcat(ruta, infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, ruta);
	strcat(infoV->tipoArchivo, ".txt");
	
	archivo = fopen(infoV->tipoArchivo, "a+");
	fprintf(archivo,"%s; %s; %s; %d; %s; %d; %s; %d; %d;", infoV->numeroPlaca, infoV->marca, infoV->modelo, infoV->anno, infoV->color, infoV->cilindrada, infoV->tipoCombustible, infoV->capacidadPasajeros, infoV->precioAlquiler);
	
	while(indice < infoV->cantInfoExtra)
	{
		fprintf(archivo, " %s,", listaExtra[indice].extras.infoExtra);
		indice++;
		
		if(indice == infoV->cantInfoExtra-1)
		{
			fprintf(archivo, " %s; %d;", listaExtra[indice].extras.infoExtra, infoV->tipoEstado.estado);
			indice++;
		}
	}
}

void insertarVehiculo(Lista *L, informacionVehiculos infoV)
{
	int contador = 0;
	int cantidadPreguntas;

	printf("Cuantos vehiculos desea registrar? ");
	scanf("%d", &cantidadPreguntas);
	getchar();
	printf("\n\n");
	
	infoV.cantvehiculos = 1;
	while(contador < cantidadPreguntas)
	{
		lecturaDatosVehiculos(&infoV);
		Nodo *n, *aux;

		if(L->inicio == NULL) //Valida si la lista esta vacia
		{
			L->inicio = (Nodo *) malloc(sizeof(Nodo));
			L->inicio->dato = infoV;
			L->inicio->siguiente = NULL;	
		}
		else
		{
			n = L->inicio;
			while(n != NULL)
			{
				aux = n;
				n = n->siguiente;
			}
			aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
			aux->siguiente->siguiente = NULL;
			aux->siguiente->dato = infoV;
		}
		contador++;
		infoV.cantvehiculos++;
		insercionArchivos(&infoV);
	}	
	printf("\n");
	printf("El registro de los vehiculos se ha realizado exitosamente\n");
}

void extraerListaVehiculos(informacionVehiculos *infoV, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int respuesta;
	string marca;
	string modelo;
	string anno;
	string color;
	string cilindrada;
	string tipoDeCombustible;
	string capacidadPasajeros;
	string precioAlquiler;
	string estado;
	string espacio = " ";
	
	printf("Que desea modificar?\n1.Marca\n2.Modelo\n3.Anno\n4.Color\n5.Cilindrada\n6.Tipo de combustible\n7.Capacidad de pasajeros\n8.Precio de alquiler\n9.Estado del vehiculo\n");
	scanf("%d", &respuesta);
	getchar();
	
	if(respuesta == 1)
	{
		printf("Ingrese la nueva marca: ");
		gets(marca);
		strcpy(lista[1], espacio);
		strcat(lista[1], marca);
	}
	
	else if(respuesta == 2)
	{
		printf("Ingrese el nuevo modelo: ");
		gets(modelo);
		strcpy(lista[2], espacio);
		strcat(lista[2], modelo);
	}
	else if(respuesta == 3)
	{
		printf("Ingrese el nuevo anno: ");
		gets(anno);
		strcpy(lista[3], espacio);
		strcat(lista[3], anno);
	}
	else if(respuesta == 4)
	{
		printf("Ingrese el nuevo color: ");
		gets(color);
		strcpy(lista[4], espacio);
		strcat(lista[4], color);
	}
	else if(respuesta == 5)
	{
		printf("Ingrese la nueva cilindrada: ");
		gets(cilindrada);
		strcpy(lista[5], cilindrada);
	}
	else if(respuesta == 6)
	{
		printf("Ingrese el nuevo tipo de combustible: ");
		gets(tipoDeCombustible);
		strcpy(lista[6], espacio);
		strcat(lista[6], tipoDeCombustible);
	}
	else if(respuesta == 7)
	{
		printf("Ingrese la nueva capacidad de pasajeros: ");
		gets(capacidadPasajeros);
		strcpy(lista[7], espacio);
		strcat(lista[7], capacidadPasajeros);
	}
	else if(respuesta == 8)
	{
		printf("Ingrese el nuevo precio de alquiler: ");
		gets(precioAlquiler);
		strcpy(lista[8], espacio);
		strcat(lista[8], precioAlquiler);
	}

	else
	{
		printf("Ingrese el nuevo estado: \n 1- Disponible \n 2- Alquilado \n 3- En reparacion \n 4- Fuera de circulacion\n");
		gets(estado);
		strcpy(lista[9], espacio);
		strcat(lista[9], estado);
	}
	
	string rutaAux;
	strcpy(rutaAux, ".\\InfoVehiculos\\");
	strcat(rutaAux,infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, rutaAux);
	strcat(infoV->tipoArchivo, ".txt");
	archivoAux = fopen(infoV->tipoArchivo, "a+");
	
	while(indice < infoV->tamanoListaV)
	{	
		if(indice == (infoV->tamanoListaV)-1)
		{
			fprintf(archivoAux,"%s;", lista[indice]);
		}
		else
		{
			fprintf(archivoAux,"%s;", lista[indice]);
		}
		indice ++;
	}
	printf("\n");
	printf("La modificacion se realizo exitosamente");
	//exit(-1);
}

void modificarInfoV(informacionVehiculos *infoV)
{
	FILE *archivo = NULL; 
	
	string listaVehiculos[100];
	infoV->tamanoListaV = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese la placa del vehiculo al cual desea modificar: ");
	gets(infoV->numeroPlaca);
	
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\");
	strcat(ruta, infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, ruta);
	strcat(infoV->tipoArchivo, ".txt");
	
	archivo = fopen(infoV->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaVehiculos[indice], token);
      			printf("%s\n", token);
      			infoV->tamanoListaV++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoV->tipoArchivo);
	extraerListaVehiculos(infoV, listaVehiculos);
}

void eliminarVehiculo(informacionVehiculos *infoV)
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\");
	
	printf("Ingrese la placa del vehiculo que desea eliminar: ");
	gets(infoV->numeroPlaca);
	
	strcat(ruta, infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, ruta);
	strcat(infoV->tipoArchivo, ".txt");
	
	archivo = fopen(infoV->tipoArchivo, "w");

	fclose(archivo);
	
	remove(infoV->tipoArchivo);
	printf("\nEl vehiculo ha sido eliminado del sistema\n");
}

void infoUnVehiculo(informacionVehiculos *infoV)
{
	FILE *archivo = NULL; 
	
	string listaVehiculos[100];
	infoV->tamanoListaV = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese la placa del vehiculo al cual desea consultar la informacion: ");
	gets(infoV->numeroPlaca);
	
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\");
	strcat(ruta, infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, ruta);
	strcat(infoV->tipoArchivo, ".txt");
	
	archivo = fopen(infoV->tipoArchivo, "a+");
	
	printf("\n");
	printf("La informacion del vehiculo es: ");
	printf("\n\n");
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
				printf("%s\n", token);
      			indice++;
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
}

int main()
{
    Lista *L;
	L = listaNueva();
    informacionVehiculos vehiculo;

    //insertarVehiculo(L, vehiculo);
	//modificarInfoV(&vehiculo);
	//eliminarVehiculo(&vehiculo);
	infoUnVehiculo(&vehiculo);
    
    return 0;
}
