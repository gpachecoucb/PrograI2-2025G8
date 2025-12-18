#include <iostream>
#include "Producto.h"
#include "Facturacion_detalle.h"
#include "Facturacion.h"
#include "Libreria_Trabajadores.h"
#include "Libreria_Clientes.h"
#include "Libreria_Proveedores.h"
#include <ctime>
#include <map>

void MostrarMenuPrincipal();
void MostrarProductosBajoInventario(string NombreArchivo);
void MostrarProductosMasVendidos();
void MostrarProductosMenosVendidos();
void MostrarVentasDelDiaTotalGanado();
void MostrarProductosVendidosPersonaCIX(int ci);
int MenuReportes();
void MostrarMenuReportes();
void MostrarClientesFacturados();
int main(){
    int opcion;
    vector<Producto> vector_productos;
    CargarDatosBinarioVectorP("Productos.bin", vector_productos);
    vector<FacturacionDetalle> vector_FacturacionDetalles;
    CargarDatosBinarioVectorDF("FacturacionDetalles.bin", vector_FacturacionDetalles);
    vector<Facturacion> vector_Facturaciones;
    CargarDatosBinarioVectorF("Facturaciones.bin", vector_Facturaciones);

    
    do{
        system("cls");
        MostrarMenuPrincipal();
        
        cout << "Escoja una opcion"<< endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            ControlProductos(vector_productos);
            break;
        case 2:
            ControlFacturacionDetalles(vector_FacturacionDetalles);
            break;
        case 3:
            ControlFacturaciones(vector_Facturaciones, vector_FacturacionDetalles);
            break;
        case 4:
            Menu_Trabajadores();
            break;
        case 5:
            Menu_Clientes();
            break;
        case 6:
            Menu_Proveedores();
            break;
        case 7:
            MenuReportes();
            break;
        
        case 0:
            
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            system("pause");
            break;
        }
       
        
        
    }while (opcion != 0);
    return 0;
}
int MenuReportes(){
    int opcion;
    do{
        system("cls");
        MostrarMenuReportes();
        cout << "Escoja una opcion"<< endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            system("cls");
            MostrarProductosBajoInventario("Productos.bin");
            system("pause");
            break;
        case 2:
            system("cls");
            MostrarProductosMasVendidos();
            system("pause");
            break;
            
        case 3:
            system("cls");
            MostrarProductosMenosVendidos();
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "Ingrese el ci del cliente: " << endl;
            int ci;
            cin >> ci;
            cin.ignore();
            MostrarProductosVendidosPersonaCIX(ci);
            system("pause");
            break;
        case 5:
            system("cls");
            MostrarVentasDelDiaTotalGanado();
            system("pause");
            break;
        case 6:
            system("cls");
            MostrarClientesFacturados() ;
            system("pause");
            break;
        
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            system("pause");
            break;
        }

    }while(opcion != 0);
    return 0;

}
void MostrarMenuReportes(){
    cout << "=============================" << endl;
    cout << "Menu Reportes:" << endl;
    cout << "=============================" << endl;
    cout << "1. Productos de bajo inventario" << endl;
    cout << "2. Productos mas vendidos" << endl;
    cout << "3. Productos menos vendidos" << endl;
    cout << "4. Listar Productos comprados por un cliente" << endl;
    cout << "5. Ventas del dia y total ganado" << endl;
    cout << "6. Mostar Clientes Facturados" << endl;
    
    cout << "0. Salir" << endl;
     
    cout << "=============================" << endl;
}
void MostrarMenuPrincipal(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria:" << endl;
    cout << "=============================" << endl;
    cout << "1. Control de Productos" << endl;
    cout << "2. Control de FacturacionDetalles"<< endl;
    cout << "3. Control de Facturacion"<< endl;
    cout << "4. Control de Trabajadores"<<endl;
    cout << "5. Control de Clientes"<<endl;
    cout << "6. Control de Proveedores" << endl;
    cout << "7. REPORTES" << endl;
    cout <<  "0. Salir" << endl;
    
    cout << "=============================" << endl;
}
/*
REPORTES A HACER:
-Listado general de todas las estructuras (HECHO)
-Listar Productos con menos de 5 unidades en inventario (HECHO)
-Mostrar Productos mas vendido y cuantos se vendieron y la ganancia (HECHO)
-Mostrar el producto menos vendido y cuantos se vendieron y la ganancias (HECHO)
-Lista de productos que compro la persona con ci X (HECHO)
-Ventas deL dia y el total ganado (HECHO)
-Clientes facturados
-Ordenamiento alfabetico de clientes
*/
void MostrarClientesFacturados() {
    // 1. Cargar todas las facturas en memoria agrupadas por CI
    // Usamos un mapa: La llave es el CI (int), el valor es una lista de Nros de Factura (vector<int>)
    map<int, vector<int>> facturas_por_cliente;
    
    ifstream archivoFacturas("Facturaciones.bin", ios::binary);
    if (!archivoFacturas) {
        cout << "No se pudo abrir el archivo de Facturaciones o no existen facturas aun." << endl;
        return;
    }

    Facturacion facturacion;
    while (archivoFacturas.read((char*)&facturacion, sizeof(Facturacion))) {
        if (!facturacion.eliminado) {
            // Guardamos el numero de factura en la lista correspondiente a ese CI
            facturas_por_cliente[facturacion.ci_cliente].push_back(facturacion.nro_factura);
        }
    }
    archivoFacturas.close();

    // Si no hay facturas cargadas, no tiene sentido seguir
    if (facturas_por_cliente.empty()) {
        cout << "No hay facturas registradas en el sistema." << endl;
        return;
    }

    // 2. Recorrer la lista de clientes y cruzar informacion
    ifstream archivoClientes("Lista_de_Clientes.bin", ios::binary);
    if (!archivoClientes) {
        cout << "No se pudo abrir el archivo de Clientes." << endl;
        return;
    }

    Clientes cliente;
    bool hay_algun_facturado = false;

    cout << "=======================================================" << endl;
    cout << "       REPORTE DE CLIENTES CON FACTURACION" << endl;
    cout << "=======================================================" << endl;

    while (archivoClientes.read((char*)&cliente, sizeof(Clientes))) {
        // Verificamos si el CI del cliente existe en nuestro mapa de facturas
        // .count() devuelve 1 si existe, 0 si no.
        if (facturas_por_cliente.count(cliente.Nro_CI) > 0) {
            hay_algun_facturado = true;
            
            cout << "Cliente : " << cliente.Nombres << " " << cliente.Apellidos << endl;
            cout << "CI      : " << cliente.Nro_CI << endl;
            cout << "Facturas: ";

            // Obtenemos la lista de facturas de este cliente especifico
            vector<int> lista_facturas = facturas_por_cliente[cliente.Nro_CI];
            
            // Las imprimimos separadas por coma
            for (size_t i = 0; i < lista_facturas.size(); i++) {
                cout << "#" << lista_facturas[i];
                if (i < lista_facturas.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "-------------------------------------------------------" << endl;
        }
    }
    archivoClientes.close();

    if (!hay_algun_facturado) {
        cout << "Ningun cliente registrado tiene facturas asociadas." << endl;
        // (Esto pasaria si hay facturas pero son de CIs que no estan en el archivo de clientes)
    }
}
void MostrarVentasDelDiaTotalGanado(){
    time_t ahora = time(0);
    tm *tiempo = localtime(&ahora);
    int anio = 1900 + tiempo->tm_year;
    int mes = 1 + tiempo->tm_mon;
    int dia = tiempo->tm_mday;
    ifstream archivoFacturacion;
    double contador_ganancias;
    archivoFacturacion.open("Facturaciones.bin", ios::binary);
    Facturacion facturacion;
    if(archivoFacturacion.good()){
        while(archivoFacturacion.read((char*)&facturacion, sizeof(facturacion))){
            if(!facturacion.eliminado){
                if(facturacion.fecha.año == anio && facturacion.fecha.mes == mes && facturacion.fecha.dia == dia){
                    cout << "------------------------------------" << endl;
                    cout << "Nro Factura: " << facturacion.nro_factura <<endl;
                    cout << "Ci Cliente: " << facturacion.ci_cliente << endl;
                    cout << "Fecha: " << facturacion.fecha.dia << "/" << facturacion.fecha.mes << "/"<<facturacion.fecha.año << endl;
                    cout << "TOTAL: " << facturacion.total_factura << endl;
                    cout << "------------------------------------" << endl;
                    MostrarFacturacionDetallesNroFacturas("FacturacionDetalles.bin", facturacion.nro_factura);
                    contador_ganancias += facturacion.total_factura;
                }
            }
        }
    }
    archivoFacturacion.close();
    cout << "TOTAL GANADO EL DIA DE HOY" << endl;
    cout << contador_ganancias << endl;
    cout << "==========================" << endl;

}
void MostrarProductosVendidosPersonaCIX(int ci) {
    //  Buscar al Cliente
    ifstream archivoClientes("Lista_de_clientes.bin", ios::binary);
    Clientes cliente;
    Clientes clienteBuscado;
    bool encontrado = false;

    if (archivoClientes.good()) {
        while (archivoClientes.read((char*)&cliente, sizeof(Clientes))) {
            if (cliente.Nro_CI == ci) { 
                clienteBuscado = cliente;
                encontrado = true;
                break; 
            }
        }
    }
    archivoClientes.close();

    if (!encontrado) {
        cout << "No existe cliente con CI " << ci << " registrado." << endl;
        return;
    }

    // Obtener los IDs de las facturas de este cliente
    vector<int> ids_facturas_cliente;
    ifstream archivoFacturacion("Facturaciones.bin", ios::binary);
    Facturacion facturacion;

    if (archivoFacturacion.good()) {
        while (archivoFacturacion.read((char*)&facturacion, sizeof(Facturacion))) {
            if (facturacion.ci_cliente == ci) { 
                ids_facturas_cliente.push_back(facturacion.nro_factura);
            }
        }
    }
    archivoFacturacion.close();

    if (ids_facturas_cliente.empty()) {
        cout << "El cliente " << clienteBuscado.Nombres << " no tiene compras registradas." << endl;
        return;
    }

    // Cargar Productos (para saber el nombre luego)
    vector<Producto> todos_los_productos;
    CargarDatosBinarioVectorP("Productos.bin", todos_los_productos);

    //  Leer Detalles UNA SOLA VEZ y sumar cantidades
    // Map: Key = ID_Producto, Value = Cantidad Comprada Total (Es el funcionamiento de un diccionario)
    map<int, int> conteo_productos; 

    ifstream archivoDetalles("FacturacionDetalles.bin", ios::binary);
    FacturacionDetalle detalle;

    if (archivoDetalles.good()) {
        while (archivoDetalles.read((char*)&detalle, sizeof(FacturacionDetalle))) {
            if (!detalle.eliminado) {
                // Verificamos si esta detalle pertenece a alguna factura del cliente
                bool es_factura_cliente = false;
                for (int id_fact : ids_facturas_cliente) { // id_fact = id_factura del vector ids_facturas_cliente
                    if (detalle.nro_factura == id_fact) {
                        es_factura_cliente = true;
                        break;
                    }
                }

                // Si es una compra de este cliente, sumamos
                if (es_factura_cliente) {
                    conteo_productos[detalle.id_producto] += detalle.cantidad;
                }
            }
        }
    }
    archivoDetalles.close();

    // 5. Mostrar Resultados
    cout << "---------------------------------------" << endl;
    cout << "Cliente: " << clienteBuscado.Nombres << endl;
    cout << "CI: " << clienteBuscado.Nro_CI << endl;
    cout << "Productos Comprados:" << endl;

    bool compro_algo = false;
    // Recorremos todos los productos para ver cuáles compró
    for (Producto prod : todos_los_productos) { // por cada producto en el vector de productos
        // Buscamos si el ID del producto existe en nuestro mapa de conteo
        if (conteo_productos.count(prod.id_producto) > 0) {
            int cantidad = conteo_productos[prod.id_producto];
            if (cantidad > 0) {
                cout << " - " << prod.nombre << ": " << cantidad << " unidades." << endl;
                compro_algo = true;
            }
        }
    }

    if (!compro_algo) {
        cout << " (No se encontraron detalles de productos para las facturas registradas)" << endl;
    }
    cout << "---------------------------------------" << endl;
}
void MostrarProductosBajoInventario(string NombreArchivo)
{
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin",
                                     "Pintura", "Decoracion", "Hogar y limpieza",
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz"};
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Producto producto;
    if (archivo.good())
    {
        while (archivo.read((char *)&producto, sizeof(Producto)))
        {
            if (!producto.eliminado)
            {
                if(producto.cantidad <= 5){
                    cout << "---------------------------------------" << endl;
                    cout << "ID_producto: " << producto.id_producto << endl;
                    cout << "ID_proveedor: " << producto.id_proveedor << endl;
                    cout << "Nombre: " << producto.nombre << endl;
                    if (producto.tipo >= 1 && producto.tipo <= tipo_productos.size()) {
                        cout << "Tipo: " << tipo_productos[producto.tipo - 1] << endl;
                    } else {
                        cout << "Tipo: ERROR/DESCONOCIDO (" << producto.tipo << ")" << endl;
                    }
                    cout << "Marca: " << producto.marca << endl;
                    cout << "Distribuidor: " << producto.distribuidor << endl;
                    cout << "Cantidad en inventario: " << producto.cantidad << endl;
                    cout << "Precio de compra: " << producto.precio_Compra << endl;
                    cout << "Precio de venta: " << producto.precio_Venta << endl;
                }
            }
        }
    }
    archivo.close();
}
void MostrarProductosMasVendidos() 
{
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin",
                                     "Pintura", "Decoracion", "Hogar y limpieza",
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz"};
    ifstream archivoProducto;
    archivoProducto.open("Productos.bin", ios::binary);
    ifstream archivoDetalleFacturacion;
    Producto producto;
    FacturacionDetalle factura_detalle;
    int id_producto;
    int mayor = 0;
    vector<int> vector_cantidad_ventas;
    vector<Producto> vector_productos;
    if(archivoProducto.good()){
        while(archivoProducto.read((char*)&producto, sizeof(Producto))){
            if(!producto.eliminado){
                id_producto = producto.id_producto;
                int contador_ventas = 0;
                archivoDetalleFacturacion.open("FacturacionDetalles.bin", ios::binary);
                while(archivoDetalleFacturacion.read((char*)&factura_detalle, sizeof(FacturacionDetalle))){
                    if(!factura_detalle.eliminado){
                        if(factura_detalle.id_producto == id_producto){
                            contador_ventas+=factura_detalle.cantidad;
                        }

                    }

                }
                archivoDetalleFacturacion.close();
                vector_cantidad_ventas.push_back(contador_ventas);
                vector_productos.push_back(producto);
                if(contador_ventas > mayor){
                    mayor = contador_ventas;
                }
            }
        }
        
        
        for(int i = 0; i < vector_cantidad_ventas.size(); i++){
            
            if(vector_cantidad_ventas[i] == mayor){
                cout << "---------------------------------------" << endl;
                cout << "ID_producto: " << vector_productos[i].id_producto << endl;
                cout << "ID_proveedor: " << vector_productos[i].id_proveedor << endl;
                cout << "Nombre: " << vector_productos[i].nombre << endl;
                if (vector_productos[i].tipo >= 1 && vector_productos[i].tipo <= tipo_productos.size()) {
                    cout << "Tipo: " << tipo_productos[vector_productos[i].tipo - 1] << endl;
                } else {
                    cout << "Tipo: ERROR/DESCONOCIDO (" << vector_productos[i].tipo << ")" << endl;
                }
                cout << "Marca: " << vector_productos[i].marca << endl;
                cout << "Distribuidor: " << vector_productos[i].distribuidor << endl;
                cout << "Cantidad en inventario: " << vector_productos[i].cantidad << endl;
                cout << "Precio de compra: " << vector_productos[i].precio_Compra << endl;
                cout << "Precio de venta: " << vector_productos[i].precio_Venta << endl;
                cout << "=========================" << endl;
                cout << "TOTAL VENDIDO: " << vector_cantidad_ventas[i] << endl;
                cout << "TOTAL GANADO: " << vector_cantidad_ventas[i] * vector_productos[i].precio_Venta << endl;
                cout << "=========================" << endl;
            }
        }
    }
    archivoProducto.close();
}
void MostrarProductosMenosVendidos() 
{
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin",
                                     "Pintura", "Decoracion", "Hogar y limpieza",
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz"};
    ifstream archivoProducto;
    archivoProducto.open("Productos.bin", ios::binary);
    ifstream archivoDetalleFacturacion;
    Producto producto;
    FacturacionDetalle factura_detalle;
    int id_producto;
    int menor = 100000; //Valor Exageradamente alto
    vector<int> vector_cantidad_ventas;
    vector<Producto> vector_productos;
    if(archivoProducto.good()){
        while(archivoProducto.read((char*)&producto, sizeof(Producto))){
            if(!producto.eliminado){
                id_producto = producto.id_producto;
                int contador_ventas = 0;
                archivoDetalleFacturacion.open("FacturacionDetalles.bin", ios::binary);
                while(archivoDetalleFacturacion.read((char*)&factura_detalle, sizeof(FacturacionDetalle))){
                    if(!factura_detalle.eliminado){
                        if(factura_detalle.id_producto == id_producto){
                            contador_ventas+=factura_detalle.cantidad;
                        }

                    }

                }
                archivoDetalleFacturacion.close();
                vector_cantidad_ventas.push_back(contador_ventas);
                vector_productos.push_back(producto);
                if(contador_ventas < menor){
                    menor = contador_ventas;
                }
            }
        }
        for(int i = 0; i < vector_cantidad_ventas.size(); i++){
            
            if(vector_cantidad_ventas[i] == menor){
                cout << "---------------------------------------" << endl;
                cout << "ID_producto: " << vector_productos[i].id_producto << endl;
                cout << "ID_proveedor: " << vector_productos[i].id_proveedor << endl;
                cout << "Nombre: " << vector_productos[i].nombre << endl;
                if (vector_productos[i].tipo >= 1 && vector_productos[i].tipo <= tipo_productos.size()) {
                    cout << "Tipo: " << tipo_productos[vector_productos[i].tipo - 1] << endl;
                } else {
                    cout << "Tipo: ERROR/DESCONOCIDO (" << vector_productos[i].tipo << ")" << endl;
                }
                cout << "Marca: " << vector_productos[i].marca << endl;
                cout << "Distribuidor: " << vector_productos[i].distribuidor << endl;
                cout << "Cantidad en inventario: " << vector_productos[i].cantidad << endl;
                cout << "Precio de compra: " << vector_productos[i].precio_Compra << endl;
                cout << "Precio de venta: " << vector_productos[i].precio_Venta << endl;
                cout << "=========================" << endl;
                cout << "TOTAL VENDIDO: " << vector_cantidad_ventas[i] << endl;
                cout << "TOTAL GANADO: " << vector_cantidad_ventas[i] * vector_productos[i].precio_Venta << endl;
                cout << "=========================" << endl;
                
            }
        }
    }
}