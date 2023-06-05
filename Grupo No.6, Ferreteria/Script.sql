/*Crear Base de datos*/
create database Ferreteria;
use Ferreteria;
show tables;
drop database ferreteria;
/*Creacion de tablas*/
create table Articulos(
ID_Articulos int primary key auto_increment,
ID_Transaccion int,
Nombre_Articulo varchar(50),
Cantidad_Articulo int,
Precio_Articulo int,
Cantidad_Total int,
Fecha_Compra varchar(50)
);
Select * from compras;
Select * from articulos;
drop table Articulos;
drop table compras;
insert into articulos(ID_Transaccion,Nombre_Articulo, Cantidad_Articulo, Precio_Articulo,Cantidad_Total,Fecha_Compra) values(202,'Lapicero',100,2,200,'20-12-12');

create table compras(
ID_Articulos int primary key auto_increment,
ID_Transaccion int,
Nombre_Articulo varchar(50),
Cantidad_Articulo int,
Precio_Articulo int,
Cantidad_Total int,
Fecha_Compra varchar(50),

ID_Articulo_Venta int,
ID_Transaccion_Venta int,
Cantidad_Venta int,
Precio_Articulo_Venta int,
Precio_Total_Venta int,
Nombre_Articulo_Venta Varchar(50),
Fecha_Venta varchar(50)
);

create table Usuarios(
ID_Usuario int Primary key auto_increment,
Tipo_Usuario int not null,
Perfil_Usuario varchar(50)  not null,
Nombre_Usuario varchar(50) not null,
Pass_Usuario int not null
);

Select * from usuarios;
drop table usuarios;
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(1,"Administrador","Adolfo",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Hernesto",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Paquito",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Stan",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Fransin",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Roger",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(2,"Usuario","Andrea",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(1,"Usuario","Hernesto",1234);
insert into usuarios(Tipo_Usuario,Perfil_Usuario, Nombre_Usuario,Pass_Usuario) values(1,"Administrador","Josue",1234);


create table Clientes(
ID_Cliente int Primary key auto_increment,
Nombre_Clientes varchar(50) not null,
Apellido_Clientes varchar(50) not null,
Telefono_Cliente int not null,
ID_Usuario_Cliente int,
FOREIGN KEY (ID_Usuario_Cliente) REFERENCES Usuarios(ID_Usuario)
);
Select * from Clientes;
drop table Clientes;
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Pedro","Aldana",55678101,2);
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Paquito","Torres",12223810,3);
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Stan","Simpson",34220033,4);
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Fransin","Smith",87779033,5);
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Roger","Hernandez",53112565,6);
insert into Clientes(Nombre_Clientes, Apellido_Clientes,Telefono_Cliente,ID_Usuario_Cliente) values("Andrea","Marroquin",34122654,7);


create table Personal(
ID_Personal int Primary key auto_increment,
Nombre_Personal varchar(50) not null,
Apellido_Personal varchar(50) not null,
Puesto_Personal varchar(50) not null,
Telefono_Personal int not null,
Fecha_Incorporacion_year int not null,
Fecha_Incorporacion_mes varchar(50) not null,
ID_Usuario_Personal int not null,
Salario_Personal int not null,
FOREIGN KEY (ID_Usuario_Personal) REFERENCES Usuarios(ID_Usuario)
);
select * from personal;
drop table personal;
insert into Personal(Nombre_Personal, Apellido_Personal,Puesto_Personal,Telefono_Personal, Fecha_Incorporacion_year,Fecha_Incorporacion_mes,ID_Usuario_Personal, Salario_Personal) values("Hernesto","Torres","Ventas",33456100,2005,"Diciembre",2,3500);
insert into Personal(Nombre_Personal, Apellido_Personal,Puesto_Personal,Telefono_Personal, Fecha_Incorporacion_year,Fecha_Incorporacion_mes,ID_Usuario_Personal, Salario_Personal) values("Josue","Matildo","Compras",12330988,2003,"Diciembre",9,4000);

create table Proveedores(
ID_Proveedores int primary key auto_increment,
Nombre_Proveedores varchar(50) not null,
CorreoElectronico_Proveedores varchar(50) not null,
Telefono_Proveedores int,
ID_articulo_proveedores int,
FOREIGN KEY (ID_articulo_proveedores) REFERENCES Articulos(ID_Articulos)
);
select * from proveedores;
drop table proveedores;
insert into proveedores(Nombre_Proveedores, CorreoElectronico_Proveedores,Telefono_Proveedores,ID_articulo_proveedores)values("Platino","platino@gmail",90008312,1);


