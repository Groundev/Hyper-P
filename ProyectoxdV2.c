#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100 // Máximo de productos por factura
#define max_cajas 5 // Máximo de cajas

typedef struct {
    char nombre_cliente[20];
    char apellido_cliente[20];
    int cedula_cliente;
    int telefono_cliente;
    char direccion_cliente[50];
} Cliente;

Cliente* clientes = NULL; // Puntero a array dinámico de clientes
int numCliente = 0;       // Número actual de clientes

typedef struct {
    char codigo[10];
    char descripcion[50];
    int cantidad;
    float precio_unitario;
    float precio_total;
} ProductoFactura;

typedef struct {
    int numero_factura;
    char fecha[15];  // Formato "DD/MM/AAAA"
    Cliente cliente;
    ProductoFactura productos[MAX_PRODUCTOS];
    int total_productos;
    float subtotal;
    float iva;  // Porcentaje aplicado
    float total_pagar;
    int caja_asignada;
} Factura;

Factura* facturas = NULL; // Array dinámico de facturas
int numFacturas = 0;      // Número actual de facturas

typedef struct {
    char codigo[10];
    char nombre[50];
    int cantidad;
    float precio_bs;
    float precio_usd;
    float precio_cop;
    float precio_eur;
} Producto;

Producto* productos = NULL; // Puntero a array dinámico de productos
int numProductos = 0;

typedef struct {
    int nro_trabajador;
    char nombre[20];
    char apellido[20];
    int cedula;
    int tlf;
    char direccion[50];
} Trabajador;

Trabajador* trabajadores = NULL; // Puntero a array dinámico de trabajadores
int numTrabajadores = 0;       // Número actual de trabajadores

enum num_cajas {
    Caja_1 = 1,
    Caja_2,
    Caja_3,
    Caja_4,
    Caja_5,
};

typedef struct {
    enum num_cajas nro_caja;
    Trabajador* nro_trabajador;
    float total_BS;
    float total_USD;
    float total_COP;
    float total_EUR;
    int facturados;
} Caja;

Caja cajas[max_cajas]; //Array que contiene los datos de las cajas

//Funciones para caja
void inicializarCajas() {
    for (int i = 0; i < max_cajas; i++) {
        cajas[i].nro_caja = i + 1;
        cajas[i].nro_trabajador = NULL;  // No se asigna un trabajador aún
        cajas[i].total_BS = 0.0;
        cajas[i].total_USD = 0.0;
        cajas[i].total_COP = 0.0;
        cajas[i].total_EUR = 0.0;
        cajas[i].facturados = 0;
    }
}

void asignarTrabajadorACaja() {
    int cajaNumero, idTrabajador;
    printf("Ingrese el número de caja (1-5): ");
    scanf("%d", &cajaNumero);
    
    if (cajaNumero < 1 || cajaNumero > max_cajas) {
        printf("Número de caja inválido.\n");
        return;
    }
    
    printf("Ingrese el ID del trabajador a asignar: ");
    scanf("%d", &idTrabajador);

    Trabajador* trabajador = NULL;
    for (int i = 0; i < numTrabajadores; i++) {
        if (trabajadores[i].nro_trabajador == idTrabajador) {
            trabajador = &trabajadores[i];
            break;
        }
    }
    
    if (trabajador == NULL) {
        printf("Trabajador no encontrado.\n");
        return;
    }

    cajas[cajaNumero - 1].nro_trabajador = trabajador;
    printf("Trabajador %s %s asignado a la caja %d.\n", trabajador->nombre, trabajador->apellido, cajaNumero);
}

void mostrarCajas() {
    for (int i = 0; i < max_cajas; i++) {
        printf("Caja %d:\n", cajas[i].nro_caja);
        if (cajas[i].nro_trabajador != NULL) {
            printf("Trabajador: %s %s\n", cajas[i].nro_trabajador->nombre, cajas[i].nro_trabajador->apellido);
            printf("Cedula: %d\n", cajas[i].nro_trabajador->cedula);
            printf("Telefono: %d\n", cajas[i].nro_trabajador->tlf);
            printf("Direccion: %s\n", cajas[i].nro_trabajador->direccion);
        } else {
            printf("Trabajador: No asignado\n");
        }
        printf("Total BS: %.2f\n", cajas[i].total_BS);
        printf("Total USD: %.2f\n", cajas[i].total_USD);
        printf("Total COP: %.2f\n", cajas[i].total_COP);
        printf("Total EUR: %.2f\n", cajas[i].total_EUR);
        printf("Facturados: %d\n", cajas[i].facturados);
        printf("\n");
    }
}

void menu_cajas() {
    int opcion;
    do {
        printf("\n1. Inicializar caja\n2. Asignar Trabajador\n3. Mostrar cajas\n4. Salir\n");
        printf("Seleccione una opción: \n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: inicializarCajas(); break;
            case 2: asignarTrabajadorACaja(); break;
            case 3: mostrarCajas(); break;
            case 4: printf("Saliendo...\n"); break;
        default: printf("Opción no válida\n");
        }
    } while(opcion != 4);
}
//Funciones para cajas

//Funciones para trabajadores
void agregarTrabajador(){
    int max = 0;
    printf("Por favor ingrese cuantos Trabajadores desea añadir.\n");
    scanf("%d", &max);

    // Realocamos memoria para los nuevos trabajadores
    trabajadores = realloc(trabajadores, (numTrabajadores + max) * sizeof(Trabajador));

    if (trabajadores == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    for(int i = 0; i < max; i++){
        
        printf("Ingrese el ID de trabajador\n");
        trabajadores[numTrabajadores + i].nro_trabajador = numTrabajadores + i + 1;
        
        printf("Ingrese nombre\n");
        scanf("%19s", trabajadores[numTrabajadores + i].nombre);

        printf("Ingrese apellido\n");
        scanf("%19s", trabajadores[numTrabajadores + i].apellido);

        printf("Ingrese cedula\n");
        scanf("%d", &trabajadores[numTrabajadores + i].cedula);

        printf("Ingrese telefono\n");
        scanf("%d", &trabajadores[numTrabajadores + i].tlf);

        printf("Ingrese direccion\n");
        scanf("%49s", trabajadores[numTrabajadores + i].direccion);

    }

    numTrabajadores += max; // Actualizamos el número total de trabajadores
}

void modificarTrabajador() {
    int seleccion = 0;
    printf("Ingrese el ID del trabajador que desea modificar:\n");
    scanf("%d", &seleccion);

    for(int i = 0; i < numTrabajadores; i++) {
        if(trabajadores[i].nro_trabajador == seleccion){
            printf("Trabajador encontrado. Ingrese los nuevos datos.\n");

            printf("Ingrese nombre\n");
            scanf("%19s", trabajadores[i].nombre);

            printf("Ingrese apellido\n");
            scanf("%19s", trabajadores[i].apellido);

            printf("Ingrese cedula\n");
            scanf("%d", &trabajadores[i].cedula);

            printf("Ingrese telefono\n");
            scanf("%d", &trabajadores[i].tlf);

            printf("Ingrese direccion\n");
            scanf("%49s", trabajadores[i].direccion);

            printf("Trabajador modificado exitosamente.\n");
            return;
        }
    }
    printf("Trabajador con ID %d no encontrado.\n", seleccion);
}

void eliminarTrabajador() {
    int seleccion = 0;
    printf("Ingrese el ID del trabajador que desea eliminar:\n");
    scanf("%d", &seleccion);

    for(int i = 0; i < numTrabajadores; i++) {
        if(trabajadores[i].nro_trabajador == seleccion) {
            // Eliminamos el producto moviendo los siguientes productos una posición hacia adelante
            for(int j = i; j < numTrabajadores - 1; j++) {
                trabajadores[j] = trabajadores[j + 1];
            }
            numTrabajadores--;
            trabajadores = realloc(trabajadores, numTrabajadores * sizeof(Trabajador));
            printf("Trabajador eliminado exitosamente.\n");
            return;
        }
    }
    printf("Trabajador con numero %d no encontrado.\n", seleccion);
}

void mostrarTrabajador() {
    if(numTrabajadores == 0){
        printf("no se encuentran trabajadores registrados.\n");
    }else{
        printf("Lista de trabajadores:\n");
        for(int i = 0; i < numTrabajadores; i++) {
            printf("ID trabajador %d:\n", trabajadores[i].nro_trabajador);
            printf("Nombre: %s\n", trabajadores[i].nombre);
            printf("Apellido: %s\n", trabajadores[i].apellido);
            printf("Cedula: %d\n", trabajadores[i].cedula);
            printf("Telefono: %d\n", trabajadores[i].tlf);
            printf("Direccion: %s\n", trabajadores[i].direccion);
            printf("\n");
        }
    }
}

void menu_trabajadores() {
    int opcion;
    do {
        printf("\n1. Agregar Trabajador\n2. Modificar Trabajador\n3. Eliminar Trabajador\n4. Mostrar Trabajador\n5. Salir\n");
        printf("Seleccione una opción: \n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarTrabajador(); break;
            case 2: modificarTrabajador(); break;
            case 3: eliminarTrabajador(); break;
            case 4: mostrarTrabajador(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opción no válida\n");
        }
    } while(opcion != 5);
}   
//Funciones para trabajadores

//Funciones de factura
void agregarProductoFactura(Factura* factura) {
    if (factura->total_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos a la factura.\n");
        return;
    }

    char codigoProducto[10];
    printf("Ingrese el código del producto: ");
    scanf("%9s", codigoProducto);

    // Buscar el producto por código
    Producto* producto = NULL;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].codigo, codigoProducto) == 0) {
            producto = &productos[i];
            break;
        }
    }

    if (producto == NULL) {
        printf("Producto con código %s no encontrado.\n");
        return;
    }

    int cantidad;
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &cantidad);

    if (cantidad > producto->cantidad) {
        printf("Cantidad insuficiente en inventario.\n");
        return;
    }

    ProductoFactura productoFactura;
    strcpy(productoFactura.codigo, producto->codigo);
    strcpy(productoFactura.descripcion, producto->nombre);
    productoFactura.cantidad = cantidad;
    productoFactura.precio_unitario = producto->precio_usd; // Puedes cambiar la moneda si es necesario
    productoFactura.precio_total = productoFactura.cantidad * productoFactura.precio_unitario;

    producto->cantidad -= cantidad; // Actualizar la cantidad en inventario

    factura->productos[factura->total_productos] = productoFactura;
    factura->total_productos++;
    factura->subtotal += productoFactura.precio_total;
    factura->total_pagar = factura->subtotal + factura->iva; // Actualizar el total a pagar

    printf("Producto agregado a la factura.\n");
}

void modificarProductoFactura() {
    int numeroFactura;
    printf("Ingrese el número de la factura a modificar: ");
    scanf("%d", &numeroFactura);

    Factura* factura = NULL;
    for (int i = 0; i < numFacturas; i++) {
        if (facturas[i].numero_factura == numeroFactura) {
            factura = &facturas[i];
            break;
        }
    }

    if (factura == NULL) {
        printf("Factura con número %d no encontrada.\n", numeroFactura);
        return;
    }

    char codigoProducto[10];
    printf("Ingrese el código del producto a modificar: ");
    scanf("%9s", codigoProducto);

    ProductoFactura* productoFactura = NULL;
    for (int i = 0; i < factura->total_productos; i++) {
        if (strcmp(factura->productos[i].codigo, codigoProducto) == 0) {
            productoFactura = &factura->productos[i];
            break;
        }
    }

    if (productoFactura == NULL) {
        printf("Producto con código %s no encontrado en la factura.\n", codigoProducto);
        return;
    }

    int nuevaCantidad;
    printf("Ingrese la nueva cantidad del producto: ");
    scanf("%d", &nuevaCantidad);

    // Actualizar los datos del producto en la factura
    float diferenciaPrecio = (nuevaCantidad - productoFactura->cantidad) * productoFactura->precio_unitario;
    productoFactura->cantidad = nuevaCantidad;
    productoFactura->precio_total = productoFactura->cantidad * productoFactura->precio_unitario;
    factura->subtotal += diferenciaPrecio;
    factura->total_pagar = factura->subtotal + factura->iva; // Actualizar el total a pagar

    printf("Producto modificado en la factura.\n");
}

void eliminarProductoFactura() {
    int numeroFactura;
    printf("Ingrese el número de la factura a modificar: ");
    scanf("%d", &numeroFactura);

    Factura* factura = NULL;
    for (int i = 0; i < numFacturas; i++) {
        if (facturas[i].numero_factura == numeroFactura) {
            factura = &facturas[i];
            break;
        }
    }

    if (factura == NULL) {
        printf("Factura con número %d no encontrada.\n", numeroFactura);
        return;
    }

    char codigoProducto[10];
    printf("Ingrese el código del producto a eliminar: ");
    scanf("%9s", codigoProducto);

    int index = -1;
    for (int i = 0; i < factura->total_productos; i++) {
        if (strcmp(factura->productos[i].codigo, codigoProducto) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Producto con código %s no encontrado en la factura.\n", codigoProducto);
        return;
    }

    ProductoFactura productoFactura = factura->productos[index];
    factura->subtotal -= productoFactura.precio_total;
    factura->total_pagar = factura->subtotal + factura->iva; // Actualizar el total a pagar

    // Desplazar los productos en el array para eliminar el producto
    for (int i = index; i < factura->total_productos - 1; i++) {
        factura->productos[i] = factura->productos[i + 1];
    }

    factura->total_productos--;

    printf("Producto eliminado de la factura.\n");
}

void mostrarProductosFactura(Factura* factura) {
    printf("Productos en la factura:\n");
    for (int i = 0; i < factura->total_productos; i++) {
        printf("Código: %s\n", factura->productos[i].codigo);
        printf("Descripción: %s\n", factura->productos[i].descripcion);
        printf("Cantidad: %d\n", factura->productos[i].cantidad);
        printf("Precio unitario: %.2f\n", factura->productos[i].precio_unitario);
        printf("Precio total: %.2f\n", factura->productos[i].precio_total);
        printf("\n");
    }
}

void agregarFactura() {
    int cajaNumero;
    printf("Ingrese el número de caja (1-5): ");
    scanf("%d", &cajaNumero);
    
    if (cajaNumero < 1 || cajaNumero > max_cajas || cajas[cajaNumero - 1].nro_trabajador == NULL) {
        printf("Caja inválida o sin trabajador asignado.\n");
        return;
    }

    facturas = realloc(facturas, (numFacturas + 1) * sizeof(Factura));
    if (facturas == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    Factura nuevaFactura;
    nuevaFactura.numero_factura = numFacturas + 1;
    nuevaFactura.total_productos = 0;
    nuevaFactura.subtotal = 0.0;
    nuevaFactura.iva = 0.0;
    nuevaFactura.total_pagar = 0.0;
    nuevaFactura.caja_asignada = cajaNumero;

    printf("Ingrese la fecha de la factura (DD/MM/AAAA): ");
    scanf("%14s", nuevaFactura.fecha);
    
    printf("Ingrese la cédula del cliente: ");
    int clienteCedula;
    scanf("%d", &clienteCedula);

    Cliente* cliente = NULL;
    for (int i = 0; i < numCliente; i++) {
        if (clientes[i].cedula_cliente == clienteCedula) {
            cliente = &clientes[i];
            break;
        }
    }
    if (cliente == NULL) {
        printf("Cliente no encontrado.\n");
        return;
    }
    nuevaFactura.cliente = *cliente;

    char continuar;
    do {
        agregarProductoFactura(&nuevaFactura);
        printf("¿Desea agregar otro producto a la factura? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    nuevaFactura.iva = nuevaFactura.subtotal * 0.16;
    nuevaFactura.total_pagar = nuevaFactura.subtotal + nuevaFactura.iva;

    cajas[cajaNumero - 1].total_USD += nuevaFactura.total_pagar;
    cajas[cajaNumero - 1].total_BS += nuevaFactura.total_pagar * 63.50;
    cajas[cajaNumero - 1].total_COP += nuevaFactura.total_pagar * 4000;
    cajas[cajaNumero - 1].total_BS += nuevaFactura.total_pagar * 0.96;
    cajas[cajaNumero - 1].facturados++;

    facturas[numFacturas] = nuevaFactura;
    numFacturas++;
    printf("Factura agregada a la caja %d.\n", cajaNumero);
}

void mostrarFacturas() {
    printf("Lista de facturas:\n");
    for (int i = 0; i < numFacturas; i++) {
        printf("Número de factura: %d\n", facturas[i].numero_factura);
        printf("Fecha: %s\n", facturas[i].fecha);
        printf("Cliente: %s %s\n", facturas[i].cliente.nombre_cliente, facturas[i].cliente.apellido_cliente);
        mostrarProductosFactura(&facturas[i]); // Pasar la factura específica a la función
        printf("Total de productos: %d\n", facturas[i].total_productos);
        printf("Subtotal: %.2f\n", facturas[i].subtotal);
        printf("IVA: %.2f\n", facturas[i].iva);
        printf("Total a pagar: %.2f\n", facturas[i].total_pagar);
        printf("\n");
    }
}

void eliminarFactura() {
    int numeroFactura;
    printf("Ingrese el número de la factura a eliminar: ");
    scanf("%d", &numeroFactura);

    int index = -1;
    for (int i = 0; i < numFacturas; i++) {
        if (facturas[i].numero_factura == numeroFactura) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Factura con número %d no encontrada.\n", numeroFactura);
        return;
    }

    // Restaurar las cantidades de los productos eliminados al inventario
    for (int i = 0; i < facturas[index].total_productos; i++) {
        ProductoFactura productoFactura = facturas[index].productos[i];
        for (int j = 0; j < numProductos; j++) {
            if (strcmp(productos[j].codigo, productoFactura.codigo) == 0) {
                productos[j].cantidad += productoFactura.cantidad;
                break;
            }
        }
    }

    // Desplazar las facturas en el array para eliminar la factura
    for (int i = index; i < numFacturas - 1; i++) {
        facturas[i] = facturas[i + 1];
    }

    numFacturas--;
    facturas = realloc(facturas, numFacturas * sizeof(Factura));
    if (facturas == NULL && numFacturas > 0) {
        printf("Error al reasignar memoria\n");
        exit(1);
    }

    printf("Factura eliminada.\n");
}

void modificarFactura() {
    int numeroFactura;
    printf("Ingrese el número de la factura a modificar: ");
    scanf("%d", &numeroFactura);

    Factura* factura = NULL;
    for (int i = 0; i < numFacturas; i++) {
        if (facturas[i].numero_factura == numeroFactura) {
            factura = &facturas[i];
            break;
        }
    }

    if (factura == NULL) {
        printf("Factura con número %d no encontrada.\n", numeroFactura);
        return;
    }

    printf("Ingrese la nueva fecha de la factura (DD/MM/AAAA): ");
    scanf("%14s", factura->fecha);
    printf("Ingrese la nueva cédula del cliente: ");
    int clienteCedula;
    scanf("%d", &clienteCedula);

    // Buscar el cliente por cédula
    Cliente* cliente = NULL;
    for (int i = 0; i < numCliente; i++) {
        if (clientes[i].cedula_cliente == clienteCedula) {
            cliente = &clientes[i];
            break;
        }
    }

    if (cliente == NULL) {
        printf("Cliente con cédula %d no encontrado.\n", clienteCedula);
        return;
    }

    factura->cliente = *cliente;  // Asignar cliente desde el array de clientes

    printf("Factura modificada. Puede agregar o eliminar productos usando las opciones correspondientes.\n");
}

void menu_fs() {
    int opcion;
    do {
        printf("\n1. Agregar Factura\n2. Modificar Factura\n3. Eliminar Factura\n4. Mostrar Facturas\n5. Modificar Producto Facturado\n6. Eliminar Producto Facturado\n7. Salir\n");
        printf("Seleccione una opción: \n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarFactura(); break;
            case 2: modificarFactura(); break;
            case 3: eliminarFactura(); break;
            case 4: mostrarFacturas(); break;
            case 5: modificarProductoFactura(); break;
            case 6: eliminarProductoFactura(); break;
            case 7: printf("Saliendo...\n"); break;
            default: printf("Opción no válida\n");
        }
    } while(opcion != 7);

    // Liberar memoria antes de salir
    free(facturas);
    free(clientes);
    free(productos);
}
//Funciones de factura

//Funciones de productos
void agregarProducto(){
    int max = 0;
    printf("Por favor ingrese cuantos productos desea añadir.\n");
    scanf("%d", &max);

    // Realocamos memoria para los nuevos productos
    productos = realloc(productos, (numProductos + max) * sizeof(Producto));

    if (productos == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    for(int i = 0; i < max; i++){
        printf("Ingrese nombre\n");
        scanf("%49s", productos[numProductos + i].nombre);

        printf("Ingrese codigo\n");
        scanf("%10s", productos[numProductos + i].codigo);

        printf("Ingrese cantidad\n");
        scanf("%d", &productos[numProductos + i].cantidad);

        printf("Ingrese precio en Dolares\n");
        scanf("%f", &productos[numProductos + i].precio_usd);

        printf("Ingrese precio en Bolivares\n");
        productos[numProductos + i].precio_bs = productos[numProductos + i].precio_usd * 63.50;

        printf("Ingrese precio en Pesos\n");
        productos[numProductos + i].precio_cop = productos[numProductos + i].precio_usd * 4000;

        printf("Ingrese precio en Euros\n");
        productos[numProductos + i].precio_eur = productos[numProductos + i].precio_usd * 0.96;
    }

    numProductos += max; // Actualizamos el número total de productos
}

void eliminarProducto(){
    char seleccion[10];
    printf("Ingrese el código del producto que desea eliminar:\n");
    scanf("%9s", seleccion);

    for(int i = 0; i < numProductos; i++) {
        if(strcmp(productos[i].codigo, seleccion) == 0) {
            // Eliminamos el producto moviendo los siguientes productos una posición hacia adelante
            for(int j = i; j < numProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            numProductos--;
            productos = realloc(productos, numProductos * sizeof(Producto));
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto con código %s no encontrado.\n", seleccion);
}

void modificarProducto(){
    char seleccion[10];
    printf("Ingrese el código del producto que desea modificar:\n");
    scanf("%9s", seleccion);

    for(int i = 0; i < numProductos; i++) {
        if(strcmp(productos[i].codigo, seleccion) == 0) {
            printf("Producto encontrado. Ingrese los nuevos datos.\n");

            printf("Ingrese nombre\n");
            scanf("%49s", productos[i].nombre);

            printf("Ingrese cantidad\n");
            scanf("%d", &productos[i].cantidad);

            printf("Ingrese precio en Dolares\n");
            scanf("%f", &productos[numProductos + i].precio_usd);
    
            printf("Ingrese precio en Bolivares\n");
            productos[numProductos + i].precio_bs = productos[numProductos + i].precio_usd * 63.50;
    
            printf("Ingrese precio en Pesos\n");
            productos[numProductos + i].precio_cop = productos[numProductos + i].precio_usd * 4000;
    
            printf("Ingrese precio en Euros\n");
            productos[numProductos + i].precio_eur = productos[numProductos + i].precio_usd * 0.96;

            printf("Producto modificado exitosamente.\n");
            return;
        }
    }
    printf("Producto con código %s no encontrado.\n", seleccion);
}

void mostrarProductos(){
    if(numProductos == 0){
        printf("no se encuentran productos registrados.");
    }else{
        printf("Lista de productos:\n");
        for(int i = 0; i < numProductos; i++) {
            printf("Producto %d:\n", i + 1);
            printf("Nombre: %s\n", productos[i].nombre);
            printf("Codigo: %s\n", productos[i].codigo);
            printf("Cantidad: %d\n", productos[i].cantidad);
            printf("Precio en Dolares: %.2f\n", productos[i].precio_usd);
            printf("Precio en Bolivares: %.2f\n", productos[i].precio_bs);
            printf("Precio en Pesos: %.2f\n", productos[i].precio_cop);
            printf("Precio en Euros: %.2f\n", productos[i].precio_eur);
            printf("\n");
        }
    }
}

void menu_productos(){
    // Aquí puedes llamar a las funciones agregarProducto, modificarProducto y eliminarProducto para probar
    int opcion;
    do {
        printf("\n1. Agregar Producto\n2. Modificar Producto\n3. Eliminar Producto\n4. Mostrar Productos\n5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarProducto(); break;
            case 2: modificarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: mostrarProductos(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opción no válida\n");
        }
    } while(opcion != 5);
}
//Funciones de productos

//Funciones de Clientes
void agregarCliente(){
    int max = 0;
    printf("Por favor ingrese los clientes atendidos.\n");
    scanf("%d", &max);

    // Realocamos memoria para los nuevos productos
    clientes = realloc(clientes, (numCliente + max) * sizeof(Cliente));

    if (clientes == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    for(int i = 0; i < max; i++){
        printf("Ingrese nombre\n");
        scanf("%19s", clientes[numCliente + i].nombre_cliente);

        printf("Ingrese apellido\n");
        scanf("%19s", clientes[numCliente + i].apellido_cliente);

        printf("Ingrese cedula\n");
        scanf("%d", &clientes[numCliente + i].cedula_cliente);

        printf("Ingrese el numero telefonico\n");
        scanf("%d", &clientes[numCliente + i].telefono_cliente);

        printf("Ingrese la direccion del cliente\n");
        scanf("%49s", clientes[numCliente + i].direccion_cliente);

    }

    numCliente += max; // Actualizamos el número total de clientes
}

void eliminarCliente(){
    int seleccion;
    printf("Ingrese la cedula del cliente que desea eliminar:\n");
    scanf("%d", &seleccion);

    for(int i = 0; i < numCliente; i++) {
        if(clientes[i].cedula_cliente == seleccion) {
            // Eliminamos el cliente moviendo los siguientes productos una posición hacia adelante
            for(int j = i; j < numCliente - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            numCliente--;
            clientes = realloc(clientes, numCliente * sizeof(Cliente));
            printf("Cliente eliminado exitosamente.\n");
            return;
        }
    }
    printf("El cliente de cedula %d no encontrado.\n", seleccion);
}

void modificarCliente(){
    int seleccion;
    printf("Ingrese la cedula del cliente que desea modificar:\n");
    scanf("%d", &seleccion);

    for(int i = 0; i < numCliente; i++) {
        if(clientes[i].cedula_cliente == seleccion) {
            printf("Cliente encontrado. Ingrese los nuevos datos.\n");

        printf("Ingrese nombre\n");
        scanf("%19s", clientes[numCliente + i].nombre_cliente);

        printf("Ingrese apellido\n");
        scanf("%19s", clientes[numCliente + i].apellido_cliente);

        printf("Ingrese cedula\n");
        scanf("%d", &clientes[numCliente + i].cedula_cliente);

        printf("Ingrese el numero telefonico\n");
        scanf("%d", &clientes[numCliente + i].telefono_cliente);

        printf("Ingrese la direccion del cliente\n");
        scanf("%49s", clientes[numCliente + i].direccion_cliente);

        printf("Cliente modificado exitosamente.\n");
        return;
        
        }
    }
    printf("El cliente de cedula %d no encontrado.\n", seleccion);
}

void mostrarClientes(){
    if(numCliente== 0){
        printf("no se encuentran a los clientes registrados.");
    }else{
        printf("Lista de clientes:\n");
        for(int i = 0; i < numCliente; i++) {
        printf("nombre: %s\n", clientes[i].nombre_cliente);
        printf("apellido: %s\n", clientes[i].apellido_cliente);
        printf("cedula: %d\n", clientes[i].cedula_cliente);
        printf("numero telefonico: %d\n", clientes[i].telefono_cliente);
	    printf("direccion del cliente %s\n", clientes[i].direccion_cliente);

        }
    }
}

void menu_clientes(){
    int opcion;
    do {
        printf("\n1. Agregar Cliente\n2. Modificar Cliente\n3. Eliminar Cliente\n4. Mostrar Cliente\n5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarCliente(); break;
            case 2: modificarCliente(); break;
            case 3: eliminarCliente(); break;
            case 4: mostrarClientes(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opción no válida\n");
        }
    } while(opcion != 5);

}
//Funciones de Clientes

//Funciones Reportes
void mostrarUltimas10Facturas() {
    if (numFacturas == 0) {
        printf("No hay facturas registradas.\n");
        return;
    }
    
    int start = numFacturas > 10 ? numFacturas - 10 : 0;
    printf("Últimas 10 facturas emitidas:\n");
    for (int i = start; i < numFacturas; i++) {
        printf("Factura #%d\n", facturas[i].numero_factura);
        printf("Fecha: %s\n", facturas[i].fecha);
        printf("Cliente: %s %s\n", facturas[i].cliente.nombre_cliente, facturas[i].cliente.apellido_cliente);
        printf("Total a pagar: %.2f\n", facturas[i].total_pagar);
        printf("\n");
    }
}

ProductoFactura* productoMasVendido() {
    if (numFacturas == 0) {
        printf("No hay facturas registradas.\n");
        return NULL;
    }

    int maxCantidad = 0;
    ProductoFactura* productoMasVendido = NULL;

    for (int i = 0; i < numFacturas; i++) {
        for (int j = 0; j < facturas[i].total_productos; j++) {
            if (facturas[i].productos[j].cantidad > maxCantidad) {
                maxCantidad = facturas[i].productos[j].cantidad;
                productoMasVendido = &facturas[i].productos[j];
            }
        }
    }

    return productoMasVendido;
}

void mostrarProductoMasVendido() {
    ProductoFactura* producto = productoMasVendido();
    if (producto != NULL) {
        printf("Producto más vendido:\n");
        printf("Código: %s\n", producto->codigo);
        printf("Descripción: %s\n", producto->descripcion);
        printf("Cantidad vendida: %d\n", producto->cantidad);
        printf("Precio total: %.2f\n", producto->precio_total);
    }
}

void menu_reportes() {
    int opcion;
    do {
        printf("\n--- Menu de Reportes ---\n");
        printf("1. Últimas 10 Facturas\n");
        printf("2. Producto Más Vendido\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                mostrarUltimas10Facturas();
                break;
            case 2:
                mostrarProductoMasVendido();
                break;
                
            case 3:
                printf("Saliendo del menú de reportes...\n");
                break;

            default:
                printf("Opción no válida\n");
        }
        
    } while (opcion != 3);
}
//Funciones Reportes

//Funciones Ventas
double ventasDiarias(const char *fecha) {
    double total = 0.0;
    for (int i = 0; i < numFacturas; i++) {
        if (strcmp(facturas[i].fecha, fecha) == 0) {
            total += facturas[i].total_pagar;
        }
    }
    return total;
}

double ventasMensuales(int mes, int anio) {
    double total = 0.0;
    int dia, mesFactura, anioFactura;
    for (int i = 0; i < numFacturas; i++) {
        sscanf(facturas[i].fecha, "%d/%d/%d", &dia, &mesFactura, &anioFactura);
        if (mesFactura == mes && anioFactura == anio) {
            total += facturas[i].total_pagar;
        }
    }
    return total;
}

double ventasTotales() {
    double total = 0.0;
    for (int i = 0; i < numFacturas; i++) {
        total += facturas[i].total_pagar;
    }
    return total;
}

void ventasDiariasPorCaja(const char *fecha) {
    for (int i = 0; i < max_cajas; i++) {
        double total = 0.0;
        for (int j = 0; j < numFacturas; j++) {
            if (facturas[j].caja_asignada == cajas[i].nro_caja &&
                strcmp(facturas[j].fecha, fecha) == 0) {
                total += facturas[j].total_pagar;
            }
        }
        printf("Ventas diarias para Caja %d: %.2f\n", cajas[i].nro_caja, total);
    }
}

void ventasMensualesPorCaja(int mes, int anio) {
    int dia, mesFactura, anioFactura;
    for (int i = 0; i < max_cajas; i++) {
        double total = 0.0;
        for (int j = 0; j < numFacturas; j++) {
            if (facturas[j].caja_asignada == cajas[i].nro_caja) {
                sscanf(facturas[j].fecha, "%d/%d/%d", &dia, &mesFactura, &anioFactura);
                if (mesFactura == mes && anioFactura == anio) {
                    total += facturas[j].total_pagar;
                }
            }
        }
        printf("Ventas mensuales para Caja %d: %.2f\n", cajas[i].nro_caja, total);
    }
}

void menu_ventas() {
    int opcion;
    do {
        printf("\n--- Menu de Ventas ---\n");
        printf("1. Ventas Diarias\n");
        printf("2. Ventas Mensuales\n");
        printf("3. Ventas Totales\n");
        printf("4. Ventas Diarias por Caja\n");
        printf("5. Ventas Mensuales por Caja\n");
        printf("6. Reportes\n");  // Opción para acceder al menú de reportes
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1: {
                char fecha[15];
                printf("Ingrese la fecha (DD/MM/AAAA): ");
                scanf("%14s", fecha);
                double total = ventasDiarias(fecha);
                printf("Ventas del día %s: %.2f\n", fecha, total);
                break;
            }
            case 2: {
                int mes, anio;
                printf("Ingrese el mes (1-12): ");
                scanf("%d", &mes);
                printf("Ingrese el año: ");
                scanf("%d", &anio);
                double total = ventasMensuales(mes, anio);
                printf("Ventas del mes %d/%d: %.2f\n", mes, anio, total);
                break;
            }
            case 3: {
                double total = ventasTotales();
                printf("Ventas totales: %.2f\n", total);
                break;
            }
            case 4: {
                char fecha[15];
                printf("Ingrese la fecha (DD/MM/AAAA): ");
                scanf("%14s", fecha);
                ventasDiariasPorCaja(fecha);
                break;
            }
            case 5: {
                int mes, anio;
                printf("Ingrese el mes (1-12): ");
                scanf("%d", &mes);
                printf("Ingrese el año: ");
                scanf("%d", &anio);
                ventasMensualesPorCaja(mes, anio);
                break;
            }
            case 6: {
                menu_reportes();  // Llamar al menú de reportes
                break;
            }
            case 7:
                printf("Saliendo del menú de ventas...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
        
    } while (opcion != 7);
}
//Funciones Ventas

//Funcion de menus principales
void menu_admin(){
    int opcion;
    do {
        printf ("\n --- Menu de Admnistracion --- \n");
        printf("\n1. Cajas\n2. Trabajadores\n3. Productos\n4. Ventas\n5. Cerrar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menu_cajas(); break;
            case 2: menu_trabajadores(); break;
            case 3: menu_productos(); break;
            case 4: menu_ventas(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida\n");
        }
    } while(opcion != 5);
}

 void menu_ctrlV(){
 int opcion;
    do {
        printf ("\n --- Menu de Ventas --- \n");
        printf("\n1. Clientes\n2. Facturas\n3. Cerrar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menu_clientes(); break;
            case 2: menu_fs(); break;
            case 3: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida\n");
        }
    } while(opcion != 3);
 }
//Funcion de menus principales

//Funcion principal
int main(){
    // Aquí llamamos a los diferentes modulos
    int opcion;
    do {
        printf ("\n --- Bienvenido al Hipermercado Cachamay --- \n");  
        printf ("\n RIF: J-123456789      Tlf:041404633588\n");
        printf("\n1. Control Ventas \n2. Admin. Comercio \n3. Salir \n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menu_ctrlV(); break;
            case 2: menu_admin(); break;
            case 3: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida\n");
        }
    } while(opcion != 3);

    return 0;
}
//Funcion principal
