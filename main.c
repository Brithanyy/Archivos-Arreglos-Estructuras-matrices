#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <strings.h>
///VARIABLES GLOBALES:
//aclaracion: el nombre del archi lo uso con una constante.
//Te lo iba a decir en la clase pero fue el recuperatorio.
const char NOMBRESTRUCT[15] = {"socios.bin"};
const int FILA = 3;
const int COLUM = 3;

///ESTRUCTURA:
typedef struct{
    int idSocio;
    char nombreApellido[35];
    int categoria;
    int edad;
}Socio;

///PROTOTIPADO FUNCIONES:
void menu();
void cargarMatrix(int matrix[FILA][COLUM]);
void mostrarMatrix(int matrix[FILA][COLUM]);
int sumarElementosMatrix(int matrix[FILA][COLUM]);
float promedioMatrix(int matrix[FILA][COLUM]);
void cargandoArchiSocio(Socio socios);
Socio cargarUnSoloSocio();
void mostrarStructSocio();
void mostrarUnSoloSocio(Socio socios);
void promedioEdadSegunCategoria(int categoria);
int cantidadRegistrosSocios();
void mostrandoRegistroEspecifico(int registro);
int pasarAlArregloLosSociosCatEspecifica(int categoria, Socio arrSocios[10]);
void mostrarArrSocio(Socio arrSoci[], int validos);
void mostrarUnArrSocio(Socio arrSoci[], int i);
int encontrarStringSocios(char nombre[]);


int main(){
///Variables antes del swich:
int matrix[FILA][COLUM];
float promedio;
Socio socios;
int categoria;
int cantSocios;
int registro;
int flag = 0;
Socio arrSocios[10];
int cantRegistrosArr;
int validosArr;
char nombre[30];
int idSocio;
///------------------------------------>
char eleccion = 's';
int ejercicio;
do{
menu();
printf("\nIngrese el numero del ejercicio correspondiente: ");
fflush(stdin);
scanf("%i", &ejercicio);
printf("\n");
switch(ejercicio) {
    case 1:
        cargarMatrix(matrix);
        mostrarMatrix(matrix);
        promedio = promedioMatrix(matrix);
        printf("\nEl promedio de la matriz es: %.2f \n", promedio);
    break;
    case 2:
        //cargandoArchiSocio(socios);
        mostrarStructSocio();
    break;
    case 3:
        printf("Ingrese la categoria: ");
        fflush(stdin);
        scanf("%i", &categoria);
        promedioEdadSegunCategoria(categoria);
    break;
    case 4:
        cantSocios = cantidadRegistrosSocios();
        printf("Cantidad de registros: %i \n", cantSocios);
    break;
    case 5:
        cantSocios = cantidadRegistrosSocios();
        printf("Cantidad de registros: %i \n\n", cantSocios);
        do{
            printf("Ingrese un registro y se lo mostrare: ");
            fflush(stdin);
            scanf("%i", &registro);
            if(registro <= cantSocios && registro >= 1){
                flag = 1;
            }else{
                flag = 0;
                printf("\nIngrese un registro correcto.\n");

            }
        }while(flag == 0);
        mostrandoRegistroEspecifico(registro);

    break;
    case 6:
        printf("Ingrese la categoria: ");
        fflush(stdin);
        scanf("%i", &categoria);
        cantRegistrosArr = pasarAlArregloLosSociosCatEspecifica(categoria,arrSocios);
        printf("\nEl arreglo tiene un total %i socios registrados.\n ", cantRegistrosArr);
    break;
    case 7:
        printf("Ingrese la categoria: ");
        fflush(stdin);
        scanf("%i", &categoria);
        validosArr = pasarAlArregloLosSociosCatEspecifica(categoria,arrSocios);
        printf("\nEl arreglo tiene un total %i socios registrados.\n ", validosArr);
        mostrarArrSocio(arrSocios,validosArr);
    break;
    case 8:
        printf("Ingresa el nombre y apellido a buscar: ");
        fflush(stdin);
        gets(nombre);
        idSocio = encontrarStringSocios(nombre);
        if(idSocio != 0){
            printf("\nEl idSocio es: %i \n", idSocio);
        }else{
            printf("\nNo se encontro el socio que buscaba.\n");
        }

    break;
}
printf("\n\nPulsa 's' si desea ver otro ejercicio: ");
fflush(stdin);
scanf("%c", &eleccion);
printf("\n");
}while(eleccion == 's');


}
///FUNCIONES
//menu swich:
void menu(){
    printf("Inciso 1.\n");
    printf("Inciso 2.\n");
    printf("Inciso 3.\n");
    printf("Inciso 4.\n");
    printf("Inciso 5.\n");
    printf("Inciso 6.\n");
    printf("Inciso 7.\n");
    printf("Inciso 8.\n");
}
//cargar matrix rand:
void cargarMatrix(int matrix[FILA][COLUM]){
    srand(time(NULL));
    int i,j;
    for(i = 0; i<FILA;i++){
        for(j = 0; j<COLUM;j++){
            matrix[i][j] = rand()%10;
        }
        printf("\n");
    }
}
//mostrar matrix:
void mostrarMatrix(int matrix[FILA][COLUM]){
int i,j;
for(i = 0; i<FILA; i++){
    for(j = 0; j<COLUM; j++){
        printf("|%i| ", matrix[i][j]);
        }
        printf("\n");
    }
}
//sumar elementos matrix:
int sumarElementosMatrix(int matrix[FILA][COLUM]){
    int i,j;
    int acumulador = 0;
    for(i = 0; i<FILA; i++){
    for(j = 0; j<COLUM; j++){
        acumulador = acumulador + matrix[i][j];
        }
    }
    return acumulador;
}
float promedioMatrix(int matrix[FILA][COLUM]){
    int suma = sumarElementosMatrix(matrix);
    int elementos = FILA * COLUM;
    float promedio = suma / elementos;
    return promedio;
}
//cargar en un archivo la estructura socio:
void cargandoArchiSocio(Socio socios){
    char eleccion = 's';
    FILE *archi = fopen(NOMBRESTRUCT,"ab");
    if(archi != NULL){
        while(eleccion == 's'){
            socios = cargarUnSoloSocio();
            fwrite(&socios,sizeof(Socio),1,archi);
            printf("\nPulsa 's' si desea continuar: ");
            fflush(stdin);
            scanf("%c", &eleccion);
            printf("\n");
        }
        fclose(archi);
    }else{
        printf("\nERROR AL ABRIR EL ARCHIVO.\n");
    }
}
Socio cargarUnSoloSocio(){
    Socio socio;
    int verificacion;
    int flag = 0;
    printf("Numero de Socio: ");
    fflush(stdin);
    scanf("%i", &socio.idSocio);
    printf("\n");
    printf("Nombre y Apellido: ");
    fflush(stdin);
    gets(socio.nombreApellido);
    printf("\n");
    do{
        printf("Categoria |1|2|3|4|: ");
        fflush(stdin);
        scanf("%i", &verificacion);
        if(verificacion >= 1 && verificacion <= 4){
            socio.categoria = verificacion;
            flag = 1;
        }else{
            printf("\nCategoria incorrecta. Intente neuvamente.\n");
            flag = 0;
        }
    }while(flag == 0);
    printf("\n");
    printf("Edad: ");
    fflush(stdin);
    scanf("%i", &socio.edad);
    printf("\n");
    return socio;
}
void mostrarStructSocio(){
    Socio socios;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&socios,sizeof(Socio),1,archi);
            if(!feof(NULL)){
                mostrarUnSoloSocio(socios);
            }
        }
        fclose(archi);
    }
}
void mostrarUnSoloSocio(Socio socios){
    printf("\n---------------------------------------->\n");
    printf("Numero de socio: %i ", socios.idSocio);
    printf("\n");
    printf("Nombre y apellido: %s ", socios.nombreApellido);
    printf("\n");
    printf("Categoria: %i ", socios.categoria);
    printf("\n");
    printf("Edad: %i ", socios.edad);
    printf("\n---------------------------------------->\n");

}
//sumando edad de categoria especifica:
void promedioEdadSegunCategoria(int categoria){
    Socio socios;
    int acumuladorEdades = 0;
    int contador = 0;
    float promedio;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&socios,sizeof(Socio),1,archi);
            if(!feof(archi)){
                if(socios.categoria == categoria){
                    acumuladorEdades = acumuladorEdades + socios.edad;
                    contador++;
                }
            }
        }
        fclose(archi);
    }
   promedio = acumuladorEdades / contador;
   printf("\nEl promedio de la categoria %i es %.2f % \n", categoria,promedio);
}
int cantidadRegistrosSocios(){
    Socio socios;
    int cantidadSocios;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
        fseek(archi,0,SEEK_END);
        cantidadSocios = ftell(archi) / sizeof(Socio);
        fclose(archi);
    }
    return cantidadSocios;
}
void mostrandoRegistroEspecifico(int registro){
    Socio soci;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
        fseek(archi,sizeof(Socio) * (registro - 1),SEEK_SET);
        fread(&soci,sizeof(Socio),1,archi);
        mostrarUnSoloSocio(soci);
        fclose(archi);
    }else{
        printf("\nERROR AL ABRIR EL ARCHIVO.\n");
    }
}
int pasarAlArregloLosSociosCatEspecifica(int cat, Socio arrSocios[10]){
    Socio soci;
    int i = 0;
    int cantRegistrosArr = 0;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
            while(!feof(archi)){
                fread(&soci,sizeof(Socio),1,archi);
                if(!feof(archi)){
                    if(soci.categoria == cat){
                        arrSocios[i].idSocio = soci.idSocio;
                        strcpy(arrSocios[i].nombreApellido,soci.nombreApellido);
                        arrSocios[i].categoria = soci.categoria;
                        arrSocios[i].edad = soci.edad;
                        i++;
                        cantRegistrosArr++;
                    }
                }
            }
        fclose(archi);
    }else{
        printf("\nERROR AL ABRIR EL ARCHIVO.\n");
    }
    return cantRegistrosArr;
}
void mostrarArrSocio(Socio arrSoci[], int validos){
    int i = 0;
    while(i <= validos - 1){
        mostrarUnArrSocio(arrSoci,i);
        i++;
    }
}
void mostrarUnArrSocio(Socio arrSoci[], int i){
    printf("\n--------------------------------------->\n");
    printf("Numero de socio: %i", arrSoci[i].idSocio);
    printf("\n");
    printf("Nombre y Apellido: %s ", arrSoci[i].nombreApellido);
    printf("\n");
    printf("Categoria: %i ", arrSoci[i].categoria);
    printf("\n");
    printf("Edad: %i ", arrSoci[i].edad);
    printf("\n--------------------------------------->\n");
}
int encontrarStringSocios(char nombre[]){
    Socio soci;
    int i = 0;
    FILE *archi = fopen(NOMBRESTRUCT,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&soci,sizeof(Socio),1,archi);
            if(!feof(archi)){
                if(strcmp(soci.nombreApellido,nombre) == 0){
                    i++;
                }
            }
        }
    }
    return i;
}
