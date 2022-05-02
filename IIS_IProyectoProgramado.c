#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista Lista;
typedef struct ListaCliente ListaCliente;
typedef struct Nodo Nodo;
typedef char string[300];

// --- Estados de un vehiculo --- //
char *DISPONIBLE = "Disponible";
char *ALQUILADO = "Alquilado";
char *EN_REPARACION = "En reparacion";
char *FUERA_DE_CIRCULACION = "Fuera de circulacion";
//-------------------------------//										

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
	int tamanoPlacas;
	int numeroVehiculos;
    string estado;
}informacionVehiculos;

typedef struct{
	string numeroCedula;
	string nombreCompleto;
	string fechaNacimiento;
	string correoElectronico;
	string categoria;
	string tipoArchivo;
	int tamano;
}informacionCliente;

struct Nodo
{
    informacionVehiculos dato; 
    informacionCliente dato2;
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

struct ListaCliente
{
	Nodo *inicio2;
};

ListaCliente *lista2(void)
{
	ListaCliente *C;
	C = (ListaCliente *) malloc(sizeof(ListaCliente));
	C->inicio2 = NULL;
	return C;
}

informacionVehiculos listaExtra[0];
void menu(Lista *L, ListaCliente *C, informacionVehiculos infoV, informacionCliente infoC);

void lecturaDatosVehiculos(informacionVehiculos *infoV)
{
	int respuesta, cantInfoExtra, indice = 0, numEstado;
	
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
	printf("\n");
	
	printf("Desea agregar informacion extra?\n1.Si\n2.No\nDigite el numero correspondiente a su respuesta: ");
	scanf("%d", &respuesta);
	
	if(respuesta == 1)
	{
		printf("\n");
		printf("Cuanta informacion extra desea agregar? ");
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
	scanf("%d", &numEstado);
	getchar();

	if(numEstado == 1)
	{
		strcpy(infoV->estado, DISPONIBLE);
	}
	else if(numEstado == 2)
	{
		strcpy(infoV->estado, ALQUILADO);
	}
	else if(numEstado == 3)
	{
		strcpy(infoV->estado, EN_REPARACION);
	}
	else
	{
		strcpy(infoV->estado, FUERA_DE_CIRCULACION);
	}
}

void insercionArchivosVehiculos(informacionVehiculos *infoV)
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
	}
	fprintf(archivo, " %s;",infoV->estado);
}

void creacionTxTPlacas(informacionVehiculos *infoV)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\Placas");
	
	strcpy(infoV->tipoArchivo, ruta);
	strcat(infoV->tipoArchivo, ".txt");
	
	archivo = fopen(infoV->tipoArchivo, "a+");
	fprintf(archivo,"%s;", infoV->numeroPlaca);
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
		insercionArchivosVehiculos(&infoV);
		creacionTxTPlacas(&infoV);
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
		fprintf(archivoAux,"%s;", lista[indice]);
		indice++;
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

void eliminarPlacaTotal(informacionVehiculos *infoV, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;

	while(indice < infoV->tamanoListaV)
	{
		if(strcmp(lista[indice], infoV->numeroPlaca) == 0)
		strcpy(lista[indice], "");
		indice++;
	}

	string rutaAux;
	strcpy(rutaAux, ".\\InfoVehiculos\\Placas");
	strcpy(infoV->tipoArchivo, rutaAux);
	strcat(infoV->tipoArchivo, ".txt");
	archivoAux = fopen(infoV->tipoArchivo, "a+");
	
	indice = 0;
	while(indice < infoV->tamanoListaV)
	{	
		fprintf(archivoAux,"%s;", lista[indice]);
		indice++;
	}
}

void datosPlacasTotales(informacionVehiculos *infoV)
{
	FILE *archivo = NULL; 
	
	string listaVehiculos[100];
	infoV->tamanoListaV = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\Placas");
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
      			infoV->tamanoListaV++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoV->tipoArchivo);
	eliminarPlacaTotal(infoV, listaVehiculos);
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
	datosPlacasTotales(infoV);
	printf("\nEl vehiculo ha sido eliminado del sistema\n");
}

void infoUnVehiculo(informacionVehiculos *infoV)
{
	FILE *archivo = NULL; 
	
	string listaVehiculos[100];
	infoV->tamanoListaV = 0;
	int indice = 1;
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
	printf("\n\n ");
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
				if(indice == 1)
				{
					printf("Numero de placa:        %s\n", token);
				}
				else if(indice == 2)
				{
					printf(" Marca:                 %s\n", token);
				}
				else if(indice == 3)
				{
					printf(" Modelo:                %s\n", token);
				}
				else if(indice == 4)
				{
					printf(" Anno:                  %s\n", token);
				}
				else if(indice == 5)
				{
					printf(" Color:                 %s\n", token);
				}
				else if(indice == 6)
				{
					printf(" Cilindrada:            %s\n", token);
				}
				else if(indice == 7)
				{
					printf(" Tipo de combustible:   %s\n", token);
				}
				else if(indice == 8)
				{
					printf(" Cantidad de pasajeros: %s\n", token);
				}
				else if(indice == 9)
				{
					printf(" Precio de alquiler:    %s\n", token);
				}
				else if(indice == 10)
				{
					printf(" Informacion extra:     %s\n", token);
				}
				else if(indice == 11)
				{
					printf(" Estado:                %s\n", token);
				}
				else
				{
					printf("%s\n", token);
				}
      			indice++;
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	printf("\n");
	printf("\n");
}

void mostrarVehiculosTotales(informacionVehiculos *infoV, string lista[])
{
	FILE *archivo;
	string aux; 
	string ruta;
	string info;
	int indice1 = 0;
	int indice2 = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;

	printf("Informacion de todos los vehiculos registrados: \n");
	printf("\n");
	printf("\n ");
	
	while(indice2 < infoV->tamanoPlacas)
	{
		strcpy(ruta, ".\\InfoVehiculos\\");
		strcat(ruta,lista[indice2]);
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
					printf("%s\n", token);
      				indice1++;
      				token = strtok(NULL, delimitador);
   				}
			}
			fclose(archivo);
			printf("\n\n");
		}
		indice2++;
	}	
}	

void extraerDatosPlacas(informacionVehiculos *infoV)
{
	FILE *archivo = NULL; 

	string listaPlacas[100];
	infoV->tamanoPlacas = 0;
	infoV->numeroVehiculos = 1;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoVehiculos\\Placas");
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
      			strcpy(listaPlacas[indice], token);
      			infoV->tamanoPlacas++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	mostrarVehiculosTotales(infoV, listaPlacas);
}

void lecturaDatosCliente(informacionCliente *infoC)
{	
	int numCategoria;
	printf("Ingrese su cedula: ");
	gets(infoC->numeroCedula);
	
	printf("\nIngrese su nombre completo (ambos nombres y apellidos): ");
	gets(infoC->nombreCompleto);
	
	printf("\nIngrese su fecha de nacimiento: ");
	gets(infoC->fechaNacimiento);
	
	printf("\nIngrese su correo electronico: ");
	gets(infoC->correoElectronico);
	
	printf("\nIngrese el numero correspondiente a su categoria: \n1.Bronce\n2.Plata\n3.Oro\n4.Zafiro\n");
	scanf("%d", &numCategoria);

	if(numCategoria == 1)
	{
		strcpy(infoC->categoria, "Bronce");
	}
	else if(numCategoria == 2)
	{
		strcpy(infoC->categoria, "Plata");
	}
	else if(numCategoria == 3)
	{
		strcpy(infoC->categoria, "Oro");
	}
	else
	{
		strcpy(infoC->categoria, "Zafiro");
	}
}

void creacionArchivosClientes(informacionCliente *infoC)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoClientes\\");
	
	strcat(ruta, infoC->numeroCedula);
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	fprintf(archivo,"%s; %s; %s; %s; %s;", infoC->numeroCedula, infoC->nombreCompleto, infoC->fechaNacimiento, infoC->correoElectronico, infoC->categoria);
	fclose(archivo);
}

void insercionCedNom(informacionCliente *infoC)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoClientes\\Cedulas");
	
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	fprintf(archivo,"%s - %s; ", infoC->numeroCedula, infoC->nombreCompleto);
}

void insertarDatosCliente(ListaCliente *C, informacionCliente infoC)
{
	lecturaDatosCliente(&infoC);
	Nodo *n, *aux;

	if(C->inicio2 == NULL) //Valida si la lista esta vacia
	{
			C->inicio2 = (Nodo *) malloc(sizeof(Nodo));
			C->inicio2->dato2 = infoC;
			C->inicio2->siguiente = NULL;
	}
	else
	{
		n = C->inicio2;
		while(n != NULL)
		{
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
		aux->siguiente->siguiente = NULL;
		aux->siguiente->dato2 = infoC;
	}		
	creacionArchivosClientes(&infoC);
	insercionCedNom(&infoC);
	printf("\n");
	printf("\n");
	printf("La informacion se ha registrado exitosamente");
}

void extraerListaClientes(informacionCliente *infoC, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	string nombre;
	string fechaN;
	string correo;
	string categoria;
	string espacio = " ";
	int respuesta;
	
	printf("\nQue desea modificar?\n1.Nombre\n2.Fecha de nacimiento\n3.Correo electronico\n4.Categoria\n");
	scanf("%d", &respuesta);
	getchar();
	
	if(respuesta == 1)
	{
		printf("Ingrese el nuevo nombre: ");
		gets(nombre);
		strcpy(lista[1], espacio);
		strcat(lista[1], nombre);
	}
	
	else if(respuesta == 2)
	{
		printf("Ingrese la nueva fecha de nacimiento: ");
		gets(fechaN);
		strcpy(lista[2], espacio);
		strcat(lista[2], fechaN);
	}
	else if(respuesta == 3)
	{
		printf("Ingrese el nuevo correo electronico: ");
		gets(correo);
		strcpy(lista[3], espacio);
		strcat(lista[3], correo);
	}
	else 
	{
		printf("Ingrese la nueva categoria: ");
		gets(categoria);
		strcpy(lista[4], espacio);
		strcat(lista[4], categoria);
	}
	
	string rutaAux;
	strcpy(rutaAux, ".\\InfoClientes\\");
	strcat(rutaAux,infoC->numeroCedula);
	strcpy(infoC->tipoArchivo, rutaAux);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivoAux = fopen(infoC->tipoArchivo, "a+");
	
	while(indice < infoC->tamano)
	{	
		fprintf(archivoAux,"%s;", lista[indice]);
		indice ++;
	}
	printf("\n");
	printf("La modificacion se realizo exitosamente");
	//exit(-1);
}

void modificarInfoCliente(informacionCliente *infoC)
{
	FILE *archivo = NULL; 
	
	string listaCliente[100];
	infoC->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese el numero de cedula del cliente al cual desea modificar la informacion: ");
	gets(infoC->numeroCedula);
	
	string ruta;
	strcpy(ruta, ".\\InfoClientes\\");
	strcat(ruta, infoC->numeroCedula);
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaCliente[indice], token);
      			infoC->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoC->tipoArchivo);
	extraerListaClientes(infoC, listaCliente);
}

void infoUnCliente(informacionCliente *infoC)
{	
	FILE *archivo;
	int indice = 1;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string aux; 
	string ruta;
	string cedula;
	
	printf("\nIngrese el numero de cedula del cliente al cual desea consultar la informacion: ");
	gets(cedula);
	printf("\n");
	printf("\n");
	
	strcpy(ruta, ".\\InfoClientes\\");
	strcat(ruta, cedula);
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	
	printf("La informacion del cliente seleccionado es: \n\n");
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
				if(indice == 1)
				{
					printf(" Numero de cedula:     %s\n", token);
				}
				else if(indice == 2)
				{
					printf(" Nombre completo:     %s\n", token);
				}
				else if(indice == 3)
				{
					printf(" Fecha de nacimiento: %s\n", token);
				}
				else if(indice == 4)
				{
					printf(" Correo electronico:  %s\n", token);
				}
				else if(indice == 5)
				{
					printf(" Categoria:           %s\n", token);
				}
				else
				{
					printf("%s\n", token);
				}
				indice ++;
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	printf("\n");
}

void consultaTodosC(informacionCliente *infoC)
{	
	FILE *archivo;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string aux; 
	string ruta;
	string codigo;
	
	strcpy(ruta, ".\\InfoClientes\\Cedulas");
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	printf("Clientes registrados: \n\n ");
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
				printf("%s\n", token);
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	infoUnCliente(infoC);
}

void eliminarInfoCliente(informacionCliente *infoC, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	string nombre;
	string fechaN;
	string correo;
	string categoria;
	string espacio = " ";
	int respuesta;
	
	if(strcmp(lista[infoC->tamano-1], " Alquilando") == 0)
	{
		printf("\nNo se puede hacer la eliminacion, actualmente el cliente esta alquilando un vehiculo"); 
	}

	else 
	{
		remove(infoC->tipoArchivo);
		printf("\n");
		printf("\nLa informacion del cliente ha sido eliminada\n");
	}
}

void extraerInfoC(informacionCliente *infoC)
{
	FILE *archivo = NULL; 
	
	string listaCliente[100];
	infoC->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese el numero de cedula del cliente que desea eliminar: ");
	gets(infoC->numeroCedula);
	
	string ruta;
	strcpy(ruta, ".\\InfoClientes\\");
	strcat(ruta, infoC->numeroCedula);
	strcpy(infoC->tipoArchivo, ruta);
	strcat(infoC->tipoArchivo, ".txt");
	
	archivo = fopen(infoC->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaCliente[indice], token);
      			infoC->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	eliminarInfoCliente(infoC, listaCliente);
}

//-----------------------  Devolucion de un Vehiculo --------------------------------//

void modificarEstadoVehiculo(informacionVehiculos *infoV, char placaVehiculo[10])
{
	FILE *archivo = NULL; 
	
	string listaVehiculos[100];
	infoV->tamanoListaV = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	strcpy(infoV->numeroPlaca, placaVehiculo);

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

	// --- Actualizacion del estado del vehiculo a disponible --- //
	strcpy(listaVehiculos[10], " ");
	strcat(listaVehiculos[10], DISPONIBLE);

	// --- Actualizacion de los datos del vehiculo en el archivo --- //
	string rutaAux;
	strcpy(rutaAux, ".\\InfoVehiculos\\");
	strcat(rutaAux,infoV->numeroPlaca);
	strcpy(infoV->tipoArchivo, rutaAux);
	strcat(infoV->tipoArchivo, ".txt");

	FILE *archivoAux;
	archivoAux = fopen(infoV->tipoArchivo, "a+");
	
	indice = 0;
	while(indice < infoV->tamanoListaV)
	{	
		if(indice == (infoV->tamanoListaV)-1)
		{
			fprintf(archivoAux,"%s;", listaVehiculos[indice]);
		}
		else
		{
			fprintf(archivoAux,"%s;", listaVehiculos[indice]);
		}
		indice ++;
	}
	printf("\n");
	printf("La modificacion se realizo exitosamente");

}

//Función para realizar la devolución de un vehículo
void devolucionVehiculo(){
	char cedula[9];
	char placaVehiculo[10];
	char condicionesDelVehiculo[300];

	printf("** Sistema de devolucion de vehiculos. **\nIngrese su numero de cedula para poder continuar: ");
	gets(cedula);
	printf("El numero de cedula es %s\n", cedula);

	printf("\nIngrese la placa del vehiculo que desea regresar: ");
	gets(placaVehiculo);
	printf("La placa del vehiculo es %s\n", placaVehiculo);

	printf("\nIngrese las condiciones en las que el vehiculo se esta regresando: ");
	gets(condicionesDelVehiculo);
	printf("Las condiciones son:  %s\n", condicionesDelVehiculo);

	informacionVehiculos vehiculo;
	modificarEstadoVehiculo(&vehiculo, placaVehiculo);

}

//----------------------------------------------------------------------------------//

void administrarInfoV(){
	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");
	while(activadorBucle2 == 1){
		printf("____________________________________________________________\n");
		printf("\n");
		printf("       Administrar informacion de los vehiculos             \n");
		printf("____________________________________________________________\n");
		printf(" \n");
		printf("Seleccione una de las funciones disponibles:\n");
		printf(" \n");
		printf("1-Modificar informacion\n");
		printf("2-Eliminar vehiculo registrado\n");
		printf("3-Consultar la informacion de un vehiculo\n");
		printf("4-Consultar lista de vehiculos registrados\n");
		printf("5-Regresar al menu principal\n");
		printf("\n");
		printf("\n");
		printf("La opcion selecionada es: ");
		scanf( "%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6){
		
		
			printf("La opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}
		
   		Lista *L;
		L = listaNueva();
		informacionVehiculos vehiculo;
	
		ListaCliente *C;
		C = lista2();
		informacionCliente cliente;

		switch(opcionElegidaSubmenu)
		{
			
			case 1: modificarInfoV(&vehiculo);
			break;
			case 2: eliminarVehiculo(&vehiculo);
			break;
			case 3: infoUnVehiculo(&vehiculo);
			break;
			case 4: extraerDatosPlacas(&vehiculo);
			break;
			case 5: menu(L, C, vehiculo, cliente);
			break;
		}
	}		
}

void administrarInfoC(){
	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");
	while(activadorBucle2 == 1){
		printf("____________________________________________________________\n");
		printf("\n");
		printf("       Administrar informacion de los clientes              \n");
		printf("____________________________________________________________\n");
		printf(" \n");
		printf("Seleccione una de las funciones disponibles:\n");
		printf(" \n");
		printf("1-Modificar informacion\n");
		printf("2-Eliminar informacion\n");
		printf("3-Consultar informacion\n");
		printf("4-Regresar al menu principal\n");
		printf("\n");
		printf("\n");
		printf("La opcion selecionada es: ");
		scanf( "%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6)
		{
		
		
			printf("La opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}
		
   		Lista *L;
		L = listaNueva();
		informacionVehiculos vehiculo;
	
		ListaCliente *C;
		C = lista2();
		informacionCliente cliente;

		switch(opcionElegidaSubmenu)
		{
			
			case 1: modificarInfoCliente(&cliente);
			break;
			case 2: extraerInfoC(&cliente);
			break;
			case 3: consultaTodosC(&cliente);
			break;
			case 4: menu(L, C, vehiculo, cliente);
			break;
		}
	}		
}

void menu(Lista *L, ListaCliente *C, informacionVehiculos infoV, informacionCliente infoC)
{
	int activadorBucle=1;
	int opcionElegidaPrincipal;

	
	while(activadorBucle==1)
	{
		printf("\t************************************\n\n");
		printf("\t*         RENT A CAR               *\n");     
		printf("\t*                                  *\n");         
		printf("\t*         MENU PRINCIPAL           *\n\n");
		printf("\t************************************\n");
		printf(" \n");
		printf("\tSeleccione una de las funciones disponibles:\n");
		printf(" \n");
		printf("\t1-Registrar vehiculo\n");
		printf("\t2-Administrar informacion de los vehiculos \n");
		printf("\t3-Registrar cliente\n");
		printf("\t4-Administrar informacion de los clientes\n");
		printf("\t5-Solicitar alquiler de un vehiculo\n");
		printf("\t6-Consultar solicitudes de alquileres registradas\n");
		printf("\t7-Devolver vehiculo\n");
		printf("\t8-Analisis de datos\n");
		printf("\t9-Salir\n");
		printf(" \n");
		printf(" \n");
		printf("\tLa opcion selecionada es: ");
		scanf( "%d", &opcionElegidaPrincipal);
		getchar();
		printf(" \n");
		printf(" \n");

		if((opcionElegidaPrincipal>9)|| (opcionElegidaPrincipal<1))
		{
			printf("----La opcion elegida no es valida, elija otra opcion----\n");
			printf(" \n");
			printf(" \n");
			printf(" \n");
		}
		switch(opcionElegidaPrincipal)
		{	
			case 1: insertarVehiculo(L, infoV);
			break;
			
			case 2: administrarInfoV();
			break;
			
			case 3: insertarDatosCliente(C, infoC);
			break;
			
			case 4: administrarInfoC();
			break;

			case 5: printf("Solicitar alquiler de un vehiculo");
			break;
			
			case 6: printf("Consultar solicitudes de alquileres\n");
			break;

			case 7: printf("Devolver vehiculo\n");
			break;

			case 8: printf("Analisis de datos\n");
			break;

			case 9: activadorBucle=0;
		}
	}
}

int main()
{
    Lista *L;
	L = listaNueva();
	informacionVehiculos vehiculo;
	
	ListaCliente *C;
	C = lista2();
	informacionCliente cliente;

    //insertarVehiculo(L, vehiculo);
	//modificarInfoV(&vehiculo);
	//eliminarVehiculo(&vehiculo);
	//infoUnVehiculo(&vehiculo);
	//extraerDatosPlacas(&vehiculo);
	//insertarDatosCliente(C, cliente);
	//modificarInfoCliente(&cliente);
	//consultaTodosC(&cliente);
	//extraerInfoC(&cliente);
	//menu(L, C, vehiculo, cliente);
	devolucionVehiculo();
    
    return 0;
}
