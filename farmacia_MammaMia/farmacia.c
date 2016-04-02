 /***********************************************************************************\
 * 																					 *
 * Sistema de gestion de inventario y orden de compras de la farmacia Mamma Mía      *
 * Proyecto de la asignatura Algoritmos I del Instituto Universitario "Jesús Obrero" *
 * Pretende poner en práctica el uso de archivos secuenciales en C					 *	
 * 																					 *
 * 																					 *
 \***********************************************************************************/

#include <stdio.h>

#define MAXNOMBRE 20	//Define el numero maximo de caracteres para el nombre de un producto
#define MAXNUMPRODUCT 5

// se define el tipo de variable compleja que modela las caracteristicas que posee cada producto
typedef struct{		
	//int i_codProduct;				// codigo del producto
	char s_Nomb[MAXNOMBRE];	// nombre del producto
	float f_Cost;			// precio del producto
	int i_Vent;	//cantidad de items vendidos del producto
	int i_Stock;// contidad restante de items del producto
	
} TipoProducto;


TipoProducto arr_producto[MAXNUMPRODUCT]; // El indice del vector corresponde al codigo del producto comenzando este en 1

int leerArchivo ();
int leerArchivoVentas();
void mostrarInventario();
void ordenCompra();
		

int main()
{
	int i_codProduct;
	int i_maxProductLeido;
	int i_listaMenu;
	int i_salida = 0;
	enum listMenu { llenar_archivo = 1, cargar_archivo , mostrar_inventario, mostrar_ventas_dia, generar_orden, salir};
//	TipoProducto arr_producto[MAXNUMPRODUCT]; // El indice del vector corresponde al codigo del producto comenzando este en 1
//	leerArchivo();
	do{
		printf("bienvenido..........\n");
		printf("1) llenar archivo de inventario manualmente.\n");
		printf("2) cargar archivo de inventario\n");
		printf("3) mostrar inventario\n");
		printf("4) mostrar ventas del dia\n");
		printf("5) generar orden de compra\n");
		printf("6) salir\n");
		printf("seleccione una op	cion: ");
		scanf("%d",&i_listaMenu);
		switch (i_listaMenu){
			case llenar_archivo: //llenar archivo de inventario manualmente
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
				break;
			case salir:
				i_salida = 1;
				break;
		}
	}while(!i_salida);
	
	printf("\n\ngracias por utilizar nuestro sistema...\n\n\n");
	/*for( i_codProduct = 1; i_codProduct <= i_maxProductLeido; i_codProduct++){
		printf(" producto: codigo %d descripcion %15s precio es %3.2f\n",i_codProduct,arr_producto[i_codProduct].s_Nomb,
																					arr_producto[i_codProduct].f_Cost);
	}*/	
	
	return 0;
}


// Funcion para leer el archivo de datos con informacion de los productos
int leerArchivo () //retorna la cantidad de productos leidos
{	
	int i_codProduct; //indica el codigo del producto
	int i_maxProductLeido; // indica el numero maximo ee productos leidos
	
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
		do{
			printf("leyendo archivo de informacion, producto %d \n",i_codProduct);
			fscanf(archivoInfo," %s %f",arr_producto[i_codProduct].s_Nomb,&arr_producto[i_codProduct].f_Cost);
			i_codProduct++;
			
			//se verifica que la lectura de productos del archivo no excedan el espacio del vector donde se van a almacenar los valores
			if (i_codProduct < MAXNUMPRODUCT){
				i_maxProductLeido = i_codProduct;				
			}else {break;}
			
		}while((!feof(archivoInfo)) || (i_codProduct == MAXNUMPRODUCT-1));
		
		fclose(archivoInfo);
				
	}
	return i_maxProductLeido;
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
			arr_producto[i_codProduct].i_Vent = arr_producto[i_codProduct].i_Vent + i_ventaAux;
			printf("se registro venta del articulo codigo %d por una cantidad de %d \n",i_codProduct,arr_producto[i_codProduct].i_Vent);
		}while(!feof(archivoVentas));
		fclose(archivoVentas);
	}
	for( i_codProduct = 1; i_codProduct <= MAXNUMPRODUCT; i_codProduct++){
	printf(" producto: codigo %d  descripcion %10s cantidad de ventas %d\n",i_codProduct,arr_producto[i_codProduct].s_Nomb,
																					arr_producto[i_codProduct].i_Vent);
		
	}
	
	return 0;
}	


// Funcion que muestra el inventario por pantalla para que el usuario pueda visualizar lo que imprimira al archivo
void mostrarInventario()
{
	
	
	
	
}


// Procedimiento que genera el archivo de orden de compras
void ordenCompra()
{
	int generarOrden;
	enum generarOrden { generOrden = 1, noGenerOrden};
	printf("desea generar orden de compra?");
	scanf("%d",&generarCompra);
	switch (generarOrden)
}