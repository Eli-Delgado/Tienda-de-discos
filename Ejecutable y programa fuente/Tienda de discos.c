#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
	int dd, mm, aaaa;
}FECHA;

typedef struct
{
	int codigo;
	char album[30];
	char artista[30];
	char genero[30];
	float precio;
	int existencia;
	int estado;
}ALMACEN;

typedef struct
{
	int folio;
	int cant_articulos;
	float total;
	int cant_ind[' '];
	float importe[' '];
	int estado[' '];
	FECHA f;
	ALMACEN al[' '];
}TICKET;

typedef struct
{
	int folio;
	char nombres[30];
	char apellidos[30];
	char calle[30];
	int numero;
	char colonia[30];
	int cp;
	TICKET ti;
}FACTURA;

///////////////
///PRINCIPAL///
///////////////
void bienvenida();
int menu_principal();

/////////////
///ALMACEN///
/////////////
void gestion_de_almacen();//Funcion de la gestion del almacen
int menu_almacen();//MENU DE ALMACEN
void extraer_almacen(ALMACEN al_temp[' ']);//EXTRAER ALMACEN
void alta_almacen();//AGREGAR AL ALMACEN
void escritura_almacen(ALMACEN al_temp[' ']);//IMPRIMIR ALMACEN
void baja_almacen();//DAR DE BAJA
void reescribir_almacen(ALMACEN al_temp[' ']);//REESCRIBIR ALMACEN
void modificar_almacen();//MODIFICACIONES
void busqueda_almacen();//BUSQUEDA

////////////
///VENTAS///
////////////
void punto_de_venta();//Funcion para el punto de venta
int menu_ventas();//Menu de ventas
int agregar_articulo(int n_ti, ALMACEN al_temp[' '], TICKET ti[1]);//Funcion para agregar articulo
int quitar_articulo(int n_ti, ALMACEN al_temp[' '], TICKET ti[1]);//Fucion para quitar articulo
int cancelar_venta(int n_ti, ALMACEN al_temp[' '], TICKET ti[1]);//Fucion para cancelar venta
int realizar_venta(int n_ti, ALMACEN al_temp[' '], TICKET ti[1]);//Funcion para realizar venta, guardar ticket y factura segun sea el caso
void guardar_ticket(TICKET ti[1]);//Funcion para guardar ticket
void guardar_factura(TICKET ti[1]);//Funcion para pedir datos de factura y guardarla

//////////////
///REPORTES///
//////////////
void reportes();
int menu_reportes();//Funcion para mostrar el menu de reportes
int eleccion_tickets();//Funcion para el menu de tickets
int eleccion_facturas();//Funcion para el menu de facturas

void extraer_tickets(TICKET ti_temp[' ']);//Funcion para extraer tickets
void imprimir_tickets(int n_tickets, TICKET ti_temp[' ']);//Funcion para imprimir tickets
void los_tickets_en_excel(int eleccion, int n_tickets, TICKET ti_temp[' ']);//Funcion para mandar todos los tickets a excel
void todos_los_tickets(TICKET ti_temp[' ']);//Funcion obtener todos los tickets
void tickets_por_dia(TICKET ti_temp[' ']);//Funcion para obtener los tickets por dia
void tickets_por_mes(TICKET ti_temp[' ']);//Funcion para obtener los tickets por mes
void ticket_individual(TICKET ti_temp[' ']);//Funcion para obtener el ticket individual

void extraer_facturas(FACTURA fa_temp[' ']);//Funcion para extraer facturas
void imprimir_facturas(int n_facturas, FACTURA fa_temp[' ']);//Funcion para imprimir facturas
void las_facturas_en_excel(int eleccion, int n_facturas, FACTURA fa_temp[' ']);//Funcion para mandar todos las facturas a excel
void todos_las_facturas(FACTURA fa_temp[' ']);//Funcion obtener todas las facturas
void facturas_por_dia(FACTURA fa_temp[' ']);//Funcion para obtener las facturas por dia
void facturas_por_mes(FACTURA fa_temp[' ']);//Funcion para obtener las facturas por mes
void factura_individual(FACTURA fa_temp[' ']);//Funcion para obtener la factura individual


void todas_las_facturas_detalladas(int n_facturas, FACTURA fa_temp[' ']);//Funcion para mandar todas las facturas detalladas a EXCEL [FUNCION AGREGADA]

/////////////
///GENERAL///
/////////////
int contador_lineas(FILE *file);//CONTADOR DE LINEAS
void rellenar(char aux[' ']);//RELLENAR DE ESPACIOS UNA PALABRA
int val_int(char aux[' ']);//VALIDADOR DE ENTEROS
float val_float(char aux[' ']);//VALIDADOR DE FLOTANTES
void pause();//Pausa
int val_fecha(int op, FECHA f[1]);//VALIDADOR DE FECHA


int main()
{
	//VARIABLES LOCALES
	int i, op_p, n_almacen, n_articulos;
	FILE *almacen;
	ALMACEN al_temp[' '];
	char aux[100];
	
	bienvenida();
	system("cls");
	do
	{
		op_p = menu_principal();
		switch(op_p)
		{
			case 1://Gestion de almacen
				system("cls");
				gestion_de_almacen();
				break;
			case 2://Ventas
				system("cls");
				almacen = fopen("almacen.txt","rt");
				n_almacen = contador_lineas(almacen) -1;
				fclose(almacen);
				if(n_almacen != 0)
				{
					n_articulos = 0;
					extraer_almacen(al_temp);
					for(i=0;i<n_almacen;i++)
					{
						n_articulos += al_temp[i].existencia;
					}
					if(n_articulos == 0)
					{
						printf("\n Los productos del almacen se han agotado o el almacen esta vacio\n\n");
						pause();
					}
					else
						punto_de_venta();
				}
				else
				{
					printf("\n El almacen esta vacio \n\n");
					pause();
				}
				break;
			case 3://Reportes
				system("cls");
				reportes();
				break;
			case 4://Salir
				do
				{
					printf("\n\n %cRealmente desea salir [1.- SI  /  2.- NO]?: ",168);
					fflush(stdin);
					gets(aux);
					op_p = val_int(aux);
					if(op_p==1)
						op_p = 4;
				}while(op_p!=4&&op_p!=2);
				break;
		}
		system("cls");
	}while(op_p!=4);
	
	system("cls");
	printf("\n\n\n\n \t\t\tFIN DEL PROGRAMA \n\n\n");
	pause();
	return 0;
}


///////////////
///PRINCIPAL///
///////////////

//Funcion de bienvenida
void bienvenida()
{
	printf("\n\n\n\n");
	printf("\n\n\t\t\t BIENVENIDO A LA TIENDA DE DISCOS\n\n\t\t\t        %c ESCUCHALO BIEN %c\n\n\n\n\n\n\n\n",34,34);
	printf(" PRESIONE UNA TECLA PARA INICIAR: ");
	getch();
}

//Funcion para el menu principal
int menu_principal()
{
	int op;
	char aux[10];
	printf("\n\t\t MENU PRINCIPAL: ");
	printf("\n\n 1.- Gestion de almacen\n 2.- Punto de Venta\n 3.- Reportes\n 4.- Salir\n");
	do
	{
		printf("\n Elija una opcion [1-4]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>4);
	return op;
}

/////////////
///ALMACEN///
/////////////

//Funcion de la gestion del almacen
void gestion_de_almacen()
{
	FILE *almacen;
	ALMACEN al, al_temp[' '];
	char aux[50];
	int op_al;
	do
	{
		//IMPRIMIR PRIMERA LINEA DE IDENTIFICACION
		almacen = fopen("almacen.txt","rt");
		if(almacen == NULL)
		{
			almacen = fopen("almacen.txt","a+t");
			fprintf(almacen,"CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           ESTADO               \n");
		}
		fclose(almacen);
		//SWITCH DE OPCIONES
		op_al = menu_almacen();
		switch(op_al)
		{
			case 1://ALTAS
				system("cls");
				alta_almacen();
				break;
			case 2://BAJAS
				system("cls");
				baja_almacen();
				break;
			case 3://MODIFICACIONES
				system("cls");
				modificar_almacen();
				break;
			case 4://BUSQUEDAS
				system("cls");
				busqueda_almacen();
				break;
			case 5://VER ALMACEN COMPLETO
				system("cls");
				extraer_almacen(al_temp);
				escritura_almacen(al_temp);
				pause();
				break;
			case 6://REGRESAR
				break;
		}
		system("cls");
	}while(op_al!=6);
}

//Menu de almacen
int menu_almacen()
{
	int op;
	char aux[10];
	printf("\n\t\t GESTION DE ALMACEN");
	printf("\n\n 1.- Altas\n 2.- Bajas\n 3.- Modificaciones\n 4.- Busqueda\n 5.- Visualizar almacen completo\n 6.- Regresar\n");
	do
	{
		printf("\n Elija una opcion [1-6]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>6);
	return op;
}

//Funcion para extraer almacen
void extraer_almacen(ALMACEN al_temp[' '])
{
	FILE *almacen;
	int i, n;
	char aux[150];
	almacen = fopen("almacen.txt","rt");
	rewind(almacen);
	n = contador_lineas(almacen) - 1;
	rewind(almacen);
	fgets(aux,148,almacen);
	fputs("\n",almacen);
	for(i=0;i<n;i++)
	{
		fgets(aux,22,almacen);
		al_temp[i].codigo = atoi(aux);
		
		fgets(al_temp[i].album,21,almacen);
		fgets(aux,2,almacen);
		
		fgets(al_temp[i].artista,21,almacen);
		fgets(aux,2,almacen);
		
		fgets(al_temp[i].genero,21,almacen);
		fgets(aux,2,almacen);
		
		fgets(aux,22,almacen);
		al_temp[i].precio = atof(aux);
		
		fgets(aux,22,almacen);
		al_temp[i].existencia = atof(aux);
		
		fgets(aux,22,almacen);
		al_temp[i].estado = atoi(aux);
		
		fputs("\n",almacen);
	}
	fclose(almacen);
}

//Funcion de entrada de discos
void alta_almacen()
{
	FILE *almacen;
	ALMACEN al_temp[' '];
	ALMACEN al;
	int n, i, op, lon;
	char aux[150];
	almacen = fopen("almacen.txt","rt");
	if(almacen == NULL)
	{
		printf(" ERROR AL ABRIR ARCHIVO");
	}
	else
	{
		n = contador_lineas(almacen) - 1;
		almacen = fopen("almacen.txt","a+t");
	}
	rewind(almacen);
	do//¿AGREGAR MAS?
	{
		almacen = fopen("almacen.txt","a+t");
		extraer_almacen(al_temp);
		do//¿CORRECTO?
		{
			printf("\n\t\t ALTA %d\n",n+1);
			do
			{
				printf("\n Codigo del producto: ");
				fflush(stdin);
				gets(aux);
				al.codigo = val_int(aux);
				//REVISAR CODIGOS REPETIDOS
				for(i=0;i<n;i++)
				{
					if(al_temp[i].codigo==al.codigo)
					{
						printf("\n El Codigo ya ha sido registrado\n");
						al.codigo=-1;
					}
				}
			}while(al.codigo<1||al.codigo>99999);
			
			do
			{
				printf("\n Nombre del album: ");
				fflush(stdin);
				gets(al.album);
				lon = strlen(al.album);
				if(lon > 20)
					printf("\n Cadena muy larga\n");
			}while(lon>20);
			
			do
			{
				printf("\n Nombre del artista / grupo: ");
				fflush(stdin);
				gets(al.artista);
				lon = strlen(al.artista);
				if(lon > 20)
					printf("\n Cadena muy larga\n");
			}while(lon>20);
			
			do
			{
				printf("\n Genero: ");
				fflush(stdin);
				gets(al.genero);
				lon = strlen(al.genero);
				if(lon > 20)
					printf("\n Cadena muy larga\n");
			}while(lon>20);
			
			do
			{
				printf("\n Precio: ");
				fflush(stdin);
				gets(aux);
				al.precio = val_float(aux);
			}while(al.precio<0||al.precio>=999);
			
			do
			{
				printf("\n Introduzca la existencia: ");
				fflush(stdin);
				gets(aux);
				al.existencia = val_int(aux);
			}while(al.existencia<0||al.existencia>999);
			
			al.estado = 1;//El estado 1 representa que esta dado de alta
			
			do
			{
				printf("\n %cLos datos son correctos [1.- SI  /  2.- NO]?: ",168);
				fflush(stdin);
				gets(aux);
				op = val_int(aux);
			}while(op!=1&&op!=2);
			if(op==2)
			{
				system("cls");
				printf("\t\t REINGRESO");
			}	
		}while(op!=1);
		do
		{
			printf("\n %cDesea agregar mas [1.- SI   /   2.- NO]?: ",168);
			scanf("%d",&op);
		}while(op!=1&&op!=2);
		system("cls");
		n++;
		//GUARDAR EN ARCHIVO
		fprintf(almacen,"%.5d                %-20s %-20s %-20s %6.2f               %.3d                  %1d                    \n",al.codigo,al.album,al.artista,al.genero,al.precio,al.existencia,al.estado);
		fclose(almacen);
	}while(op!=2);
}

//Funcion de salida de datos de almacen
void escritura_almacen(ALMACEN al_temp[' '])
{
	FILE *almacen;
	int i, n;
	almacen = fopen("almacen.txt","rt");
	rewind(almacen);
	n = contador_lineas(almacen) - 1;
	fclose(almacen);
	printf("\n\t\t\t\t\t\t ALMACEN\n\n");
	printf(" CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
	for(i=0;i<n;i++)
	{
		printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia);
	}
}

//Funcion para dar de baja del almacen
void baja_almacen()
{
	FILE *almacen;
	ALMACEN al_temp[' '];
	char aux[30];
	int baja, flag, n, i, op;
	do
	{
		printf("\n\n Introduzca el codigo del producto que desea dar de baja: ");
		fflush(stdin);
		gets(aux);
		baja = val_int(aux);
	}while(baja<0||baja>99999);
	extraer_almacen(al_temp);
	almacen = fopen("almacen.txt","rt");
	n = contador_lineas(almacen) - 1;
	fclose(almacen);
	flag = 0;
	for(i=0;i<n;i++)
	{
		if(al_temp[i].codigo == baja)
		{
			flag=1;
			baja=i;
			break;
		}
	}
	system("cls");
	if(flag==0)
		printf("\n\n El codigo no esta registrado");
	else
	{
		al_temp[baja].estado = 0;
		printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
		printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[baja].codigo,al_temp[baja].album,al_temp[baja].artista,al_temp[baja].genero,al_temp[baja].precio,al_temp[baja].existencia);
		do
		{
			printf("\n %cSeguro que desea dar de baja este producto [1.- SI  /  2.- NO]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
		}while(op!=1&&op!=2);
		if(op==1)
		{
			reescribir_almacen(al_temp);
			printf("\n\n El producto se ha dado de baja");
		}
	}
	if(op!=2)
		pause();
}

//Funcion para Reescribir archivo almacen
void reescribir_almacen(ALMACEN al_temp[' '])
{
	FILE *almacen;
	int i, n;
	almacen = fopen("almacen.txt","rt");
	rewind(almacen);
	n = contador_lineas(almacen) - 1;
	fclose(almacen);
	almacen = fopen("almacen.txt","wt");
	fprintf(almacen,"CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           ESTADO               \n");
	for(i=0;i<n;i++)
	{
		if(al_temp[i].estado == 1)
			fprintf(almacen,"%.5d                %-20s %-20s %-20s %6.2f               %.3d                  %1d                    \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia,al_temp[i].estado);
	}
	fclose(almacen);
}

//Funcion para modificar almacen
void modificar_almacen()
{
	FILE *almacen;
	ALMACEN al_temp[' '], al_aux[' '];
	char aux[30];
	int mod, flag, n, i, op, lon;
	do
	{
		printf("\n\n Introduzca el codigo del producto que desea modificar: ");
		fflush(stdin);
		gets(aux);
		mod = val_int(aux);
	}while(mod<0||mod>99999);
	extraer_almacen(al_temp);
	almacen = fopen("almacen.txt","rt");
	n = contador_lineas(almacen) - 1;
	fclose(almacen);
	flag = 0;
	for(i=0;i<n;i++)
	{
		if(al_temp[i].codigo == mod)
		{
			flag=1;
			mod=i;
			break;
		}
	}
	if(flag==0)
		printf("\n\n El codigo no esta registrado");
	else
	{
		do
		{
			system("cls");
			printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
			printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
			printf("\n\t MENU\n\n 1.- Modificar CODIGO\n 2.- Modificar Nombre del ALBUM\n 3.- Modificar Nombre del ARTISTA\n 4.- Modificar GENERO\n 5.- Modificar PRECIO\n 6.- Modificar EXISTENCIA del producto\n 7.- Regresar\n");
			do
			{
				printf("\n %cQue opcion desea [1 - 7]?: ",168);
				fflush(stdin);
				gets(aux);
				op = val_int(aux);
			}while(op<1||op>7);
			switch(op)
			{
				case 1://CODIGO
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO CODIGO\n");
					extraer_almacen(al_aux);
					do
					{
						printf("\n Codigo del producto: ");
						fflush(stdin);
						gets(aux);
						al_temp[mod].codigo = val_int(aux);
						//REVISAR CODIGOS REPETIDOS
						for(i=0;i<n;i++)
						{
							if(al_aux[i].codigo==al_temp[mod].codigo)
							{
								printf("\n El Codigo ya ha sido registrado\n");
								al_temp[mod].codigo=-1;
							}
						}
					}while(al_temp[mod].codigo<1||al_temp[mod].codigo>99999);
					printf("\n\n Se realizo la modificacion");
					break;
				case 2://NOMBRE DEL ALBUM
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO NOMBRE DEL ALBUM\n");
					do
					{
						printf("\n Nombre del album: ");
						fflush(stdin);
						gets(al_temp[mod].album);
						lon = strlen(al_temp[mod].album);
						if(lon > 20)
							printf("\n Cadena muy larga\n");
					}while(lon > 20);
					printf("\n\n Se realizo la modificacion");
					break;
				case 3://NOMBRE DEL ARTISTA
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO NOMBRE DEL ARTISTA\n");
					do
					{
						printf("\n Nombre del artista: ");
						fflush(stdin);
						gets(al_temp[mod].artista);
						lon = strlen(al_temp[mod].artista);
						if(lon > 20)
							printf("\n Cadena muy larga\n");
					}while(lon > 20);
					printf("\n\n Se realizo la modificacion");
					break;
				case 4://GENERO
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO GENERO\n");
					do
					{
						printf("\n Genero: ");
						fflush(stdin);
						gets(al_temp[mod].genero);
						lon = strlen(al_temp[mod].genero);
						if(lon > 20)
							printf("\n Cadena muy larga\n");
					}while(lon > 20);
					printf("\n\n Se realizo la modificacion");
					break;
				case 5://PRECIO
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO PRECIO\n");
					do
					{
						printf("\n Precio: ");
						fflush(stdin);
						gets(aux);
						al_temp[mod].precio = val_float(aux);
					}while(al_temp[mod].precio<0||al_temp[mod].precio>=999);
					printf("\n\n Se realizo la modificacion");
					break;
				case 6://EXISTENCIA
					system("cls");
					printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
					printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n\n",al_temp[mod].codigo,al_temp[mod].album,al_temp[mod].artista,al_temp[mod].genero,al_temp[mod].precio,al_temp[mod].existencia);
					printf("\n\n MODIFICANDO EXISTENCIA\n");
					do
					{
						printf("\n Introduzca la existencia: ");
						fflush(stdin);
						gets(aux);
						al_temp[mod].existencia = val_int(aux);
					}while(al_temp[mod].existencia<0||al_temp[mod].existencia>999);
					printf("\n\n Se realizo la modificacion");
					break;
				case 7://REGRESAR
					break;
			}
			reescribir_almacen(al_temp);
			if(op!=7)
				pause();
			system("cls");
		}while(op!=7);
	}
	if(op!=7)
		pause();
}

void busqueda_almacen()
{
	FILE *almacen;
	ALMACEN al_temp[' '];
	char aux[30];
	int bus, flag=0, n, i, op, lon;
	system("cls");
	do
	{
		printf("\n\t MENU\n\n 1.- Buscar por CODIGO\n 2.- Buscar por Nombre del ALBUM\n 3.- Buscar por Nombre del ARTISTA\n 4.- Buscar por GENERO\n 5.- Regresar\n");
		do
		{
			printf("\n %cOpcion [1 - 5]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
		}while(op<1||op>5);
		switch(op)
		{
			case 1://Por Codigo
				flag=0;
				do
				{
					printf("\n\n Introduzca el Codigo: ");
					fflush(stdin);
					gets(aux);
					bus = val_int(aux);
				}while(bus<0||bus>99999);
				extraer_almacen(al_temp);
				almacen = fopen("almacen.txt","rt");
				n = contador_lineas(almacen) - 1;
				fclose(almacen);
				system("cls");
				printf("\n COINCIDENCIAS POR CODIGO\n\n");
				printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
				for(i=0;i<n;i++)
				{
					if(bus == al_temp[i].codigo)
					{
						printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia);
						flag++;
					}
				}
				if(flag==0)
					printf("\n\n NO SE ENCONTRO COINCIDENCIA");
				break;
			case 2://Por album
				flag=0;
				do
				{
					printf("\n Introduzca el Nombre del album: ");
					fflush(stdin);
					gets(aux);
					lon = strlen(aux);
					if(lon > 20)
						printf("\n Cadena muy larga\n");
				}while(lon > 20);
				rellenar(aux);
				extraer_almacen(al_temp);
				almacen = fopen("almacen.txt","rt");
				n = contador_lineas(almacen) - 1;
				fclose(almacen);
				system("cls");
				printf("\n COINCIDENCIAS POR NOMBRE DEL ALBUM\n\n");
				printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
				for(i=0;i<n;i++)
				{
					if((strcmpi(aux,al_temp[i].album))==0)
					{
						printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia);
						flag++;
					}
				}
				if(flag==0)
					printf("\n\n NO SE ENCONTRO COINCIDENCIA");
				break;	
			case 3://Por artista
				flag=0;
				do
				{
					printf("\n Introduzca el Nombre del artista: ");
					fflush(stdin);
					gets(aux);
					lon = strlen(aux);
					if(lon > 20)
						printf("\n Cadena muy larga\n");
				}while(lon > 20);
				rellenar(aux);
				extraer_almacen(al_temp);
				almacen = fopen("almacen.txt","rt");
				n = contador_lineas(almacen) - 1;
				fclose(almacen);
				system("cls");	
				printf("\n COINCIDENCIAS POR NOMBRE DEL ARTISTA\n\n");
				printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
				for(i=0;i<n;i++)
				{
					if((strcmpi(aux,al_temp[i].artista))==0)
					{
						printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia);
						flag++;
					}
				}
				if(flag==0)
					printf("\n\n NO SE ENCONTRO COINCIDENCIA");
				break;
			case 4://Por genero	
			flag=0;
				do
				{
					printf("\n Introduzca el Genero: ");
					fflush(stdin);
					gets(aux);
					lon = strlen(aux);
					if(lon > 20)
						printf("\n Cadena muy larga\n");
				}while(lon > 20);
				rellenar(aux);
				extraer_almacen(al_temp);
				almacen = fopen("almacen.txt","rt");
				n = contador_lineas(almacen) - 1;
				fclose(almacen);
				system("cls");
				printf("\n COINCIDENCIAS POR GENERO\n\n");
				printf("\n CODIGO               ALBUM                ARTISTA              GENERO               PRECIO               EXISTENCIA           \n\n");
				for(i=0;i<n;i++)
				{
					if((strcmpi(aux,al_temp[i].genero))==0)
					{
						printf(" %.5d                %-20s %-20s %-20s %6.2f               %.3d                  \n",al_temp[i].codigo,al_temp[i].album,al_temp[i].artista,al_temp[i].genero,al_temp[i].precio,al_temp[i].existencia);
						flag++;
					}
				}
				if(flag==0)
					printf("\n\n NO SE ENCONTRO COINCIDENCIA");
				break;
			case 5:
				break;
		}
		if(op!=5)
			pause();
		system("cls");
	}while(op!=5);
}

////////////
///VENTAS///
////////////

void punto_de_venta()
{
	FILE *tickets, *facturas;
	ALMACEN al_temp[' '];
	TICKET ti[1];
	char aux[10];
	int op_ve, i, n_ti = 0, n_tickets;
	float total;
	//FECHA LOCAL
	time_t fecha;
	struct tm *fecha_local;
	time(&fecha);
	fecha_local = localtime(&fecha);
	ti[0].f.dd = fecha_local->tm_mday;
	ti[0].f.mm = fecha_local->tm_mon + 1;
	ti[0].f.aaaa = fecha_local->tm_year + 1900;
	
	//ABRIR ARCHIVO tickets_sin_formato.txt para crear y contar lineas
	tickets = fopen("tickets_sin_formato.txt","rt");
	if(tickets == NULL)//SI no existe imprime linea de identificacion.
	{
		tickets = fopen("tickets_sin_formato.txt","a+t");
		fprintf(tickets,"TICKETS SIN FORMATO \n");
		fclose(tickets);
		tickets = fopen("tickets_sin_formato.txt","rt");
	}	
	n_tickets = contador_lineas(tickets) -1;//n_ticket (cuantos tickets hay en el archivo) tambien representa el folio del ticket.
	fclose(tickets);
	ti[0].folio = n_tickets + 1;
	
	//ABRIR ARCHIVO facturas_sin_formato.txt para crear
	facturas = fopen("facturas_sin_formato.txt","rt");
	if(facturas == NULL)//SI no existe imprime linea de identificacion.
	{
		facturas = fopen("facturas_sin_formato.txt","a+t");
		fprintf(facturas,"FACTURAS SIN FORMATO \n");
		fclose(facturas);
	}	
	fclose(facturas);
	
	
//	printf("\n %d", n_tickets);
	
	extraer_almacen(al_temp);
	do
	{
		total = 0;
		for(i=0;i<n_ti;i++)
		{
			if(ti[0].estado[i]!=0)
				total = total + ti[0].importe[i];
		}
		ti[0].total = total;
		//IR MOSTRANDO PANTALLA DE VENTA
		printf("\n\t\t\t PUNTO DE VENTA\n\n");
		printf(" FOLIO: %.5d                                  FECHA:     %.2d / %.2d / %.4d\n",ti[0].folio,ti[0].f.dd,ti[0].f.mm,ti[0].f.aaaa);
		printf("\n CODIGO     CANTIDAD   DESCRIPCION          PRECIO UNITARIO      IMPORTE             \n");
		for(i=0;i<n_ti;i++)
		{
			printf("\n %.5d      %.2d         %s %-6.2f               %-8.2f            ",ti[0].al[i].codigo,ti[0].cant_ind[i],ti[0].al[i].album,ti[0].al[i].precio,ti[0].importe[i]);
		}
		printf("\n\n                                                          TOTAL: %8.2f ",ti[0].total);
		op_ve = menu_ventas();
		switch(op_ve)
		{
			case 1://Agregar articulo
				n_ti = agregar_articulo(n_ti, al_temp, ti);
				break;
			case 2://Quitar articulo
				n_ti = quitar_articulo(n_ti, al_temp, ti);
				break;
			case 3://Cancelar venta
				n_ti = cancelar_venta(n_ti, al_temp, ti);
				break;
			case 4:
				ti[0].cant_articulos = n_ti;
				ti[0].folio = realizar_venta(n_ti, al_temp, ti);
				n_ti=0;
				break;
			case 5://Regresar salir
				if(n_ti != 0)
				{
					printf("\n Primero debe realizar la venta o cancelarla");
					op_ve = 1;
					pause();
				}
				break;
		}
		system("cls");
	}while(op_ve!=5);
}

//Menu de ventas
int menu_ventas()
{
	int op;
	char aux[10];
//	printf("\n\n 1.- Agregar articulo\n\n 2.- Quitar articulo\n\n 3.- Cancelar venta\n\n 4.- Realizar venta\n\n 5.- Regresar/salir\n");
	printf("\n\n\n 1.- Agregar articulo\n 2.- Quitar articulo\n 3.- Cancelar venta\n 4.- Realizar venta\n 5.- Regresar\n");
	do
	{
		printf("\n Elija una opcion [1-5]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>5);
	return op;	
}

//Funcion para agregar articulo
int agregar_articulo(int n_ti, ALMACEN al_temp[' '], TICKET ti[1])
{
	FILE *almacen;
	char aux[10];
	int i, n_al, op, flag, copia;
	almacen = fopen("almacen.txt","rt");
	n_al = contador_lineas(almacen) - 1;
	fclose(almacen);
	do
	{
		printf("\n Introduzca CODIGO del articulo: ");
		fflush(stdin);
		gets(aux);
		ti[0].al[n_ti].codigo = val_int(aux);
		//REVISAR CODIGOS EXISTENTES
		for(i=0;i<n_al;i++)
		{
			if(al_temp[i].codigo == ti[0].al[n_ti].codigo)
			{
				if(al_temp[i].existencia > 0)
				{
					copia=i;//GUARDO EL SUBINDICE
					flag=1;
					break;	
				}
				else
				{
					printf("\n Producto agotado\n");
					flag=2;
					break;
				}
			}
			else
				flag=0;
		}
		if(flag == 0)
		{
			printf("\n Codigo sin coincidencia\n");
			ti[0].al[n_ti].codigo = -1;
		}
		if(flag == 2)
			ti[0].al[n_ti].codigo = -1;
	}while(ti[0].al[n_ti].codigo<1||ti[0].al[n_ti].codigo>99999);
	
	ti[0].al[n_ti] = al_temp[copia];
	
	//PEDIR Y COMPARAR CANTIDAD 
	do
	{
		printf("\n Introduzca la CANTIDAD: ");
		fflush(stdin);
		gets(aux);
		ti[0].cant_ind[n_ti] = val_int(aux);
		if(ti[0].cant_ind[n_ti] > al_temp[copia].existencia)
		{
			printf("\n Solo hay %d en existencia \n",al_temp[copia].existencia);
			ti[0].cant_ind[n_ti] = -1;
		}
	}while(ti[0].cant_ind[n_ti]<=0||ti[0].cant_ind[n_ti]>999);
	
	al_temp[copia].existencia = al_temp[copia].existencia - ti[0].cant_ind[n_ti];
		
	ti[0].importe[n_ti] = ti[0].cant_ind[n_ti] * ti[0].al[n_ti].precio;
	
	ti[0].estado[n_ti]=1;
	
	system("cls");
	n_ti++;
	return n_ti;
}

//Fucion para quitar articulo
int quitar_articulo(int n_ti, ALMACEN al_temp[' '], TICKET ti[1])
{
	FILE *almacen;
	char aux[10];
	int i, j, n_al, op, flag, recuperar, eliminar, codigo_aux;
	TICKET ti_aux;
	
	almacen = fopen("almacen.txt","rt");
	n_al = contador_lineas(almacen) - 1;
	fclose(almacen);
	
	if(n_ti != 0)
	{
		do//Pido el codigo
		{
			printf("\n Introduzca CODIGO del articulo a quitar: ");
			fflush(stdin);
			gets(aux);
			codigo_aux = val_int(aux);
			//REVISAR CODIGOS EXISTENTES el la pantalla
			for(i=0;i<n_ti;i++)
			{
				if(codigo_aux == ti[0].al[i].codigo)
				{
					eliminar = i;
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if(flag == 0)
			{
				printf("\n Aun no ha ingresado este articulo.\n");
				pause();
				return n_ti;
			}
		}while(codigo_aux<1||codigo_aux>99999);
		
		do
		{
			printf("\n %cRealmente desea QUITAR este articulo [1.- SI  /  2.- NO]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
		}while(op!=1 && op!=2);
		
		//Proceso de eliminar
		if(op==1)
		{
			//Busco el producto del almacen
			for(i=0;i<n_al;i++)
			{
				if(ti[0].al[eliminar].codigo == al_temp[i].codigo)
					recuperar = i;
			}
			//Asigno estado 0 al ti[0].estado[eliminar]
			ti[0].estado[eliminar] = 0;
			//Regreso los articulos al almacen
			al_temp[recuperar].existencia = al_temp[recuperar].existencia + ti[0].cant_ind[eliminar];
			//Recorro el articulo al final
			for(i=0;i<n_ti-1;i++)
			{
				for(j=i;j<n_ti;j++)
				{
					if(ti[0].estado[i] < ti[0].estado[j])
					{
						ti_aux.cant_ind[0] = ti[0].cant_ind[i];
						ti_aux.estado[0] = ti[0].estado[i];
						ti_aux.importe[0] = ti[0].importe[i];
						ti_aux.al[0] = ti[0].al[i];
						
						ti[0].cant_ind[i] = ti[0].cant_ind[j];
						ti[0].estado[i] = ti[0].estado[j];
						ti[0].importe[i] = ti[0].importe[j];
						ti[0].al[i] = ti[0].al[j];
						
						ti[0].cant_ind[j] = ti[0].cant_ind[i];
						ti[0].estado[j] = ti[0].estado[i];
						ti[0].importe[j] = ti[0].importe[i];
						ti[0].al[j] = ti[0].al[i];
					}
				}
			}
			//Quito uno a los que estan en la pantalla, como se recorrio al final, no se tomará en cuenta.
			n_ti = n_ti -1;
		}
	}
	else
	{
		printf("\n Aun no hay ningun producto agregado");
		pause();
	}
	
	return n_ti;
}

//Funcion para cancelar venta.
int cancelar_venta(int n_ti, ALMACEN al_temp[' '], TICKET ti[1])
{
	FILE *almacen;
	char aux[10];
	int op, i, j, n_al;
	
	almacen = fopen("almacen.txt","rt");
	n_al = contador_lineas(almacen) - 1;
	fclose(almacen);
	
	if(n_ti != 0)
		do
		{
			printf("\n %cRealmente desea CANCELAR VENTA [1.- SI  /  2.- NO]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
			if(op==1)
			{
				//REGRESAR ARTICULOS AL ALMACEN 
				for(i=0;i<n_al;i++)
				{
					for(j=0;j<n_ti;j++)
					{
						if(ti[0].al[j].codigo == al_temp[i].codigo)
						{
							al_temp[i].existencia = al_temp[i].existencia + ti[0].cant_ind[j];
						}
					}
				}
				n_ti=0;//Reinicio de ticket
			}
		}while(op!=1&&op!=2);
	else
	{
		printf("\n Aun no hay ningun producto agregado");
		pause();
	}
	
	return n_ti;
}

//Funcion para realizar venta, guardar ticket y factura segun sea el caso
int realizar_venta(int n_ti, ALMACEN al_temp[' '], TICKET ti[1])
{
	float total;
	int i, op;
	char aux[10];
	if(n_ti != 0)
	{
		system("cls");
		total = 0;
		for(i=0;i<n_ti;i++)
		{
			if(ti[0].estado[i]!=0)
				total = total + ti[0].importe[i];
		}
		ti[0].total = total;
		printf("\n\t\t\t TICKET DE COMPRA\n\n");
		printf(" FOLIO: %.5d                       FECHA:     %.2d / %.2d / %.4d\n",ti[0].folio,ti[0].f.dd,ti[0].f.mm,ti[0].f.aaaa);
		printf("\n CANTIDAD   DESCRIPCION          PRECIO UNITARIO      IMPORTE             \n");
		for(i=0;i<n_ti;i++)
		{
			printf("\n %.2d         %s %-6.2f               %-8.2f            ",ti[0].cant_ind[i],ti[0].al[i].album,ti[0].al[i].precio,ti[0].importe[i]);
		}
		printf("\n\n\n\n                                              TOTAL: %8.2f ",ti[0].total);
		printf("\n\n\n\n %cEs importante que conserve su folio de ticket para futuras consultas!\n\n",173);
		//Reescribir almacen, de restando los productos que se ventiron
		reescribir_almacen(al_temp);
		
		guardar_ticket(ti);
		do
		{
			printf("\n %cDesea facturar [1.- SI  /  2.- NO]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
		}while(op!=1 && op!=2);
		if(op==1)
		{
			guardar_factura(ti);
		}
	}
	else
	{
		printf("\n Aun no hay ningun producto agregado");
		pause();
	}
	return ti[0].folio+1;
}

//Funcion para guardar ticket.
void guardar_ticket(TICKET ti[1])
{
	FILE *tickets;
	char aux[50];
	int i;
	tickets = fopen("tickets_sin_formato.txt","a+t");
	
	fprintf(tickets,"%.5d      %8.2f   %.2d    %.2d    %.4d  %.2d    ",ti[0].folio,ti[0].total,ti[0].f.dd,ti[0].f.mm,ti[0].f.aaaa,ti[0].cant_articulos);
	for(i=0;i<ti[0].cant_articulos;i++)
	{
		fprintf(tickets,"%.2d    %-20s %6.2f     %8.2f   ",ti[0].cant_ind[i],ti[0].al[i].album,ti[0].al[i].precio,ti[0].importe[i]);
	}
	fprintf(tickets,"\n");
	fclose(tickets);
}

//Funcion para pedir datos de factura y guardarla
void guardar_factura(TICKET ti[1])
{
	FILE *facturas;
	FACTURA fa[1];
	int lon, i, op;
	char aux[50];
	system("cls");
	
	facturas = fopen("facturas_sin_formato.txt","rt");
	fa[0].folio = contador_lineas(facturas);
	fclose(facturas);
	
	do
	{
		printf("\n\t Datos del cliente:\n\n");
		do
		{
			printf("\n Nombres: ");
			fflush(stdin);
			gets(fa[0].nombres);
			lon = strlen(fa[0].nombres);
			if(lon > 20)
				printf("\n Cadena muy larga\n");
		}while(lon>20);
		
		do
		{
			printf("\n Apellidos: ");
			fflush(stdin);
			gets(fa[0].apellidos);
			lon = strlen(fa[0].apellidos);
			if(lon > 20)
				printf("\n Cadena muy larga\n");
		}while(lon>20);
		
		printf("\n Direccion del cliente \n");
		
		do
		{
			printf("\n Calle: ");
			fflush(stdin);
			gets(fa[0].calle);
			lon = strlen(fa[0].calle);
			if(lon > 20)
				printf("\n Cadena muy larga\n");
		}while(lon>20);
		
		do
		{
			printf("\n Numero: ");
			fflush(stdin);
			gets(aux);
			fa[0].numero = val_int(aux);
		}while(fa[0].numero<0||fa[0].numero>99999);
		
		do
		{
			printf("\n Colonia: ");
			fflush(stdin);
			gets(fa[0].colonia);
			lon = strlen(fa[0].colonia);
			if(lon > 20)
				printf("\n Cadena muy larga\n");
		}while(lon>20);
		
		do
		{
			printf("\n Codigo Postal: ");
			fflush(stdin);
			gets(aux);
			fa[0].cp = val_int(aux);
		}while(fa[0].cp<10000||fa[0].cp>99999);
		
		fa[0].ti = ti[0];
		
		do
		{
			printf("\n %cLos datos son correctos [1.- SI  /  2.- NO]?: ",168);
			fflush(stdin);
			gets(aux);
			op = val_int(aux);
		}while(op!=1&&op!=2);
		if(op==2)
		{
			system("cls");
			printf("\t\t REINGRESO");
		}
	}while(op==2);
	
	
	//GUARDAR FACURA
	
	facturas = fopen("facturas_sin_formato.txt","a+t");
	
	fprintf(facturas,"%.5d      %-20s %-20s %-20s %.5d      %-20s %.5d      %8.2f   %.2d    %.2d    %.4d  %.2d    ",fa[0].folio,fa[0].nombres,fa[0].apellidos,fa[0].calle,fa[0].numero,fa[0].colonia,fa[0].cp,fa[0].ti.total,fa[0].ti.f.dd,fa[0].ti.f.mm,fa[0].ti.f.aaaa,fa[0].ti.cant_articulos);
	for(i=0;i<fa[0].ti.cant_articulos;i++)
	{
		fprintf(facturas,"%.2d    %-20s %6.2f     %8.2f   ",fa[0].ti.cant_ind[i],fa[0].ti.al[i].album,fa[0].ti.al[i].precio,fa[0].ti.importe[i]);
	}
	fprintf(facturas,"\n");
	
	system("cls");
	
	printf("\n\t\t\t FACTURA\n\n");
	printf(" FOLIO: %.5d                       FECHA:     %.2d / %.2d / %.4d\n",fa[0].folio,fa[0].ti.f.dd,fa[0].ti.f.mm,fa[0].ti.f.aaaa);
	
	printf("\n Datos del cliente:");
	printf("\n Nombres: %s \n Apellidos: %s \n Direccion:\n Calle: %s No. %.5d\n Colonia: %s\n C.P: %.5d\n",fa[0].nombres,fa[0].apellidos,fa[0].calle,fa[0].numero,fa[0].colonia,fa[0].cp);
	
	printf("\n CANTIDAD   DESCRIPCION          PRECIO UNITARIO      IMPORTE             \n");
	for(i=0;i<fa[0].ti.cant_articulos;i++)
	{
		printf("\n %.2d         %s %-6.2f               %-8.2f            ",fa[0].ti.cant_ind[i],fa[0].ti.al[i].album,fa[0].ti.al[i].precio,fa[0].ti.importe[i]);
	}
	printf("\n\n\n\n                                              TOTAL: %8.2f ",fa[0].ti.total);
	printf("\n\n\n\n %cEs importante que conserve su folio de factura para futuras consultas!\n\n",173);
	pause();
	fclose(facturas);
}

//////////////
///REPORTES///
//////////////

void reportes()
{
	FILE *tickets, *facturas;
	TICKET ti_temp[' '];
	FACTURA fa_temp[' '];
	char aux[10];
	int op_re;
	
	extraer_tickets(ti_temp);
	extraer_facturas(fa_temp);
		
	do
	{
		op_re = menu_reportes();
		switch(op_re)
		{
			case 1://VENTAS TICKETS
				do
				{
					system("cls");
					op_re = eleccion_tickets();
					//eleccion_tickets();
					switch(op_re)
					{
						extraer_tickets(ti_temp);
						case 1://TODOS
							todos_los_tickets(ti_temp);
							break;
						case 2://POR DIA
							tickets_por_dia(ti_temp);
							break;
						case 3://POR MES
							tickets_por_mes(ti_temp);
							break;
						case 4://INDIVIDUAL
							ticket_individual(ti_temp);
							break;
						case 5://REGRESAR
							break;
					}
				}while(op_re!=5);
				op_re = 1;
				break;
			case 2://FACTURAS
				do
				{
					system("cls");
					op_re = eleccion_facturas();
					switch(op_re)
					{
						extraer_facturas(fa_temp);
						case 1://TODOS
							todos_las_facturas(fa_temp);
							break;
						case 2://POR DIA
							facturas_por_dia(fa_temp);
							break;
						case 3://POR MES
							facturas_por_mes(fa_temp);
							break;
						case 4://INDIVIDUAL
							factura_individual(fa_temp);
							break;
						case 5://REGRESAR
							break;
					}
				}while(op_re!=5);
				op_re = 1;
				break;
			case 3://Regresar 
				break;
		}
		system("cls");
	}while(op_re!=3);
}

//Funcion para mostrar el menu de reportes
int menu_reportes()
{
	int op;
	char aux[10];
	printf("\n\t REPORTES \n\n 1.- Reportes de Ventas (tickets)\n 2.- Reportes de Facturas\n 3.- Regresar\n");
	do
	{
		printf("\n Elija una opcion [1-3]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>3);
	return op;
}

//Funcion para el menu de tickets
int eleccion_tickets()
{
	int op;
	char aux[10];
	printf("\n\t REPORTES DE VENTAS (TICKETS) \n\n 1.- Reporte de TODAS las ventas (tickets)\n 2.- Reporte por DIA\n 3.- Reporte por MES \n 4.- Ticket INDIVIDUAL\n 5.- Regresar\n");
	do
	{
		printf("\n Elija una opcion [1-5]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>5);
	return op;
}

//Funcion para el menu de facturas
int eleccion_facturas()
{
	int op;
	char aux[10];
	printf("\n\t REPORTES DE FACTURAS \n\n 1.- Reporte de TODAS las FACTURAS\n 2.- Reporte por DIA\n 3.- Reporte por MES \n 4.- Factura INDIVIDUAL\n 5.- Regresar\n");
	do
	{
		printf("\n Elija una opcion [1-5]: ");
		fflush(stdin);
		gets(aux);
		op = val_int(aux);
	}while(op<1||op>5);
	return op;
}

//Funcion para extraer tickets
void extraer_tickets(TICKET ti_temp[' '])
{
	FILE *tickets;
	int i, j, n_tickets;
	char aux[150];
	tickets = fopen("tickets_sin_formato.txt","rt");
	rewind(tickets);
	n_tickets = contador_lineas(tickets) - 1;
	rewind(tickets);
	fgets(aux,21,tickets);
	fputs("\n",tickets);
	for(i=0;i<n_tickets;i++)
	{
		fgets(aux,12,tickets);
		ti_temp[i].folio = atoi(aux);
		
		fgets(aux,12,tickets);
		ti_temp[i].total = atof(aux);
		
		fgets(aux,7,tickets);
		ti_temp[i].f.dd = atoi(aux);
		
		fgets(aux,7,tickets);
		ti_temp[i].f.mm = atoi(aux);
		
		fgets(aux,7,tickets);
		ti_temp[i].f.aaaa = atoi(aux);
		
		fgets(aux,7,tickets);
		ti_temp[i].cant_articulos = atoi(aux);
		
		for(j=0;j<ti_temp[i].cant_articulos;j++)
		{
			fgets(aux,7,tickets);
			ti_temp[i].cant_ind[j] = atoi(aux);
			
			fgets(ti_temp[i].al[j].album,21,tickets);
			fgets(aux,2,tickets);
			
			fgets(aux,12,tickets);
			ti_temp[i].al[j].precio = atof(aux);
			
			fgets(aux,12,tickets);
			ti_temp[i].importe[j] = atof(aux);
			
		}
		
		fputs("\n",tickets);
	}
	fclose(tickets);
}

//Funcion para imprimir tickets
void imprimir_tickets(int n_tickets, TICKET ti_temp[' '])
{
	int i;
	float total_tickets = 0;
	char aux[150];
	
	printf(" FOLIO      FECHA          TOTAL      \n\n");
	for(i=0;i<n_tickets;i++)
	{
		printf(" %.5d      %.2d/%.2d/%.4d     %-8.2f   \n",ti_temp[i].folio,ti_temp[i].f.dd,ti_temp[i].f.mm,ti_temp[i].f.aaaa,ti_temp[i].total);	
		total_tickets = total_tickets + ti_temp[i].total;
	}
	printf("\n\n          TOTAL TICKETS: %8.2f",total_tickets);
}

//Funcion para mandar todos los tickets a excel
void los_tickets_en_excel(int eleccion, int n_tickets, TICKET ti_temp[' '])
{
	FILE *tickets;
	int i;
	float total_tickets;
	char tipo[3][50]={"reportes\\todos_los_tickets_en_excel.xls", "reportes\\los_tickets_en_excel_por_dia.xls", "reportes\\los_tickets_en_excel_por_mes.xls"};
	char estilo[3][20]={"todas","dia","mes"};
	tickets = fopen(tipo[eleccion],"wt");
	fprintf(tickets,"\nTICKETS (%s)\n\n",estilo[eleccion]);
	fprintf(tickets," FOLIO      \tFECHA          \tTOTAL      \n\n");
	for(i=0;i<n_tickets;i++)
	{
		fprintf(tickets," %.5d      \t%.2d/%.2d/%.4d     \t%-8.2f   \n",ti_temp[i].folio,ti_temp[i].f.dd,ti_temp[i].f.mm,ti_temp[i].f.aaaa,ti_temp[i].total);	
		total_tickets = total_tickets + ti_temp[i].total;
	}
	fprintf(tickets,"\n\nTOTAL: \t %8.2f",total_tickets);
	fclose(tickets);
}

//Funcion para obtener todos los tickets
void todos_los_tickets(TICKET ti_temp[' '])
{
	FILE *tickets;
	int n_tickets;
	system("cls");					
	tickets = fopen("tickets_sin_formato.txt","rt");
	n_tickets = contador_lineas(tickets) - 1;
	fclose(tickets);
	printf("\n\t TODOS LOS TICKETS\n\n");
	imprimir_tickets(n_tickets, ti_temp);
	los_tickets_en_excel(0,n_tickets, ti_temp);
	pause();
	
}

//Funcion para obtener los tickets por dia
void tickets_por_dia(TICKET ti_temp[' '])
{
	FILE *tickets;
	TICKET ti_dia[' '];
	FECHA f[1];
	int dia = 0, x, i, n_tickets;
	system("cls");
	tickets = fopen("tickets_sin_formato.txt","rt");
	n_tickets = contador_lineas(tickets) - 1;
	fclose(tickets);
	
	printf("\n Introduzca la fecha de las ventas (tickets): \n");
	do
	{
		x = val_fecha(0,f);
		if(x==-1)
			printf("\n Fecha incorrecta, reingrese: \n");
	}while(x==-1);
	
	
	for(i=0;i<n_tickets;i++)
	{
		if((f[0].dd == ti_temp[i].f.dd) && (f[0].mm == ti_temp[i].f.mm) && (f[0].aaaa == ti_temp[i].f.aaaa))
		{
			ti_dia[dia] = ti_temp[i];
			dia++;
		}
	}
	if(dia>0)
	{
		system("cls");
		printf("\n\t VENTAS (TICKETS) POR DIA\n\n");
		imprimir_tickets(dia, ti_dia);
		los_tickets_en_excel(1,dia, ti_dia);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en la fecha");
		pause();
	}
}

//Funcion para obtener los tickets por mes
void tickets_por_mes(TICKET ti_temp[' '])
{
	FILE *tickets;
	TICKET ti_mes[' '];
	FECHA f[1];
	int mes = 0, x, i, n_tickets;
	system("cls");
	tickets = fopen("tickets_sin_formato.txt","rt");
	n_tickets = contador_lineas(tickets) - 1;
	fclose(tickets);
	
	printf("\n Introduzca la fecha de las ventas (tickets): \n");
	do
	{
		x = val_fecha(1,f);
		if(x==-1)
			printf("\n Fecha incorrecta, reingrese: \n");
	}while(x==-1);
	
	
	for(i=0;i<n_tickets;i++)
	{
		if((f[0].mm == ti_temp[i].f.mm) && (f[0].aaaa == ti_temp[i].f.aaaa))
		{
			ti_mes[mes] = ti_temp[i];
			mes++;
		}
	}
	if(mes>0)
	{
		system("cls");
		printf("\n\t VENTAS (TICKETS) POR MES\n\n");
		imprimir_tickets(mes, ti_mes);
		los_tickets_en_excel(2,mes, ti_mes);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en la fecha");
		pause();
	}
}

//Funcion para obtener el ticket individual
void ticket_individual(TICKET ti_temp[' '])
{
	FILE *tickets;
	TICKET ti_ind;
	int  i, n_tickets, flag = 0;
	char aux[20];
	int folio;
	system("cls");
	tickets = fopen("tickets_sin_formato.txt","rt");
	n_tickets = contador_lineas(tickets) - 1;
	fclose(tickets);
	
	do
	{
		printf("\n Introduzca el folio del ticket: ");
		fflush(stdin);
		gets(aux);
		folio = val_int(aux);
	}while(folio<1||folio>99999);
	system("cls");
	for(i=0;i<n_tickets;i++)
	{
		if(ti_temp[i].folio == folio)
		{
			ti_ind = ti_temp[i];
			flag++;
		}
	}
	if(flag!=0)
	{
		//MOSTRAR TICKET EN PANTALLA
		printf("\n\t\t TICKET INDIVIDUAL\n");
		printf("\n FOLIO: %.5d                       FECHA:     %.2d / %.2d / %.4d \n",ti_ind.folio,ti_ind.f.dd,ti_ind.f.mm,ti_ind.f.aaaa);
		printf("\n CANTIDAD   DESCRIPCION          PRECIO UNITARIO      IMPORTE             \n");
		for(i=0;i<ti_ind.cant_articulos;i++)
		{
			printf("\n %.2d         %s %6.2f               %-8.2f            ",ti_ind.cant_ind[i],ti_ind.al[i].album,ti_ind.al[i].precio,ti_ind.importe[i]);
		}
		printf("\n\n\n\n                                              TOTAL: \t%.2f ",ti_ind.total);
		
		//MANDAR TICKET A EXCEL
		tickets = fopen("reportes\\ticket_individual.xls","wt");
		fprintf(tickets,"TICKET INDIVIDUAL\n");
		fprintf(tickets,"\n FOLIO: \t%.5d                       \t\tFECHA:     \t%.2d/%.2d/%.4d\n",ti_ind.folio,ti_ind.f.dd,ti_ind.f.mm,ti_ind.f.aaaa);
		fprintf(tickets,"\n CANTIDAD   \tDESCRIPCION          \t\tPRECIO UNITARIO      \tIMPORTE             \n");
		for(i=0;i<ti_ind.cant_articulos;i++)
		{
			fprintf(tickets,"\n %.2d         \t%s \t\t%6.2f               \t%8.2f            ",ti_ind.cant_ind[i],ti_ind.al[i].album,ti_ind.al[i].precio,ti_ind.importe[i]);
		}
		fprintf(tickets,"\n\nTOTAL: \t%.2f ",ti_ind.total);
		fclose(tickets);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en el Folio");
		pause();
	}	
}

//Funcion para extraer facturas
void extraer_facturas(FACTURA fa_temp[' '])
{
	FILE *facturas;
	int i, j, n_facturas;
	char aux[150];
	facturas = fopen("facturas_sin_formato.txt","rt");
	rewind(facturas);
	n_facturas = contador_lineas(facturas) - 1;
	rewind(facturas);
	fgets(aux,22,facturas);
	fputs("\n",facturas);
	for(i=0;i<n_facturas;i++)
	{
		fgets(aux,12,facturas);
		fa_temp[i].folio = atoi(aux);
		
		fgets(fa_temp[i].nombres,21,facturas);
		fgets(aux,2,facturas);
		
		fgets(fa_temp[i].apellidos,21,facturas);
		fgets(aux,2,facturas);
		
		fgets(fa_temp[i].calle,21,facturas);
		fgets(aux,2,facturas);
		
		fgets(aux,12,facturas);
		fa_temp[i].numero = atoi(aux);
		
		fgets(fa_temp[i].colonia,21,facturas);
		fgets(aux,2,facturas);
		
		fgets(aux,12,facturas);
		fa_temp[i].cp = atoi(aux);
		
		fgets(aux,12,facturas);
		fa_temp[i].ti.total = atof(aux);
		
		fgets(aux,7,facturas);
		fa_temp[i].ti.f.dd = atoi(aux);
		
		fgets(aux,7,facturas);
		fa_temp[i].ti.f.mm = atoi(aux);
		
		fgets(aux,7,facturas);
		fa_temp[i].ti.f.aaaa = atoi(aux);
		
		fgets(aux,7,facturas);
		fa_temp[i].ti.cant_articulos = atoi(aux);
		
		
		for(j=0;j<fa_temp[i].ti.cant_articulos;j++)
		{
			fgets(aux,7,facturas);
			fa_temp[i].ti.cant_ind[j] = atoi(aux);
			
			fgets(fa_temp[i].ti.al[j].album,21,facturas);
			fgets(aux,2,facturas);
			
			fgets(aux,12,facturas);
			fa_temp[i].ti.al[j].precio = atof(aux);
			
			fgets(aux,12,facturas);
			fa_temp[i].ti.importe[j] = atof(aux);
			
		}
		
		fputs("\n",facturas);
	}
	fclose(facturas);
}

//Funcion para imprimir facturas
void imprimir_facturas(int n_facturas, FACTURA fa_temp[' '])
{
	int i;
	float total_facturas = 0;
	char aux[150];
	
	printf(" FOLIO      CLIENTE                                   FECHA          TOTAL      \n\n");
	for(i=0;i<n_facturas;i++)
	{
		printf(" %.5d      %s %s %.2d/%.2d/%.4d     %-8.2f   \n",fa_temp[i].folio,fa_temp[i].nombres,fa_temp[i].apellidos,fa_temp[i].ti.f.dd,fa_temp[i].ti.f.mm,fa_temp[i].ti.f.aaaa,fa_temp[i].ti.total);	
		total_facturas = total_facturas + fa_temp[i].ti.total;
	}
	printf("\n\n                                                    TOTAL FACTURAS: %8.2f",total_facturas);
}

//Funcion para mandar todos las facturas a excel
void las_facturas_en_excel(int eleccion, int n_facturas, FACTURA fa_temp[' '])
{
	FILE *facturas;
	int i;
	float total_facturas;
	char tipo[3][50]={"reportes\\todas_las_facturas_en_excel.xls", "reportes\\las_facturas_en_excel_por_dia.xls", "reportes\\las_facturas_en_excel_por_mes.xls"};
	char estilo[3][20]={"todas","dia","mes"};
	facturas = fopen(tipo[eleccion],"wt");
	fprintf(facturas,"\nFACTURAS \t(%s)\n\n",estilo[eleccion]);
	fprintf(facturas," FOLIO      \tCLIENTE                                   \t\t\t\tFECHA          \tTOTAL      \n\n");
	for(i=0;i<n_facturas;i++)
	{
		fprintf(facturas," %.5d      \t%s \t\t%s \t\t%.2d/%.2d/%.4d     \t%-8.2f   \n",fa_temp[i].folio,fa_temp[i].nombres,fa_temp[i].apellidos,fa_temp[i].ti.f.dd,fa_temp[i].ti.f.mm,fa_temp[i].ti.f.aaaa,fa_temp[i].ti.total);	
		total_facturas = total_facturas + fa_temp[i].ti.total;
	}
	fprintf(facturas,"\n\nTOTAL: \t%8.2f",total_facturas);
	fclose(facturas);
}

//Funcion obtener todas las factura
void todos_las_facturas(FACTURA fa_temp[' '])
{
	FILE *facturas;
	int n_facturas;
	system("cls");
	facturas = fopen("facturas_sin_formato.txt","rt");
	n_facturas = contador_lineas(facturas) - 1;
	fclose(facturas);
	printf("\n\t\t TODAS LAS FACTURAS\n\n");
	imprimir_facturas(n_facturas, fa_temp);
	
	las_facturas_en_excel(0,n_facturas, fa_temp);
	
	todas_las_facturas_detalladas(n_facturas, fa_temp);
	printf("\n\n Las facturas mas detalladas se encuentran en la carpeta reportes bajo el nombre todas_las_facturas_detalladas");
	pause();	
}

//Funcion para obtener los facturas por dia
void facturas_por_dia(FACTURA fa_temp[' '])
{
	FILE *facturas;
	FACTURA fa_dia[' '];
	FECHA f[1];
	int dia = 0, x, i, n_facturas;
	system("cls");
	facturas = fopen("facturas_sin_formato.txt","rt");
	n_facturas = contador_lineas(facturas) - 1;
	fclose(facturas);
	
	printf("\n Introduzca la fecha de las facturas: \n");
	do
	{
		x = val_fecha(0,f);
		if(x==-1)
			printf("\n Fecha incorrecta, reingrese: \n");
	}while(x==-1);
	
	
	for(i=0;i<n_facturas;i++)
	{
		if((f[0].dd == fa_temp[i].ti.f.dd) && (f[0].mm == fa_temp[i].ti.f.mm) && (f[0].aaaa == fa_temp[i].ti.f.aaaa))
		{
			fa_dia[dia] = fa_temp[i];
			dia++;
		}
	}
	if(dia>0)
	{
		system("cls");
		printf("\n\t FACTURAS POR MES\n\n");
		imprimir_facturas(dia, fa_dia);
		las_facturas_en_excel(1,dia, fa_dia);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en la fecha");
		pause();
	}
}

//Funcion para obtener los tickets por mes
void facturas_por_mes(FACTURA fa_temp[' '])
{
	FILE *facturas;
	FACTURA fa_mes[' '];
	FECHA f[1];
	int mes = 0, x, i, n_facturas;
	system("cls");
	facturas = fopen("facturas_sin_formato.txt","rt");
	n_facturas = contador_lineas(facturas) - 1;
	fclose(facturas);
	
	printf("\n Introduzca la fecha de las ventas (tickets): \n");
	do
	{
		x = val_fecha(1,f);
		if(x==-1)
			printf("\n Fecha incorrecta, reingrese: \n");
	}while(x==-1);
	
	
	for(i=0;i<n_facturas;i++)
	{
		if((f[0].mm == fa_temp[i].ti.f.mm) && (f[0].aaaa == fa_temp[i].ti.f.aaaa))
		{
			fa_mes[mes] = fa_temp[i];
			mes++;
		}
	}
	if(mes>0)
	{
		system("cls");
		printf("\n\t FACTURAS POR MES\n\n");
		imprimir_facturas(mes, fa_mes);
		las_facturas_en_excel(2,mes, fa_mes);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en la fecha");
		pause();
	}
}

//Funcion para obtener la factura individual
void factura_individual(FACTURA fa_temp[' '])
{
	FILE *facturas;
	FACTURA fa_ind;
	int i, n_facturas, flag = 0;
	char aux[20];
	int folio;
	system("cls");
	facturas = fopen("facturas_sin_formato.txt","rt");
	n_facturas = contador_lineas(facturas) - 1;
	fclose(facturas);
	
	do
	{
		printf("\n Introduzca el folio de la factura: ");
		fflush(stdin);
		gets(aux);
		folio = val_int(aux);
	}while(folio<1||folio>99999);
	system("cls");
	for(i=0;i<n_facturas;i++)
	{
		if(fa_temp[i].folio == folio)
		{
			fa_ind = fa_temp[i];
			flag++;
		}
	}
	if(flag!=0)
	{
		//MOSTRAR FACTURA EN PANTALLA
		printf("\n\t\t\t FACTURA INDIVIDUAL\n\n");
		printf(" FOLIO: %.5d                       FECHA:     %.2d / %.2d / %.4d\n",fa_ind.folio,fa_ind.ti.f.dd,fa_ind.ti.f.mm,fa_ind.ti.f.aaaa);
	
		printf("\n Datos del cliente:");
		printf("\n Nombres: %s \n Apellidos: %s \n Direccion:\n Calle: %s No. %.5d\n Colonia: %s\n C.P: %.5d\n",fa_ind.nombres,fa_ind.apellidos,fa_ind.calle,fa_ind.numero,fa_ind.colonia,fa_ind.cp);
	
		printf("\n CANTIDAD   DESCRIPCION          PRECIO UNITARIO      IMPORTE             \n");
		for(i=0;i<fa_ind.ti.cant_articulos;i++)
		{
			printf("\n %.2d         %s %-6.2f               %-8.2f            ",fa_ind.ti.cant_ind[i],fa_ind.ti.al[i].album,fa_ind.ti.al[i].precio,fa_ind.ti.importe[i]);
		}
		printf("\n\n\n\n                                              TOTAL: %8.2f ",fa_ind.ti.total);
		
		//MANDAR FACTURA A EXCEL
		facturas = fopen("reportes\\factura_individual.xls","wt");
		fprintf(facturas,"\n FACTURA INDIVIDUAL\n\n");
		fprintf(facturas," FOLIO: \t%.5d                       \t\tFECHA:     \t%.2d/%.2d/%.4d\n",fa_ind.folio,fa_ind.ti.f.dd,fa_ind.ti.f.mm,fa_ind.ti.f.aaaa);
	
		fprintf(facturas,"\n Datos del cliente:");
		fprintf(facturas,"\n Nombres: \t%s \n Apellidos: \t%s \n Direccion:\n Calle: \t%s \t\tNo. \t%.5d\n Colonia: \t%s\n C.P: \t%.5d\n",fa_ind.nombres,fa_ind.apellidos,fa_ind.calle,fa_ind.numero,fa_ind.colonia,fa_ind.cp);
	
		fprintf(facturas,"\n CANTIDAD   \tDESCRIPCION          \t\tPRECIO UNITARIO      \tIMPORTE             \n");
		for(i=0;i<fa_ind.ti.cant_articulos;i++)
		{
			fprintf(facturas,"\n %.2d         \t%s \t\t%-6.2f               \t%-8.2f            ",fa_ind.ti.cant_ind[i],fa_ind.ti.al[i].album,fa_ind.ti.al[i].precio,fa_ind.ti.importe[i]);
		}
		fprintf(facturas,"\n\n\n\nTOTAL: \t%8.2f ",fa_ind.ti.total);
		fclose(facturas);
		pause();
	}
	else
	{
		printf("\n No se encontro coincidencia en el Folio");
		pause();
	}	
	
}

//Funcion para mandar todas las facturas detalladas a EXCEL 
void todas_las_facturas_detalladas(int n_facturas, FACTURA fa_temp[' '])
{
	FILE *facturas;
	int i, j;
	facturas = fopen("reportes\\todas_las_facturas_detalladas.xls","wt");
	
	fprintf(facturas,"\n TODAS LAS FACTURAS DETALLADAS \n");
	
	
	
	for(i=0;i<n_facturas;i++)
	{
		fprintf(facturas," \n\nFOLIO: \t%.5d                       \t\tFECHA:     \t%.2d/%.2d/%.4d\n",fa_temp[i].folio,fa_temp[i].ti.f.dd,fa_temp[i].ti.f.mm,fa_temp[i].ti.f.aaaa);
		fprintf(facturas,"\n Datos del cliente:");
		fprintf(facturas,"\n Nombres: \t%s \n Apellidos: \t%s \n Direccion:\n Calle: \t%s \t\tNo. \t%.5d\n Colonia: \t%s\n C.P: \t%.5d\n",fa_temp[i].nombres,fa_temp[i].apellidos,fa_temp[i].calle,fa_temp[i].numero,fa_temp[i].colonia,fa_temp[i].cp);
	
		fprintf(facturas,"\n CANTIDAD   \tDESCRIPCION          \t\tPRECIO UNITARIO      \tIMPORTE             \n");
		for(j=0;j<fa_temp[i].ti.cant_articulos;j++)
		{
			fprintf(facturas,"\n %.2d         \t%s \t\t%-6.2f               \t%-8.2f            ",fa_temp[i].ti.cant_ind[j],fa_temp[i].ti.al[j].album,fa_temp[i].ti.al[j].precio,fa_temp[i].ti.importe[j]);
		}
		fprintf(facturas,"\n\nTOTAL: \t%8.2f \n\n\n",fa_temp[i].ti.total);
		fprintf(facturas,"====================================================================\n");
		
	}
	fclose(facturas);
}


/////////////
///GENERAL///
/////////////

//Funcion para contar lineas de archivo.
int contador_lineas(FILE *file)
{
	int n=0;
	char c;
	while((c = fgetc(file)) != EOF)
	{
		if(c == '\n')
			n++;
	}
	return n;
}

//FUNCION PARA RELLENAR PARABRA CON ESPACIOS
void rellenar(char aux[' '])
{
	int lon, i, n;
	lon = strlen(aux);
	for(i=lon;i<20;i++)
	{
		aux[i]=' ';
	}
}

//Funcion para validar enteros
int val_int(char aux[' '])
{
	int i, n, lon, flag=1;
	lon=strlen(aux);
	for(i=0;i<lon;i++)
	{
		if(isdigit(aux[i]))
			flag=1;
		else
			flag=0;
		if(flag==0)
			break;
	}
	if (lon==0)
		flag=0;
	if(flag==1)
		n=atoi(aux);
	else if(flag==0)
		n=-1;
	return n;
}

//Funcion para validar flotantes
float val_float(char aux[' '])
{
	int i, lon, flag, punto=0;
	float n;
	lon=strlen(aux);
	for(i=0;i<lon;i++)
	{
		if(isdigit(aux[i])||aux[i]=='.')
		{
			flag=1;
			if(aux[i]=='.')
				punto++;
		}
		else
			flag=0;
		if(flag==0||punto>1)
		{
			flag=0;
			break;
		}
	}
	if(lon==0)
		flag==0;
	if(flag==1)
		n=atof(aux);
	else if(flag==0)
		n=-1;
	return n;
}

//Funcion de pausa
void pause()
{
	printf("\n\n Presiones una tecla para continuar: ");
	getch();
	fflush(stdin);
}

//Funcion para validar fecha
int val_fecha(int op, FECHA f[1])
{
	char aux[10];
	int x = 0;
	if(op==0)
	{
		do
		{
			printf("\n dd: ");
			fflush(stdin);
			gets(aux);
			f[0].dd = val_int(aux);
		}while(f[0].dd<1||f[0].dd>31);
	}
	else
		f[0].dd = 1;
	do
	{
		printf("\n mm: ");
		fflush(stdin);
		gets(aux);
		f[0].mm = val_int(aux);
	}while(f[0].mm<1||f[0].mm>12);
	do
	{
		printf("\n aaaa: ");
		fflush(stdin);
		gets(aux);
		f[0].aaaa = val_int(aux);
	}while(f[0].aaaa<1);
	switch(f[0].mm)
	{
		case 4: case 6: case 9: case 11:
			if(f[0].dd>30)
				x = -1;
			break;
		case 2:
			if(f[0].dd <=28)
				x=0;
			else
			{
				if(f[0].dd==29 && (f[0].aaaa%4 == 0 && f[0].aaaa%400 == 0))
					x = 0;
				else
					x= -1;
			}
			if(f[0].dd > 29)
				x = -1;
			break;			
	}
	return x;	
}
