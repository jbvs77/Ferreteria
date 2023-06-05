#ifndef MENUS_H
#define MENUS_H
#include "cConn.h"
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <string>
using namespace std;

class MENUS{
	private:
		//Variables
		int opcion;
		cConn connDB;
		MYSQL *objDatos;
	   	MYSQL_RES       *res;
	   	MYSQL_ROW        row;
	   	MYSQL_FIELD     *columna;
	   	//Estructura
	   	struct Articulos{
        int ID_Articulos;
        char Nombre_Articulo[45];
        int Cantidad_Articulo;
        int Precio_Articulo;
    	}sArticulos;
	public:
		//submenu registro y mantenimiento
		void  menu_registro_y_Mantenimiento() {
		    int opcion;
			    do {
			    	system("cls");
			        cout << "\nREGISTRO Y MANTENIMIENTO\n";
			        cout << "1. Articulos\n";
			        cout << "2. Personal\n";
			        cout << "3. Clientes\n";
			        cout << "4. Proveedores\n";
			        cout << "5. Compras\n";
			        cout << "6. Ventas\n";
			        cout << "7. Salir\n";
			        cout << "Elija una opcion del menu de registro y mantenimiento: ";
			        cin >> opcion;
			        
			        switch(opcion) {
			            case 1:
				            {
				            // Lista de instrucciones de la opción 1                
				            char *cConsulta;
							system("cls");
						    char cSentencia[]="INSERT INTO articulos(ID_Articulos,Nombre_Articulo, Cantidad_Articulo, Precio_Articulo) VALUES(\%d\, \'%s\', \'%d\',\'%d\')";
						
						    printf("Ingrese ID del articulo: ");
						    scanf("%d",&sArticulos.ID_Articulos);
						
						    printf("Ingrese Nombre del articulo: ");
						    scanf("%s",&sArticulos.Nombre_Articulo);
						
						    printf("Ingrese Cantidad del articulo: ");
						    scanf("%d",&sArticulos.Cantidad_Articulo);
						
						    printf("Ingrese Precio Articulo: ");
						    scanf("%d",&sArticulos.Precio_Articulo);
						
						
						    cConsulta = new char[strlen(cSentencia)+sizeof(Articulos)-sizeof(int)];
						    sprintf(cConsulta,cSentencia, sArticulos.ID_Articulos, sArticulos.Nombre_Articulo, sArticulos.Cantidad_Articulo, sArticulos.Precio_Articulo);
						
						    
						    if(!(objDatos = mysql_init(0)))    {
						        cout<<"Error al cargar driver de la base de datos";
						        
						    }
							connDB.m_conectar_BaseDeDatos(objDatos, cConsulta);
			                system("pause>nul"); // Pausa
			                break;
                } 
			            case 2:
			            	{
							
			                cout << "bienvenido a la opcion de Personal.\n";
							char *consulta2;
							int ResulConsulta=0;
							char sentencia2[] = "SELECT * FROM articulos;
							MYSQL_RES *res;
							MYSQL_ROW row;
							MYSQL *objDatos;
							consulta2 = new char[strlen(sentencia2)];
							sprintf(consulta2, sentencia2);
							// Intentar iniciar MySQL:
							if(!(objDatos = mysql_init(0))) {
							// Imposible crear el objeto objDatos
							cout << "ERROR: imposible crear el objeto objDatos." << endl;
							}
							if(mysql_real_connect(objDatos,"localhost","root","root","ferreteria",3306,NULL,0)){
							mysql_query(objDatos, consulta2);
							res = mysql_store_result(objDatos);
							ResulConsulta = mysql_num_rows(res);
							if(ResulConsulta>0)
							{
								while (row= mysql_fetch_row(res)){
									cout<<"ID: "<<row[0]<<" NOMBRE: "<<row[1]<<" CANTIDAD: "<<row[2]<<" PRECIO: "<<row[3]<<endl;
								}
							}
							else{
							cout << "Persona no encontrada" << endl;}
							}
							else{
							cout<<"Error al conectarse a la base de datos..-->"<<mysql_error(objDatos);
							}
							}
							
			                break;
			            case 3:
			                cout << "bienvenido a  la opcion de Clientes.\n";
			                break;
			            case 4:
			                cout << "bienvenido a  la opcion de Proveedores.\n";
			                break;
			            case 5:
			                cout << "bienvenido a  la opcion de Compras.\n";
			                break;
			            case 6:
			                cout << "bienvenido a la opcion de Ventas.\n";
			                break;
			            case 7:
			                cout << "un momento, esta volviendo al menu principal...\n";
			                break;
			            default:
			                cout << "Opcion es invalida.por favor  Intente de nuevo.\n";
			        }
			    } while (opcion != 7);
		}
		// sub menu reportes 
		void menu_reportes() {
		    int opcion;
		    do {
		    	system("cls");
		        cout << "\nREPORTES\n";
		        cout << "1. Compras\n";
		        cout << "2. Ventas\n";
		        cout << "3. Kardex\n";
		        cout << "4. Salir\n";
		        cout << "Elija una opcion del menu reportes : ";
		        cin >> opcion;
		        
		        switch(opcion) {
		            case 1:
		                cout << "bienvenido a la opcion  de Compras.\n";
		                break;
		            case 2:
		                cout << "bienvenido a  la opcion  de Ventas.\n";
		                break;
		            case 3:
		                cout << "bienvenido a la opcion de Kardex.\n";
		                break;
		            case 4:
		                cout << "un momento,esta volviendo al menu principal...\n";
		                break;
		            default:
		                cout << "Opcion seleccionada es invalida.por favor  Intente de nuevo.\n";
		        }
		    } while (opcion != 4);
		}

};
#endif
