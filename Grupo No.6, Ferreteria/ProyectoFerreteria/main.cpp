#include <iostream>
#include "cConn.h"
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdlib>
#include <ctime>

using namespace std;
//Menu Usuarios
void Menu_Usuario(){
	
	//Variables
	int opcion, q_estado;
	srand(time(0));
    //Estructuras
	struct Ventas{
		int ID_Articulo_Venta;
		int ID_Transaccion_Venta= rand() % 999 + 1;
		int Cantidad_Venta;
		int Precio_Articulo_Venta ;
		int Precio_Total_Venta ;
		char Nombre_Articulo_Venta [50];
		char Fecha_Venta [50];
	}venta;	
	
	//Menu Bienvenida
	
	
	do{
		//Menu Bienvenida
		system("cls");
		cout<<" \n**Bienvenido a Ferreteria**\n";
		cout<<" 1.Comprar Productos"<<endl;
		cout<<" 2.Salir"<<endl;
		cout<<" Elija su opcion: ";
		cin>>opcion;
		//Switch opciones
		switch(opcion){
			//case compras productos
			case 1:
				{	
					system("cls");
				    MYSQL *con = mysql_init(NULL);

				    if (con == NULL) {
				        fprintf(stderr, "Error al inicializar la conexión\n", mysql_error(con));
				        exit(1);
				    }
				
				    if (mysql_real_connect(con, "localhost","root","root","ferreteria",3306,NULL,0) == NULL) {
				        fprintf(stderr, "Error al conectar a la base de datos\n", mysql_error(con));
				        exit(1);
				    }
					//Mostrar los articulos disponibles
					//Sentencia para seleccionar los artiuclos disponibles
					if (mysql_query(con, "SELECT ID_Articulos, Nombre_Articulo, Cantidad_Articulo, Precio_Articulo FROM Articulos")) {
			        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
			        exit(1);
				    }
				
				    MYSQL_RES *resultado = mysql_store_result(con);
				    if (resultado == NULL) {
				        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
				        exit(1);
				    }
				
				    int num_columnas = mysql_num_fields(resultado);
				
				    MYSQL_ROW fila;
				    cout<<" Articulos Disponibles: "<<endl;
				    while ((fila = mysql_fetch_row(resultado))) {
				        printf(" ID: %s, Nombre: %s, ", fila[0], fila[1]);
				
				        int cantidad = atoi(fila[2]);
				        if (cantidad < 1) {
				            printf("Cantidad: No hay existencias\n");
				        } else {
				            printf("Cantidad: %s, Precio: %s\n", fila[2], fila[3]);
				        }
				    }
				
				    mysql_free_result(resultado);
				    
				    //Solicitar al usuario los datos de la compra
					cout<<"\n";
				    printf(" Ingrese el ID del articulo: ");
				    scanf("%d", &venta.ID_Articulo_Venta);
				
				    /*printf(" Ingrese numero de factura: ");
				    scanf("%d", &venta.ID_Transaccion_Venta);*/
				    
				    cout<<" Numero de factura: "<<venta.ID_Transaccion_Venta<<endl;
				    				
				    printf(" Ingrese la cantidad que quiere comprar : ");
				    scanf("%d", &venta.Cantidad_Venta);
				
				    printf(" Ingrese el precio del articulo: ");
				    scanf("%d", &venta.Precio_Articulo_Venta);
					
					//Calcular el precio total
				    venta.Precio_Total_Venta = venta.Cantidad_Venta * venta.Precio_Articulo_Venta;
				    cout<<" Precio total Gastado: "<<venta.Precio_Total_Venta<<endl;
				    
				    printf(" Ingrese el nombre del articulo: ");
				    scanf("%s", &venta.Nombre_Articulo_Venta);
				
				    printf(" Ingrese la fecha de venta: ");
				    scanf("%s", &venta.Fecha_Venta);
				
				    
				
				    //Insertar los datos en la tabla compras
				    char consulta1[500];
				    //Sentencia para insertar las ventas
				    sprintf(consulta1, "INSERT INTO Compras (ID_Articulo_Venta, ID_Transaccion_Venta, Cantidad_Venta , Precio_Articulo_Venta, Precio_Total_Venta, Nombre_Articulo_Venta, Fecha_Venta) VALUES (%d, %d, %d, %d, %d, '%s', '%s')",venta.ID_Articulo_Venta, venta.ID_Transaccion_Venta, venta.Cantidad_Venta, venta.Precio_Articulo_Venta, venta.Precio_Total_Venta, venta.Nombre_Articulo_Venta, venta.Fecha_Venta);
				
				    if (mysql_query(con, consulta1)) {
				        fprintf(stderr, "Error al ejecutar la consulta\n", mysql_error(con));
				        exit(1);
				    }
				
				    //Restar la cantidad de venta al campo cantidad_compra de la tabla Articulos
				    char consulta2[200];
				    //Setenecia actualizar inventario
				    sprintf(consulta2, "UPDATE Articulos SET Cantidad_Articulo  = Cantidad_Articulo  - %d WHERE ID_Articulos = %d",venta.Cantidad_Venta, venta.ID_Articulo_Venta);
				
				    if (mysql_query(con, consulta2)) {
				        fprintf(stderr, "Error al ejecutar la consulta\n", mysql_error(con));
				        exit(1);
				    }
				
				    printf("Compra Realizada correcamente\n");
					system("pause 	");
				    mysql_close(con);
				}
			break;
			case 2: 
				cout<<" Saliendo del programa...."<<endl;
			break;	
		};
	}while(opcion!=2);
		        
		    
}
//Menu para reportes
void menu_reportes() {
	//Variables
	char MES[20];
	char YEAR[20];
	char ID[20];
	char N1[20];
	char N2[20];
	MYSQL_RES *res;
	MYSQL_ROW  row;
	MYSQL   *objDatos;
	int opcion;
	do {
			//Menu Reportes
		   	system("cls");
		    cout << "\n REPORTES\n";
		    cout << " 1. Planilla Laboral\n";
		    cout << " 2. Compras\n";
		    cout << " 3. Ventas\n";
		    cout << " 4. Kardex\n";
		    cout << " 5. Salir\n";
		    cout << " Elija una opcion del menu reportes : ";
		    cin >> opcion;
		    //Switch opciones
		    switch(opcion) {
		    	//Case planilla Laboral
		        			case 1:
				        			{
				            		//Variables
				            			int opcion2;
				           			//Menu para buscar
				            			do{
											system("cls");
											cout << "\n Buscar por: \n";
											cout << " 1. Mes\n";
											cout << " 2. Año\n";
											cout << " 3. Salir\n";
											cout << " Elija una opcion: ";
											cin >> opcion2;
											//Switch Opciones
				            				switch(opcion2){
				            									//Case buscar por mes
				            									case 1:
				            											{
				            												system("cls");
				            												//Variables
											            					char *consulta;
																			int ResulConsulta=0;
																			//Consulta Buscar
																			char sentencia[] =  "SELECT * FROM Personal WHERE Fecha_Incorporacion_mes=\'%s\'";
																			cout << "\n";
																			cout<<" Ingrese el mes: ";
																			cin>>MES;
																			consulta = new char[strlen(sentencia)+strlen(MES)];
																		   	sprintf(consulta, sentencia, MES);
															
											   								// Intentar iniciar MySQL:
																		  	if(!(objDatos = mysql_init(0))) {
																		     	 // Imposible conectar
																		    	cout << "imposible conectar." << endl;
																		  	}	
																		   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
																			    mysql_query(objDatos, consulta);
																			    res = mysql_store_result(objDatos);
																			    ResulConsulta = mysql_num_rows(res);
																			   	if(ResulConsulta>0){
																			      	while (row = mysql_fetch_row(res)){
																				      	cout << "\n";
																				    	cout << " Id Personal: " << row[0] << endl;
																					   	cout << " Nombre Personal: " << row[1] << endl;
																					   	cout << " Apellido Personal: " << row[2] << endl;
																					   	cout << " Puesto personal: " << row[3] << endl;
																					   	cout	<< " Telefono personal: "<< row[4]<<endl;
																					   	cout	<< " Mes de incorporacion: "<< row[6]<<endl;
																					   	cout	<< " Id del usuario: "<< row[7]<<endl;
																					   	cout	<< " Salario: "<< row[8]<<endl;
																					   	cout << "\n";
																					}
											   									}
											   									else{
																			    		cout << " Persona no encontrada" << endl;}
																			    }
																				else{
																			    		cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
																			    }
																				system("pause");
																		}
																break;
																case 2:
																		{
											            					system("cls");
											            					//Variables
											            					char *consulta;
																			int ResulConsulta=0;
																			//Sentencia para buscar por año
																			char sentencia[] =  " SELECT * FROM Personal WHERE Fecha_Incorporacion_year=\'%s\'";
																		   	cout << "\n";
																			cout<<" Ingrese el año: ";
																			cin>>YEAR;
																			consulta = new char[strlen(sentencia)+strlen(YEAR)];
																		   	sprintf(consulta, sentencia, YEAR);
																		   	// Intentar iniciar MySQL:
																		  	if(!(objDatos = mysql_init(0))) {
																			    // Imposible conectar
																			    cout << " ERROR: imposible crear el objeto objDatos." << endl;
																		  	}	
																		   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
																			    mysql_query(objDatos, consulta);
																			    res = mysql_store_result(objDatos);
																			    ResulConsulta = mysql_num_rows(res);
																		   	if(ResulConsulta>0)
																		   	{	
																		   	//Mostra contenido de las tablas
																		      while (row = mysql_fetch_row(res)){
																			      	cout << "\n";
																			    	cout << " Id Personal: " << row[0] << endl;
																				   	cout << " Nombre Personal: " << row[1] << endl;
																				   	cout << " Apellido Personal: " << row[2] << endl;
																				   	cout << " Puesto personal: " << row[3] << endl;
																				   	cout	<< " Telefono personal: "<< row[4]<<endl;
																				   	cout	<< " Año de incorporacion: "<< row[5]<<endl;
																				   	cout	<< " Id del usuario: "<< row[7]<<endl;
																				   	cout	<< " Salario: "<< row[8]<<endl;
																				   	cout << "\n";
																			  }
																		   	}
																		   	else{
																		    cout << " Persona no encontrada" << endl;}
																		    }
																			else{
																		    cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
																		    }
																			system("pause");
																		}
																	break;
																	default:
			                												cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
											}
										}while(opcion2!=3);
			                break;
                			} 
                			case 2:
				            {
				            	//Variables
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Buscar por: \n";
								cout << " 1. Id de transaccion\n";
								cout << " 2. Fecha\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
				            					char *consulta;
												int ResulConsulta=0;
												//Sentencia para buscar compras
												char sentencia[] =  "SELECT * FROM	compras WHERE ID_Transaccion=\'%s\'";
												cout << "\n";
												cout<<" Ingrese el id de transaccion: ";
												cin>>ID;
												consulta = new char[strlen(sentencia)+strlen(ID)];
											   	sprintf(consulta, sentencia,ID);
											
											   	// Intentar iniciar MySQL:
											  	if(!(objDatos = mysql_init(0))) {
											      	// Imposible crear el objeto objDatos
											    	cout << " ERROR: imposible crear el objeto objDatos." << endl;
											    
											
											  	}	
											   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
												    mysql_query(objDatos, consulta);
												    res = mysql_store_result(objDatos);
												    ResulConsulta = mysql_num_rows(res);
													
												   	if(ResulConsulta>0)
												   	{
												      	while (row = mysql_fetch_row(res)){
												      	cout << "\n";
												    	cout << " Id del articulo comprado: " << row[0] << endl;
													   	cout << " Id de la transaccion: " << row[1] << endl;
													   	cout << " Nombre del articulo comprado: " << row[2] << endl;
													   	cout << " Cantidad comprada: " << row[3] << endl;
													   	cout << " Precio del articulo comprado: "<< row[4]<<endl;
													   	cout << " Precio Total: "<< row[5]<<endl;
													   	cout << " Fecha de la compra: "<< row[6]<<endl;
													   	cout << "\n";
													}
												   
											   		}
											   		else{
											    		cout << " No se ha encontrado ningun registro" << endl;
													}
											    }
												else{
											    	cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
											    }
												system("pause");
											}
										break;
										case 2:
				            			{
				            					system("cls");
				            					char *consulta;
												int ResulConsulta=0;
												//Sentencia compras por fecha
												char sentencia[] =  "SELECT * FROM	compras WHERE Fecha_Compra=\'%s\'";
												cout << "\n";
												cout<<" Ingrese la fecha: ";
												cin>>ID;
												consulta = new char[strlen(sentencia)+strlen(ID)];
											   	sprintf(consulta, sentencia,ID);
											
											   	// Intentar iniciar MySQL:
											  	if(!(objDatos = mysql_init(0))) {
											    // Imposible crear el objeto objDatos
											    	cout << " ERROR: imposible crear el objeto objDatos." << endl;
											    
											
											  	}	
											
											   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
											
												    mysql_query(objDatos, consulta);
												    res = mysql_store_result(objDatos);
												    ResulConsulta = mysql_num_rows(res);
													
													
												   	if(ResulConsulta>0)
												   	{
												      	while (row = mysql_fetch_row(res)){
												      	cout << "\n";
												    	cout << " Id del articulo comprado: " << row[0] << endl;
													   	cout << " Id de la transaccion: " << row[1] << endl;
													   	cout << " Nombre del articulo comprado: " << row[2] << endl;
													   	cout << " Cantidad comprada: " << row[3] << endl;
													   	cout << " Precio del articulo comprado: "<< row[4]<<endl;
													   	cout << " Precio Total: "<< row[5]<<endl;
													   	cout << " Fecha de la compra: "<< row[6]<<endl;
													   	cout << "\n";
														}
													   
											   		}
											   	else{
											    	cout << " No se ha encontrado ningun registro" << endl;
												}
											    }
												else{
											    	cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
											    }
												system("pause");
											}
										break;
										
										default:
			                			cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
			                break;
                			} 
                			case 3:
				            {
				            	//Variables
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Buscar por: \n";
								cout << " 1. Id de transaccion\n";
								cout << " 2. Fecha\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
				            					char *consulta;
												int ResulConsulta=0;
												char sentencia[] =  "SELECT ID_Articulo_Venta, ID_Transaccion_Venta, Cantidad_Venta,Precio_Articulo_Venta,Precio_Total_Venta,Nombre_Articulo_Venta,Fecha_Venta FROM compras WHERE ID_Transaccion_Venta=\'%s\'";
												cout << "\n";
												cout<<" Ingrese el id de transaccion: ";
												cin>>ID;
												consulta = new char[strlen(sentencia)+strlen(ID)];
											   	sprintf(consulta, sentencia,ID);
											
											   	// Intentar iniciar MySQL:
											  	if(!(objDatos = mysql_init(0))) {
											      	// Imposible crear el objeto objDatos
											    	cout << " ERROR: imposible crear el objeto objDatos." << endl;
											    
											
											  	}	
											   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
												    mysql_query(objDatos, consulta);
												    res = mysql_store_result(objDatos);
												    ResulConsulta = mysql_num_rows(res);
													
												   	if(ResulConsulta>0)
												   	{
												      	while (row = mysql_fetch_row(res)){
												     	 cout << "\n";
												    	cout << " Id del articulo comprado: " << row[0] << endl;
													   	cout << " Id de la transaccion: " << row[1] << endl;
													   	cout << " Nombre del articulo comprado: " << row[5] << endl;
													   	cout << " Cantidad comprada: " << row[2] << endl;
													   	cout << " Precio del articulo comprado: "<< row[3]<<endl;
													   	cout << " Precio Total: "<< row[4]<<endl;
													   	cout << " Fecha de la compra: "<< row[6]<<endl;
													   	cout << "\n";
													}
												   
											   		}
											   		else{
											    		cout << " No se ha encontrado ningun registro" << endl;
													}
											    }
												else{
											    	cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
											    }
												system("pause");
											}
										break;
										case 2:
				            			{
				            					system("cls");
				            					char *consulta;
												int ResulConsulta=0;
												char sentencia[] =  "SELECT ID_Articulo_Venta, ID_Transaccion_Venta, Cantidad_Venta,Precio_Articulo_Venta,Precio_Total_Venta,Nombre_Articulo_Venta,Fecha_Venta FROM compras WHERE Fecha_Venta=\'%s\'";
												cout << "\n";
												cout<<" Ingrese la fecha: ";
												cin>>ID;
												consulta = new char[strlen(sentencia)+strlen(ID)];
											   	sprintf(consulta, sentencia,ID);
											
											   	// Intentar iniciar MySQL:
											  	if(!(objDatos = mysql_init(0))) {
											    // Imposible crear el objeto objDatos
											    	cout << " ERROR: imposible crear el objeto objDatos." << endl;
											    
											
											  	}	
											
											   	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
											
												    mysql_query(objDatos, consulta);
												    res = mysql_store_result(objDatos);
												    ResulConsulta = mysql_num_rows(res);
													
													
												   	if(ResulConsulta>0)
												   	{
												      	while (row = mysql_fetch_row(res)){
												      	cout << "\n";
												    	cout << " Id del articulo comprado: " << row[0] << endl;
													   	cout << " Id de la transaccion: " << row[1] << endl;
													   	cout << " Nombre del articulo comprado: " << row[5] << endl;
													   	cout << " Cantidad comprada: " << row[2] << endl;
													   	cout << " Precio del articulo comprado: "<< row[3]<<endl;
													   	cout << " Precio Total: "<< row[4]<<endl;
													   	cout << " Fecha de la compra: "<< row[6]<<endl;
													   	cout << "\n";
														}
													   
											   		}
											   	else{
											    	cout << " No se ha encontrado ningun registro" << endl;
												}
											    }
												else{
											    	cout<<" Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
											    }
												system("pause");
											}
										break;
										
										default:
			                			cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
			                break;
                			} 
                				case 4:
                				{
                							int opcion2;
							            	do{
											system("cls");
											cout << "\n Buscar por: \n";
											cout << " 1. Fecha\n";
											cout << " 2. Articulo\n";
											cout << " 3. Salir\n";
											cout << " Elija una opcion: ";
											cin >> opcion2;
											switch(opcion2){
												case 1:
												{
													system("cls");
													MYSQL *con = mysql_init(NULL);
									
												    if (mysql_real_connect(con, "localhost","root","root","ferreteria",3306,NULL,0) == NULL) {
												        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(con));
												        exit(1);
												    }
												
												    char fecha[20];
												    printf(" Ingrese la fecha a buscar: ");
												    scanf("%s", fecha);
													
													/* snprintf(consulta, sizeof(consulta), "SELECT ID_Articulos ,ID_Transaccion,Nombre_Articulo,Cantidad_Articulo,Precio_Articulo,Cantidad_Total,Fecha_Compra,ID_Articulo_Venta,ID_Transaccion_Venta,Cantidad_Venta,Precio_Articulo_Venta,Precio_Total_Venta,Nombre_Articulo_Venta,Fecha_Venta, Articulos.Cantidad_Articulo  FROM compras INNER JOIN Articulos ON compras.Fecha_Compra = Articulos.Fecha_Compra WHERE Fecha_Compra = '%s' OR Fecha_Venta = '%s'", fecha, fecha);*/
												
												    char consulta[200];
												    //Seleccionar por fecha kardex
												    snprintf(consulta, sizeof(consulta), "SELECT * FROM compras WHERE Fecha_Compra = '%s' OR Fecha_Venta = '%s'", fecha, fecha);
												
												    if (mysql_query(con, consulta)) {
												        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
												        exit(1);
												    }
												
												    MYSQL_RES *resultado = mysql_store_result(con);
												    if (resultado == NULL) {
												        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
												        exit(1);
												    }
													
												    int num_columnas = mysql_num_fields(resultado);
												
												    MYSQL_ROW fila;
												
												    while ((fila = mysql_fetch_row(resultado))) {
												    	if (fila[6] != NULL) {
												    		cout<<" Compra "<<endl;
											            	printf(" ID de Articulo: %s,Fecha: %s,  Id transaccion: %s, Nombre Articulo: %s, Precio Articulo: %s, Precio Total: %s,Cantidad comprada: %s", fila[0], fila[6],  fila[1],fila[2],fila[4],fila[5],fila[3]);
											            	cout<<"\n";
												        }
												        if (fila[13] != NULL) {
												    		cout<<" Venta "<<endl;
											            	printf(" Fecha: %s, ID de Articulo: %s, Id transaccion: %s, Nombre Articulo: %s, Precio Articulo: %s, Precio Total: %s,Cantidad comprada: %s", fila[13], fila[7], fila[8],fila[12],fila[11],fila[10],fila[9]);
											            	cout<<"\n";
												        }
												    }
												
												    mysql_free_result(resultado);
												    mysql_close(con);
												    system("pause");
				
												}
												break;
												case 2:
												{
													system("cls");
													MYSQL *con = mysql_init(NULL);
									
												    if (mysql_real_connect(con, "localhost","root","root","ferreteria",3306,NULL,0) == NULL) {
												        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(con));
												        exit(1);
												    }
												
												    char ID[20];
												    printf(" Ingrese el id del articulo a buscar: ");
												    scanf("%s", ID);
													
													/* snprintf(consulta, sizeof(consulta), "SELECT ID_Articulos ,ID_Transaccion,Nombre_Articulo,Cantidad_Articulo,Precio_Articulo,Cantidad_Total,Fecha_Compra,ID_Articulo_Venta,ID_Transaccion_Venta,Cantidad_Venta,Precio_Articulo_Venta,Precio_Total_Venta,Nombre_Articulo_Venta,Fecha_Venta, Articulos.Cantidad_Articulo  FROM compras INNER JOIN Articulos ON compras.Fecha_Compra = Articulos.Fecha_Compra WHERE Fecha_Compra = '%s' OR Fecha_Venta = '%s'", fecha, fecha);*/
												
												    char consulta[200];
												    snprintf(consulta, sizeof(consulta), "SELECT * FROM compras WHERE ID_Articulos = '%s' OR ID_Articulo_Venta = '%s'", ID, ID);
												
												    if (mysql_query(con, consulta)) {
												        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
												        exit(1);
												    }
												
												    MYSQL_RES *resultado = mysql_store_result(con);
												    if (resultado == NULL) {
												        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
												        exit(1);
												    }
												
												    int num_columnas = mysql_num_fields(resultado);
												
												    MYSQL_ROW fila;
												
												    while ((fila = mysql_fetch_row(resultado))) {
												    	if (fila[6] != NULL) {
												    		cout<<" Compra "<<endl;
											            	printf(" ID de Articulo: %s,Fecha: %s,  Id transaccion: %s, Nombre Articulo: %s, Precio Articulo: %s, Precio Total: %s,Cantidad comprada: %s", fila[0], fila[6],  fila[1],fila[2],fila[4],fila[5],fila[3]);
											            	cout<<"\n";
												        }
												        if (fila[13] != NULL) {
												    		cout<<" Venta "<<endl;
											            	printf(" ID de Articulo: %s,Fecha: %s, Id transaccion: %s, Nombre Articulo: %s, Precio Articulo: %s, Precio Total: %s,Cantidad comprada: %s", fila[7],fila[13],  fila[8],fila[9],fila[10],fila[11],fila[12]);
											            	cout<<"\n";
												        }
												    }
												
												    mysql_free_result(resultado);
												    mysql_close(con);
												    system("pause");
												}
												break;
											};
											}while(opcion2!=3);
									    
								}
                			break;	
		            		default:
		                		cout << " Opcion seleccionada es invalida.por favor  Intente de nuevo.\n";
		        }
		    } while (opcion != 5);
}

void  menu_registro_y_Mantenimiento() {
			//Variables
		    int opcion, q_estado;
		    cConn connDB;
			MYSQL *objDatos;
		   	MYSQL_RES *res;
		   	MYSQL_ROW  row;
		   	MYSQL_FIELD *columna;
		   	//Estructuras
		   	struct Usuarios{
			   	int ID_Usuario;
			   	int Tipo_Usuario;
			   	char Perfil_Usuario[45];
			   	char Nombre_Usuario[45];
			   	int Pass_Usuario;
			}sUsuarios;
			struct Clientes{
			   	int ID_Cliente;
			   	char Nombre_Clientes[45];
			   	char Apellido_Clientes[45];
			   	int Telefono_Clientes;
			   	int ID_Usuario_Clientes;
			}sClientes;
			struct Articulos{
		        int ID_Articulos;
		        int ID_Transaccion;
		        char Nombre_Articulo[45];
		        int Cantidad_Articulo;
		        int Precio_Articulo;
		        int Cantidad_Total;
		        char Fecha_Compra[45];
	    	}sArticulos;
	    	struct Personal{
		        int ID_Personal;
		        char Nombre_Personal[45];
		        char Apellido_Personal[45];
		        char Puesto_Personal[45];
		        int Telefono_Personal;
		        int Fecha_Incorporacion_year;
		        char Fecha_Incorporacion_mes[45];
		        int ID_Usuario_Personal;
		        int Salario_Personal;
	    	}sPersonal;
	    	struct Proveedores{
		        int ID_Proveedores;
		        char Nombre_Proveedores[45];
		        char CorreoElectronico_Proveedores[45];
		        int Telefono_Proveedores;
		        int ID_articulo_proveedores;
	    	}sProveedores;
			    do {
			    	system("cls");
			        cout << "\n REGISTRO Y MANTENIMIENTO\n";
			        cout << " 1. Usuarios\n";
			        cout << " 2. Articulos\n";
			        cout << " 3. Personal\n";
			        cout << " 4. Clientes\n";
			        cout << " 5. Proveedores\n";
			        cout << " 6. Comprar Articulos\n";
			        cout << " 7. Ventas Articulos\n";
			        cout << " 8. Salir\n";
			        cout << " Elija una opcion del menu de registro y mantenimiento: ";
			        cin >> opcion;
			        switch(opcion) {
			            case 1:
				            {
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Usuarios\n";
								cout << " 1. Ver Usuarios\n";
								cout << " 2. Insertar Usuarios\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){	
													//Sentencia para mostrar los usuarios			
													string consulta = "SELECT * from usuarios";
													const char* c = consulta.c_str();
													q_estado = mysql_query(objDatos, c);
													if(!q_estado){
														res= mysql_store_result(objDatos);
														cout<<"\n*************************************************************\n";
														while (row= mysql_fetch_row(res)){
															cout<<"	ID del Usuario: "<<row[0]<<endl;
															cout<<" Tipo de usuario: "<<row[1]<<endl;
															cout<<" Pefil del usuario: "<<row[2]<<endl;
															cout<<" Nombre del Usuario: "<<row[3]<<endl;
															cout<<" Contraseña: "<<row[4]<<endl;
															cout<<"\n";
														}
														cout<<"\n*************************************************************\n";
													}
												} 
												system("pause"); // Pausa
											}
										break;
										case 2:
											{
												system("cls");
												//Sentencia para insertar usuarios
												char *cConsulta;
											    char cSentencia[]="INSERT INTO Usuarios(Tipo_Usuario,Perfil_Usuario,Nombre_Usuario, Pass_Usuario) VALUES(\'%d\', \'%s\', \'%s\',\'%d\')";
												
												cout<<"\n*************************************************************\n";
												/*printf("Ingrese la ID del Usuario: ");
											    scanf("%d",&sUsuarios.ID_Usuario);*/
											    
											    printf(" Ingrese el Tipo de Usuario(1,2): ");
											    scanf("%d",&sUsuarios.Tipo_Usuario);
											
											    printf(" Ingresar el (Administrador, Cliente): ");
											    scanf("%s",&sUsuarios.Perfil_Usuario);
											
											    printf(" Ingrese Nombre Usuario: ");
											    scanf("%s",&sUsuarios.Nombre_Usuario);
											
											    printf(" Ingrese Contra: ");
											    scanf("%d",&sUsuarios.Pass_Usuario);
											
												cout<<"\n*************************************************************\n";
											    cConsulta = new char[strlen(cSentencia)+sizeof(Usuarios)-sizeof(int)];
											    sprintf(cConsulta,cSentencia,sUsuarios.Tipo_Usuario, sUsuarios.Perfil_Usuario, sUsuarios.Nombre_Usuario,sUsuarios.Pass_Usuario);

											    if(!(objDatos = mysql_init(0)))    {
											        cout<<" Error al cargar driver de la base de datos";
											    }
												connDB.m_conectar_BaseDeDatos(objDatos, cConsulta);
								                system("pause"); // Pausa
											}
											break;
										default:
			                			cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
			            break;
                		} 
			            case 2:
				            {
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Articulos\n";
								cout << " 1. Ver Articulos\n";
								cout << " 2. Salir\n";
								cout << "Elija una opcion del menu de registro y mantenimiento: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){	
												//Sentencia para seleccionar los articulos			
												string consulta = "SELECT * from articulos";
												const char* c = consulta.c_str();
												q_estado = mysql_query(objDatos, c);
												if(!q_estado){
													res= mysql_store_result(objDatos);
													cout<<"\n*************************************************************\n";
													while (row= mysql_fetch_row(res)){
														cout<<" Id: "<<row[0]<<endl;
														/*cout<<" Numero de transaccion: "<<row[1]<<endl;
														cout<<" Fecha transaccion: "<<row[6]<<endl;*/
														cout<<" Nombre: "<<row[2]<<endl;
														int cantidad = atoi(row[3]);
														if (cantidad < 1) {
											            cout<<" Cantidad: No hay existencias"<<endl;
												        } else {
												            cout<<" Cantidad: "<<row[3]<<endl;
												        }														
														cout<<" Precio Unitario:  "<<row[4]<<endl;
														/*cout<<" Precio Total: "<<row[5]<<endl;*/
														cout<<"\n";
													}
													cout<<"\n*************************************************************\n";
												}
												} 
												system("pause"); // Pausa
											}
										break;
										default:
			                			cout << "Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=2);
				            	             
				            
			                break;
                			} 
			           case 3:
				            {
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Personal\n";
								cout << " 1. Ver Personal\n";
								cout << " 2. Insertar Personal\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion del menu de registro y mantenimiento: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){
												//Setencia para mostrar al personal				
												string consulta = "SELECT * from personal";
												const char* c = consulta.c_str();
												q_estado = mysql_query(objDatos, c);
												if(!q_estado){
													res= mysql_store_result(objDatos);
													cout<<"\n*************************************************************\n";
													while (row= mysql_fetch_row(res)){
														cout<<"\n";
														cout<<" Id Personal: "<<row[0]<<endl;
														cout<<" Nombre Personal: "<<row[1]<<endl;
														cout<<" Apellido Personal: "<<row[2]<<endl;
														cout<<" Puesto Personal: "<<row[3]<<endl;
														cout<<" Telefono Personal : "<<row[4]<<endl;
														cout<<" Año de incorporacion : "<<row[5]<<endl;
														cout<<" Mes de incorporacion : "<<row[6]<<endl;
														cout<<" Id del usuario del empleado : "<<row[7]<<endl;
														cout<<" Salario del personal : "<<row[8]<<endl;
														cout<<"\n";
													}
													cout<<"\n*************************************************************\n";
												}
												} 
												system("pause"); // Pausa
											}
										break;
										case 2:
											{
												system("cls");
												char *cConsulta;
												//Sentencia es para insertar en la tabla personal
											    char cSentencia[]="INSERT INTO Personal(Nombre_Personal, Apellido_Personal,Puesto_Personal,Telefono_Personal, Fecha_Incorporacion_year,Fecha_Incorporacion_mes,ID_Usuario_Personal,Salario_Personal) VALUES(\'%s\',\'%s\',\'%s\',\'%d\',\'%d\',\'%s\',\'%d\',\'%d\')";
												cout<<"\n*************************************************************\n";
											    
												/*printf(" Ingrese ID del personal: ");
											    scanf("%d",&sPersonal.ID_Personal);*/
											
											    printf(" Ingrese Nombre del personal: ");
											    scanf("%s",&sPersonal.Nombre_Personal);
											
											    printf(" Ingrese Apellido del personal: ");
											    scanf("%s",&sPersonal.Apellido_Personal);
											
											    printf(" Ingrese Puesto del personal: ");
											    scanf("%s",&sPersonal.Puesto_Personal);
											    
											    printf(" Ingrese Telefono del personal: ");
											    scanf("%d",&sPersonal.Telefono_Personal);
											    
											    printf(" Ingrese el año de incorporacion: ");
											    scanf("%d",&sPersonal.Fecha_Incorporacion_year);
											    
											    printf(" Ingrese el mes de incorporacion: ");
											    scanf("%s",&sPersonal.Fecha_Incorporacion_mes);
											    
											    printf(" Ingrese el id del usuario: ");
											    scanf("%d",&sPersonal.ID_Usuario_Personal);
											    
											    printf(" Ingrese el salario del personal: ");
											    scanf("%d",&sPersonal.Salario_Personal);
											    
												cout<<"\n*************************************************************\n";
											
											    cConsulta = new char[strlen(cSentencia)+sizeof(Personal)-sizeof(int)];
											    sprintf(cConsulta,cSentencia,sPersonal.Nombre_Personal, sPersonal.Apellido_Personal, sPersonal.Puesto_Personal,sPersonal.Telefono_Personal,sPersonal.Fecha_Incorporacion_year,sPersonal.Fecha_Incorporacion_mes,sPersonal.ID_Usuario_Personal,sPersonal.Salario_Personal);
											
											    
											    if(!(objDatos = mysql_init(0)))    {
											        cout<<" Error al cargar driver de la base de datos";
											        
											    }
												connDB.m_conectar_BaseDeDatos(objDatos, cConsulta);
								                system("pause"); // Pausa
											}
											break;
										default:
			                			cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
				            	             
				            
			                break;
                			} 
			            case 4:
				            {
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Clientes\n";
								cout << " 1. Ver Clientes\n";
								cout << " 2. Insertar Clientes\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion del menu de registro y mantenimiento: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){	
												//Sentencia para selecciona a los clientes			
												string consulta = "SELECT * from clientes";
												const char* c = consulta.c_str();
												q_estado = mysql_query(objDatos, c);
												if(!q_estado){
													res= mysql_store_result(objDatos);
													cout<<"\n*************************************************************\n";
													while (row= mysql_fetch_row(res)){
														
														cout<<" Id del cliente: "<<row[0]<<endl;
														cout<<" Nombre del cliente: "<<row[1]<<endl;
														cout<<" Apellido del cliente: "<<row[2]<<endl;
														cout<<" Telefono: "<<row[3]<<endl;
														cout<<" Id del usuario del cliente: "<<row[4]<<endl;
														cout<<"\n";
													}
													cout<<"\n*************************************************************\n";
												}
												} 
												system("pause"); // Pausa
											}
										break;
										case 2:
											{
												system("cls");
												char *cConsulta;
											    char cSentencia[]="INSERT INTO Clientes(Nombre_Clientes, Apellido_Clientes, Telefono_Cliente, ID_Usuario_Cliente) VALUES(\'%s\', \'%s\', \'%d\',\'%d\')";
												cout<<"\n*************************************************************\n";
											    /*printf("Ingrese ID del cliente: ");
											    scanf("%d",&sClientes.ID_Cliente);*/
											
											    printf(" Ingrese Nombre del cliente: ");
											    scanf("%s",&sClientes.Nombre_Clientes);
											
											    printf(" Ingrese Apellido del cliente: ");
											    scanf("%s",&sClientes.Apellido_Clientes);
											
											    printf(" Ingrese telefono cliente: ");
											    scanf("%d",&sClientes.Telefono_Clientes);
											    
											    printf(" Ingrese ID del usuario del cliente: ");
											    scanf("%d",&sClientes.ID_Usuario_Clientes);
												cout<<"\n*************************************************************\n";
											
											    cConsulta = new char[strlen(cSentencia)+sizeof(Clientes)-sizeof(int)];
											    sprintf(cConsulta,cSentencia, sClientes.Nombre_Clientes, sClientes.Apellido_Clientes, sClientes.Telefono_Clientes,sClientes.ID_Usuario_Clientes);
											
											    
											    if(!(objDatos = mysql_init(0)))    {
											        cout<<" Error al cargar driver de la base de datos";
											        
											    }
												connDB.m_conectar_BaseDeDatos(objDatos, cConsulta);
								                system("pause"); // Pausa
											}
											break;
										default:
			                			cout << " Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
			                break;
                			} 
			            case 5:
			                {
				            	int opcion2;
				            	do{
								system("cls");
								cout << "\n Proveedores\n";
								cout << " 1. Ver Proveedores\n";
								cout << " 2. Insertar Proveedores\n";
								cout << " 3. Salir\n";
								cout << " Elija una opcion del menu de registro y mantenimiento: ";
								cin >> opcion2;
				            		switch(opcion2){
				            			case 1:
				            				{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){		
												//Sentencia para seleccionar proveedores		
												string consulta = "SELECT * from proveedores";
												const char* c = consulta.c_str();
												q_estado = mysql_query(objDatos, c);
												if(!q_estado){
													res= mysql_store_result(objDatos);
													cout<<"\n*************************************************************\n";
													while (row= mysql_fetch_row(res)){
														cout<<" Id del proveedor: "<<row[0]<<endl;
														cout<<" Nombre del proveedor: "<<row[1]<<endl;
														cout<<" Correo Electronico: "<<row[2]<<endl;
														cout<<" Telefono proveedor: "<<row[3]<<endl;
														cout<<" Id del articulo: "<<row[4]<<endl;
														cout<<"\n";
													}
													cout<<"\n*************************************************************\n";
												}
												} 
												system("pause"); // Pausa
											}
										break;
										case 2:
											{
												system("cls");
												char *cConsulta;
											    char cSentencia[]="INSERT INTO proveedores(Nombre_Proveedores,CorreoElectronico_Proveedores,Telefono_Proveedores,ID_articulo_proveedores) VALUES(\'%s\', \'%s\',\'%d\',\'%d\')";
												cout<<"\n*************************************************************\n";
											    /*printf("Ingrese ID del proveedor: ");
											    scanf("%d",&sProveedores.ID_Proveedores);*/
											
											    printf(" Ingrese el nombre del proveedor ");
											    scanf("%s",&sProveedores.Nombre_Proveedores);
											
											    printf(" Ingrese el correo electronico: ");
											    scanf("%s",&sProveedores.CorreoElectronico_Proveedores);
											
											    printf(" Ingrese el telefono del proveedor: ");
											    scanf("%d",&sProveedores.Telefono_Proveedores);
											    
											    printf(" Ingrese la ID del articulo: ");
											    scanf("%d",&sProveedores.ID_articulo_proveedores);
											    
												cout<<"\n*************************************************************\n";
											
											    cConsulta = new char[strlen(cSentencia)+sizeof(Proveedores)-sizeof(int)];
											    sprintf(cConsulta,cSentencia,sProveedores.Nombre_Proveedores, sProveedores.CorreoElectronico_Proveedores, sProveedores.Telefono_Proveedores,sProveedores.ID_articulo_proveedores);
											
											    
											    if(!(objDatos = mysql_init(0)))    {
											        cout<<"Error al cargar driver de la base de datos";
											        
											    }
												connDB.m_conectar_BaseDeDatos(objDatos, cConsulta);
								                system("pause"); // Pausa
											}
											break;
										default:
			                			cout << "Opcion es invalida.por favor  Intente de nuevo.\n";
									}
								}while(opcion2!=3);
			                break;
                			} 
			            case 6:
			                	{		
			                			srand(time(0)); 
			                			int result;
			                			int Factura= rand() % 999 + 1;
										system("cls");
								        
								        MYSQL *con = mysql_init(NULL);
									
									    if (mysql_real_connect(con, "localhost","root","root","ferreteria",3306,NULL,0) == NULL) {
									        fprintf(stderr, "Error al conectar a la base de datos\n", mysql_error(con));
									        exit(1);
									    }
									
									    // Solicitar al usuario que ingrese un dato
									    //printf(" Ingrese ID de la transaccion: ");
										//scanf("%d",&sArticulos.ID_Transaccion);
										cout<<" Numero de fatura generado: "<<Factura<<endl;
										
										printf(" Ingrese Nombre del articulo: ");
										scanf("%s",&sArticulos.Nombre_Articulo);
											
										printf(" Ingrese Cantidad del articulo: ");
										scanf("%d",&sArticulos.Cantidad_Articulo);
											
										printf(" Ingrese Precio Articulo: ");
										scanf("%d",&sArticulos.Precio_Articulo);
										
										sArticulos.Cantidad_Total=(sArticulos.Cantidad_Articulo)*(sArticulos.Precio_Articulo);
										
										cout<<" Precio Total: "<<sArticulos.Cantidad_Total<<endl;
										
										printf(" Ingrese Fecha de compra: ");
										scanf("%s",&sArticulos.Fecha_Compra);

									    char consulta1[200];
									    //Insertar Articulos en tabla articulos
									    sprintf(consulta1, "INSERT INTO articulos(ID_Transaccion,Nombre_Articulo, Cantidad_Articulo, Precio_Articulo,Cantidad_Total,Fecha_Compra) VALUES(\'%d\', \'%s\', \'%d\',\'%d\', \'%d\',\'%s\')", Factura, sArticulos.Nombre_Articulo, sArticulos.Cantidad_Articulo, sArticulos.Precio_Articulo,sArticulos.Cantidad_Total,sArticulos.Fecha_Compra);
									
									    if (mysql_query(con, consulta1)) {
									        fprintf(stderr, "Error al ejecutar la consulta %s\n", mysql_error(con));
									        exit(1);
									    }
										
										//Inserta Articulos en la tabla Compras
									    char consulta2[200];
									    sprintf(consulta2, "INSERT INTO compras(ID_Transaccion,Nombre_Articulo, Cantidad_Articulo, Precio_Articulo,Cantidad_Total,Fecha_Compra) VALUES(\'%d\', \'%s\', \'%d\',\'%d\', \'%d\',\'%s\')", Factura, sArticulos.Nombre_Articulo, sArticulos.Cantidad_Articulo, sArticulos.Precio_Articulo,sArticulos.Cantidad_Total,sArticulos.Fecha_Compra);
									
									    if (mysql_query(con, consulta2)) {
									        fprintf(stderr, "Error al ejecutar la consulta 2 %s\n", mysql_error(con));
									        exit(1);
									    }
									
									    cout<<" Compra realizada correctamente\n";
									
									    mysql_close(con);
									    
									    system("pause");
								        						
								        
									}
									break;
			            case 7:
			                	{
				            					system("cls");
								            	objDatos = mysql_init(0);
								            	objDatos = mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0);
								            	if(objDatos){	
												
												//Sentencia Ver articulos vendidos		
													string consulta = "SELECT ID_Articulo_Venta, ID_Transaccion_Venta, Cantidad_Venta,Precio_Articulo_Venta,Precio_Total_Venta,Nombre_Articulo_Venta,Fecha_Venta FROM compras WHERE ID_Articulo_Venta IS NOT NULL AND ID_Transaccion_Venta IS NOT NULL AND Cantidad_Venta IS NOT NULL AND Precio_Articulo_Venta IS NOT NULL AND Precio_Total_Venta IS NOT NULL AND Nombre_Articulo_Venta IS NOT NULL AND Fecha_Venta IS NOT NULL";
													const char* c = consulta.c_str();
													q_estado = mysql_query(objDatos, c);
													if(!q_estado){
														res= mysql_store_result(objDatos);
														cout<<"\n*************************************************************\n";
														while (row= mysql_fetch_row(res)){
														if (row[0] != NULL) {
											            cout<<" ID del articulo vendido: "<<row[0]<<endl;
												        }
												        if (row[1] != NULL) {
												            cout<<" ID de la factura: "<<row[1]<<endl;
												        }
												        if (row[2] != NULL) {
												            cout<<" Cantidad vendida: "<<row[2]<<endl;
												        }
												        if (row[3] != NULL) {
												            cout<<" Precio por unidad: "<<row[3]<<endl;
												        }
												         if (row[4] != NULL) {
												            cout<<" Precio total vendido: "<<row[4]<<endl;
												        }
												         if (row[5] != NULL) {
												            cout<<" Nombre del articulo Vendido: "<<row[5]<<endl;
												        }
												         if (row[6] != NULL) {
												            cout<<" Fecha de la Venta: "<<row[6]<<endl;
												        }
												        cout<<"\n";
														}
														cout<<"\n*************************************************************\n";
													}
												} 
												system("pause"); // Pausa
											}
			                break;
			            default:
			                cout << "Opcion es invalida.por favor  Intente de nuevo.\n";
			        }
			    } while (opcion != 8);
}
int main() {
	//Variables
	MYSQL *objDatos;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	int opcion;
	int Passrow;
	int TipoUsuario;		
	int ContraIngresada;
	int resultadoconsulta=0;
	char* user;
	char* Contra;
	char Usuario[15];
	char *consulta;
	//Menu
	cout << "\n                                LOGIN"<<endl;
	cout << "\n ************************************************************************\n";
	cout << " Ingrese su nombre de usuario: ";
	cin >> Usuario;
	cout << "\n Ingrese password: ";
	cin >> ContraIngresada;
	
	//Setencia para buscar usuario
	char sentencia[] =  "SELECT * FROM usuarios WHERE Nombre_Usuario=\'%s\'";
	consulta = new char[strlen(sentencia)+strlen(Usuario)];
   	sprintf(consulta, sentencia, Usuario);
   	//Conectar a la base de datos
   	if(!(objDatos = mysql_init(0))) {
    	cout << "Error al conectar base de datos" << endl;
    	return 1;
  	}
  	if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
		mysql_query(objDatos, consulta);
		res = mysql_store_result(objDatos);
		resultadoconsulta = mysql_num_rows(res);		
		if(resultadoconsulta>0){
			row = mysql_fetch_row(res);
			Contra = row[4];
			user = row[1];
			TipoUsuario= atoi(user);
			Passrow= atoi(Contra);
			if(Passrow==ContraIngresada){
				system ("cls"); 
				switch(TipoUsuario){
				case 1:
					//Case Menu Administrador
					do {
						system("cls");
				    	cout << "\n MENU PRINCIPAL\n";
				        cout << " 1. Registro y Mantenimiento\n";
				        cout << " 2. Reportes\n";
				        cout << " 3. Salir\n";
				        cout << " por favor elija una opcion: ";
				        cin >> opcion;			        
						switch(opcion) {
						    case 1:
						    menu_registro_y_Mantenimiento();
						    break;
						    case 2:
						   	menu_reportes();
						    break;
						    case 3:
						    cout << " Saliendo del programa...\n";
						    break;
						    default:
						    cout << " la opcion seleccionada es invalida .por favor  Intente de nuevo.\n";
						}
					}while (opcion != 3);
					break;
				case 2:
					//Case Menu Usuario
					Menu_Usuario();					
				}
			}else{cout<<"\n Contraseña incorrecta";}
		}else{cout <<"\n Usuario no encontrado" <<endl;}    
	}else{cout<<"\n Usuario incorrecto"<<mysql_error(objDatos);}
    return 0;

}
