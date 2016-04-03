 /***********************************************************************************\
 * 																					 *
 * Sistema de gestion de inventario y orden de compras de la farmacia Mamma Mía      *
 * Proyecto de la asignatura Algoritmos I del Instituto Universitario "Jesús Obrero" *
 * Pretende poner en práctica el uso de archivos secuenciales en C					 *	
 * 																					 *
 * 																					 *
 \***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXNOMBRE 20	//Define el numero maximo de caracteres para el nombre de un producto
#define MAXNUMPRODUCT 5

// se define el tipo de variable compleja que modela las caracteristicas que posee cada producto
typedef struct{		
	//int i_codProduct;				// codigo del producto
	char s_Nomb[MAXNOMBRE];	// nombre del producto
	float f_Cost;			// precio del producto
	int i_VentDia;	//cantidad de items vendidos del producto en el día
	int i_Venttot; //cantidad total de items vendidos del producto
	int i_Stock;// contidad restante de items del producto
	
} TipoProducto;


TipoProducto arr_producto[MAXNUMPRODUCT]; // El indice del vector corresponde al codigo del producto comenzando este en 1
int i_maxProductLeido; // indica el numero maximo ee productos leidos

int leerArchivo ();
int leerArchivoVentas();
void mostrarInventario();
void ordenCompra();
void llenarArchivo();
void imprimirOrden();
void esperaEnter();

int main()
{
	//int i_codProduct;
	int i_listaMenu;
	int i_salida = 0;
	enum listMenu { llenar_archivo = 1, cargar_archivo , mostrar_inventario, mostrar_ventas_dia, generar_orden, salir};
//	TipoProducto arr_producto[MAXNUMPRODUCT]; // El indice del vector corresponde al codigo del producto comenzando este en 1
//	leerArchivo();
	system("clear");
	printf("bienvenido..........\n");
	do{			
		printf("1) llenar archivo de inventario manualmente.\n");
		printf("2) cargar archivo de inventario\n");
		printf("3) mostrar inventario\n");
		printf("4) mostrar ventas del dia\n");
		printf("5) generar orden de compra\n");
		printf("6) salir\n");
		printf("seleccione una opcion: ");
		scanf("%d",&i_listaMenu);
		switch (i_listaMenu){
			case llenar_archivo: //llenar archivo de inventario manualmente
				llenarArchivo();
				break;
			case cargar_archivo: //cargar archivo de inventario
				leerArchivo();
				break;
			case mostrar_inventario: //muestra el archivo de inventario
				mostrarInventario();
				break;
			case mostrar_ventas_dia: //muestra las ventas leidas en el día
				leerArchivoVentas();
				break;
			case generar_orden: //generar la orden de compras
				ordenCompra();
				break;
			case salir:
				i_salida = 1;
				break;
			default:
				printf("Ha introducido una opción inválida\n");
				printf("Intentelo nuevamente\n\n\n");
				break;
		}
		system("clear");
	}while(!i_salida);
	
	printf("\n\nGracias por utilizar nuestro sistema...\n\n\n");

	
	return 0;
}

// Funcion para llenar el archivo de inventario manualmente
void llenarArchivo(){
	system("clear");
	printf("Esta funcion no está disponible en la versión actual del sistema...\n\n\n");
	esperaEnter();// funcion para esperar que el usuario presione enter
}

// Funcion para leer el archivo de datos con informacion de los productos
int leerArchivo () //retorna la cantidad de productos leidos
{	
	int i_codProduct; //indica el codigo del producto

	
	// Se crea el buffer para la lectura del archivo que contiene la informacion de productos ( codigo,nombre,preciounit )
	FILE *archivoInfo;
	
	// Se abre el archivo co informacion de productos y se deposita en el buffer correspondiente
	archivoInfo = fopen("/home/sams/Documents/Informatica/C_programming/workspace_CODELITE/proyecto/farmacia_MammaMia/infoproductos.txt","r");
	
	// Se verifica que el archivo se haya abierto con exito, de lo contrario se informa que no existe u ocurrio un error
	if (archivoInfo == NULL){
		printf("error en la lectura del archivo de informacion de productos");
	}else{
		//lectura del archivo y llenado del vector
		i_codProduct = 1;	
		system("clear");
		do{
			printf(" cargado producto codigo %d ... \n",i_codProduct);
			fscanf(archivoInfo," %s %f %d",arr_producto[i_codProduct].s_Nomb,&arr_producto[i_codProduct].f_Cost,&arr_producto[i_codProduct].i_Stock);
			i_codProduct++;
			
			//se verifica que la lectura de productos del archivo no excedan el espacio del vector donde se van a almacenar los valores
			if (i_codProduct < MAXNUMPRODUCT){
				i_maxProductLeido = i_codProduct;				
			}else {break;}
			
		}while((!feof(archivoInfo)) || (i_codProduct == MAXNUMPRODUCT-1));
		
		fclose(archivoInfo);// cierra el archivo de texto
		esperaEnter();// funcion para esperar que el usuario presione enter

	}
	return 0;
}
	

// Funcion para leer el archivo de registro de ventas
int leerArchivoVentas(){
	
	int i_codProduct;
	int i_ventaAux;
	// Se crea el buffer para la lectura del archivo que contiene los registros de las ventas
	FILE *archivoVentas;
	// Se abre el archivo de registros de ventas y se deposita en el buffer correspondiente
	archivoVentas = fopen("/home/sams/Documents/Informatica/C_programming/workspace_CODELITE/proyecto/farmacia_MammaMia/registrVentas.txt","r");
	
	if (archivoVentas == NULL){
		printf("error en la lectura del registro de ventas");
	}else{
		printf("leyendo archivo de registro de ventas \n");
		//i_codProduct = 1;
		do{
			fscanf(archivoVentas,"%d,%d",&i_codProduct,&i_ventaAux);
			arr_producto[i_codProduct].i_VentDia = arr_producto[i_codProduct].i_VentDia + i_ventaAux;
			printf("se registro venta del articulo codigo %d por una cantidad de %d \n",i_codProduct,arr_producto[i_codProduct].i_VentDia);
		}while(!feof(archivoVentas));
		fclose(archivoVentas);
	}
	for( i_codProduct = 1; i_codProduct <= MAXNUMPRODUCT; i_codProduct++){
	printf(" producto: codigo %d  descripcion %10s cantidad de ventas %d\n",i_codProduct,arr_producto[i_codProduct].s_Nomb,
																			arr_producto[i_codProduct].i_VentDia);
		
	}
	
	esperaEnter();
	
	return 0;
}	


// Funcion que muestra el inventario por pantalla para que el usuario pueda visualizar lo que imprimira al archivo
void mostrarInventario()
{
	int i_codProduct;
	for( i_codProduct = 1; i_codProduct <= i_maxProductLeido; i_codProduct++){
		printf(" producto: codigo %d descripcion %15s precio es %3.2f  ventas totales %d stock %d\n",i_codProduct,
																									arr_producto[i_codProduct].s_Nomb,
																									arr_producto[i_codProduct].f_Cost,
																									arr_producto[i_codProduct].i_Venttot,
																									arr_producto[i_codProduct].i_Stock);
	}
	
	esperaEnter();// funcion para esperar que el usuario presione enter
	
}


// Procedimiento que genera el archivo de orden de compras
void ordenCompra()
{
	int generarCompra;
	enum generarOrden { generOrden = 1, noGenerOrden};
	
	system("clear");
	imprimirOrden();
	printf("\n\ndesea generar archivo de orden de compra?\n\n");
	printf("1) Si\n.");
	printf("2) No.\n\n");
	scanf("%d",&generarCompra);
	switch (generarCompra){
		case generOrden:
			system("clear");
			printf("GENERANDO ARCHIVO....\n\n\n");
			esperaEnter();
			break;
		case noGenerOrden:
			break;
	}
}

void imprimirOrden()
{
	int i_codProduct;
	float f_presupuestado = 0;
	int i_cantProductos = 0;
	
	printf("Farmacia MAMMA MÍA C.A.\n");
	printf("Esquina de Salas Edif. Turimiquire, PB.");
	printf("\t\t\t\t Listado de productos a comprar.\n");
	printf("Codigo del Producto \t Nombre del Producto \t Precio Unitario \t Cantidad a pedir \t Bs presupuestado\n");
	for( i_codProduct = 1; i_codProduct < i_maxProductLeido; i_codProduct++){
		if ( arr_producto[i_codProduct].i_VentDia != 0){
			printf("\t %d \t\t\t %s \t %3.2f \t\t %d \t\t %5.2f \n",i_codProduct,
															arr_producto[i_codProduct].s_Nomb,
															arr_producto[i_codProduct].f_Cost,
															arr_producto[i_codProduct].i_VentDia,
															arr_producto[i_codProduct].i_VentDia * arr_producto[i_codProduct].f_Cost);
			i_cantProductos = i_cantProductos + 1;
			f_presupuestado = f_presupuestado + (arr_producto[i_codProduct].i_VentDia * arr_producto[i_codProduct].f_Cost);
		}
	}
	printf("\n\n Totales: \n\t cantidad de productos %d, \t presupuesto:  %5.2f \n\n\n", i_cantProductos, f_presupuestado);
	
	esperaEnter();
	
}

void esperaEnter()
{
	printf("Presione enter para continuar");
	getchar(); while(getchar() != '\n'); //linea para detener el sistema y esperar que el usuario teclee enter
	system("clear");
}