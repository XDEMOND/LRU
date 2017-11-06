//@XDEMOND
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

int contador[10];
int loc1=3,loc2=2,loc3=1;

struct Memoria{//MMT
    int numero,dirpag,estado,locinicial;
    struct Memoria *sgt;
};

struct Memoria;

Memoria *finMemoria;//final de la lista
Memoria *listaMemoria;//inicio de la lista

void insertarMemoria(int numero,int estado,int marco);
void mostrarMemoria();
int buscarMemoria();
int MemoriaDisponible();
int buscarMemoriaValor(int valor);
//----------------------------------Secuencia-----------------------------------------
struct orden{//MMT
    int numero,dirpag,estado,locinicial;
    int posicion;
    struct orden *sgt;
};

struct orden;

orden *finorden;//final de la lista
orden *listaorden;//inicio de la lista

void inserorden(int posicion,int numero);
void mostrarorden();
int buscarorden(int posicion);
int secuencia[10];
void mostrarsecuencia();
//--------------------------------------PAGINAS-------------------------------------------
struct Paginas {//PMT
    int numpag,dirmarco,numtarea;
    int estado;
    int referenciada;
    int exitencia;
    int contador;
    struct Paginas *sgt;
    struct Paginas *tarea;
};

struct Paginas;

Paginas *finPaginas;//final de la lista
Paginas *listaPaginas;//inicio de la lista

void insertarPaginas(int numero,int direccion,int tarea);
void mostrarPaginas(int tarea);
int buscarPagina(int pagina);
void Asignarcero(int direccion);
void AsignarPagina(int pagina,int loc);

struct Tareas{//JT
    int tarea;
    int tam;
    int locPMT;
    struct Paginas;
    struct Tareas *sgt;
    struct Paginas *PMT;
};

struct Tareas;

Tareas *finTareas;//final de la lista
Tareas *listaTareas;//inicio de la lista
Tareas *PMT;

void insertarTareas(int tarea,int tamano);
void mostrarTareas();
void asignarTarea(int loc,int tarea);
int buscarTarea(int numero);
void insertarPMT(int tarea,int loc);

main ()
{
    int memoria=15,marco=5,paginas,numtareas=1,lineas=20,conasig=0,c,d,disponibles=0;
    int fallos=0;
    paginas=memoria/marco;
    listaMemoria = NULL;
    listaPaginas= NULL;
    listaTareas=NULL;
    /*cout<<"\nPAGINACION FIFO\n"<<endl;
    cout<<"Informacion inicial: "<<endl;
    cout<<"Memoria total: "<<memoria<<" (KB) -> "<<memoria*1024<<" (bytes)"<<endl;
    cout<<"Tamaño de los Marco: "<<marco<<" (KB) -> "<<marco*1024<<" (bytes)"<<endl;
    cout<<"Numero de Paginas: "<<paginas<<endl;
    cout<<"Lienas por Pagina: "<<lineas<<endl;
    cout<<"Numero de Tareas: "<<numtareas<<endl;*/
    for(int i=0;i<paginas;i++)
    {
        insertarMemoria(i,NULL,marco); //Creacion de la memoria
    }
    mostrarMemoria();
    for(int i=1;i<=numtareas;i++)
    {
        int tamano,a,b;
        tamano =80+rand()%(100-80);
        insertarTareas(i,tamano); //Creacion de las tareas
        c=tamano/lineas;
        d=lineas*c;
        if(d<tamano)
        {
            c=c+1;
        }
        disponibles=disponibles+c;
    }
    mostrarTareas();
    for(int i=0;i<=9;i++)
    {
        int temporal;
        temporal=rand()%c;
        secuencia[i]= temporal;
        inserorden(i,temporal);
    }
    for(int i=0;i<c;i++)
        insertarPaginas(i,1,1);
    mostrarorden();
    mostrarPaginas(1);
    for(int i=0;i<3;i++)
    {
        int loc,lugar;
        loc=MemoriaDisponible();
        lugar=buscarorden(i);
        AsignarPagina(lugar,loc);
        cout<<endl;
        cout<<"SECUENCIA "<<i<<" "<<endl<<endl;
        mostrarPaginas(1);
        cout<<endl;
        cout<<"\n";
        system("pause");
        fallos =fallos+1;
    }
    for(int i=3;i<=9;i++)
    {
        int dis=0;
        int loc,l2,c1,c2,c3;
        dis=buscarPagina(buscarorden(i));
        l2=buscarorden(i);
        if(dis==1)
        {
            cout<<endl;
            cout<<"\n"<<"\nSECUENCIA "<<i<<""<<endl;
            cout<<"\nSin cambios"<<endl;
            cout<<endl;
            system("pause");
            loc1=loc1+1;
            loc2=loc2+1;
            loc3=loc3+1;
            c1=loc1;
            c2=loc2;
            c3=loc3;
        }
        else
        {
            fallos=fallos+1;
            if((loc1>loc2) && (loc1>loc3))
            {
                Asignarcero(0);
                AsignarPagina(l2,0);
                c1=0;
            }
            if((loc2>loc1) && (loc2>loc3))
            {
                Asignarcero(5);
                AsignarPagina(l2,5);
                c2=0;
            }
            if((loc3>loc1) && (loc3>loc2))
            {
                Asignarcero(10);
                AsignarPagina(l2,10);
                c3=0;
            }
            cout<<"\nSECUENCIA "<<i<<""<<endl;
            mostrarPaginas(1);
            cout<<endl;
            cout<<"\n";
            system("pause");
            loc1=c1;
            loc2=c2;
            loc3=c3;
        }
    }
    cout<<"Numeros de fallos: "<<fallos<<endl;
    system("pause");
}
//----------------------------------------MEMORIA---------------------------------------------
void insertarMemoria(int numero,int estado,int marco)
{
    Memoria *nuevo;
    nuevo=new struct Memoria;
    nuevo->numero=numero;
    nuevo->estado=estado;
    nuevo->locinicial=numero*marco;
    nuevo->sgt=NULL;

    if(listaMemoria==NULL)
    {
        listaMemoria=nuevo;
        listaMemoria->sgt=listaMemoria;
        finMemoria=nuevo;
    }
    else
    {
        finMemoria->sgt = nuevo;
        nuevo->sgt = listaMemoria;
        finMemoria = nuevo;
    }
}

void mostrarMemoria()
{
    Memoria *aux;
    aux=listaMemoria;
    int i=1;

    if(listaMemoria!=NULL)
    {
        cout<<"\nMMT\n"<<endl;
        cout<<"MARCO"<<"\t"<<"LOC.INICIAL"<<"\t"<<"ESTADO"<<endl;
        cout<<"-------------------------------"<<endl;
        do
        {    cout<<" "<<aux->numero<<"\t"<<aux->locinicial<<"\t\t"<<aux->estado<<endl;
            aux = aux->sgt;
            i++;
        }
        while(aux!=listaMemoria);
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

int buscarMemoria(int valor) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Memoria *aux;
    int i = 1 , flag = 0;
    if(listaMemoria !=NULL)
    {
        aux = listaMemoria;
        do
        {
            if(aux->estado == valor)
            {
                flag=1;
                aux->estado =1;
                //localidadmemor = aux->locinicial;
                return aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaMemoria);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

int MemoriaDisponible() //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Memoria *aux;
    int valor=0;
    int i = 1 , flag = 0;
    if(listaMemoria !=NULL)
    {
        aux = listaMemoria;
        do
        {
            if(aux->estado == valor)
            {
                flag=1;
                aux->estado =1;
                //localidadmemor = aux->locinicial;
                return aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaMemoria);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}
//------------------------------------------SECUENCIA----------------------------------
void inserorden(int posicion,int numero)
{
    orden *nuevo;
    nuevo=new struct orden;
    nuevo->numero=numero;
    nuevo->posicion=posicion;
    nuevo->sgt=NULL;

    if(listaorden==NULL)
    {
        listaorden=nuevo;
        listaorden->sgt=listaorden;
        finorden=nuevo;
    }
    else
    {
        finorden->sgt = nuevo;
        nuevo->sgt = listaorden;
        finorden = nuevo;
    }
}

int buscarorden(int posicion) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    orden *aux;
    int i = 1 , flag = 0;
    if(listaorden !=NULL)
    {
        aux = listaorden;
        do
        {
            if(aux->posicion == posicion)
            {
                flag=1;
                //localidadmemor = aux->locinicial;
                return aux->numero;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaorden);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void mostrarorden()
{
    orden *aux;
    aux=listaorden;
    int i=1;

    if(listaorden!=NULL)
    {
        cout<<"\nSECUENCIA:\n"<<endl;
        do
        {
            cout<<aux->numero<<" , ";
            aux = aux->sgt;
            i++;
        }
        while(aux!=listaorden);
            cout<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}
//-------------------------------------------------------PAGINAS-------------------------------------------
int buscarPagina(int pagina) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Paginas *aux;
    int i = 1 , flag = 0;
    if(listaPaginas !=NULL)
    {
        aux = listaPaginas;
        do
        {
            if(aux->numpag == pagina)
            {
                flag=1;
                return aux->estado;
                //localidadmemor = aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaPaginas);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void AsignarPagina(int pagina,int loc) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Paginas *aux;
    int i = 1 , flag = 0;
    if(listaPaginas !=NULL)
    {
        aux = listaPaginas;
        do
        {
            if(aux->numpag == pagina)
            {
                flag=1;
                aux->estado =1;
                aux->exitencia=1;
                aux->referenciada=1;
                aux->dirmarco=loc;
                //localidadmemor = aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaPaginas);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void Asignarcero(int direccion) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Paginas *aux;
    int i = 1 , flag = 0;
    if(listaPaginas !=NULL)
    {
        aux = listaPaginas;
        do
        {
            if(aux->dirmarco==direccion)
            {
                flag=1;
                aux->estado=0;
                aux->exitencia=0;
                aux->referenciada=0;
                aux->dirmarco=1;
                //localidadmemor = aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaPaginas);
            if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void insertarPaginas(int numero,int direccion,int tarea)
{
    Paginas *nuevo;
    nuevo=new struct Paginas;
    nuevo->numpag=numero;
    nuevo->dirmarco=direccion;
    nuevo->numtarea=tarea;
    nuevo->sgt=NULL;

    if(listaPaginas==NULL)
    {
        listaPaginas=nuevo;
        listaPaginas->sgt=listaPaginas;
        finPaginas=nuevo;
    }
    else
    {
        finPaginas->sgt = nuevo;
        nuevo->sgt = listaPaginas;
        finPaginas = nuevo;
    }
}

void mostrarPaginas(int tarea)
{
    Paginas *aux;
    aux=listaPaginas;
    int i=1;

    if(listaPaginas!=NULL)
    {
        cout<<"\nPMT "<<tarea<<"\n"<<endl;
        cout<<"PAGINA"<<"\t"<<"LOC.MARCO"<<"\t"<<"ESTADO"<<"\t\t"<<"EXISTENCIA"<<"\t"<<"REFERENCIA"<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;

        do
        {
            if(aux->numtarea==tarea)
            cout<<" "<<aux->numpag<<"\t"<<aux->dirmarco<<"\t\t"<<aux->estado<<"\t\t"<<aux->exitencia<<"\t\t"<<aux->referenciada<<endl;
            aux = aux->sgt;
            i++;
        }
        while(aux!=listaPaginas);
    }
    else
        cout<<"\a\n\n\tNo hay marcos"<<endl;
}
//-------------------------------------------TAREAS--------------------------------------
void insertarTareas(int tarea,int tamano)
{
    Tareas *nuevo;
    nuevo=new struct Tareas;
    nuevo->tarea=tarea;
    nuevo->tam=tamano;
    nuevo->sgt=NULL;

    if(listaTareas==NULL)
    {
        listaTareas=nuevo;
        listaTareas->sgt=listaTareas;
        finTareas=nuevo;
    }
    else
    {
        finTareas->sgt = nuevo;
        nuevo->sgt = listaTareas;
        finTareas = nuevo;
    }
}

void mostrarTareas()
{
    Tareas *aux;
    aux=listaTareas;
    int i=1;

    if(listaTareas!=NULL)
    {
        cout<<"\nJT\n"<<endl;
        cout<<"TAREA"<<"\t"<<"TAMANIO"<<"\t\t"<<"LOC.PMT"<<endl;
        cout<<"--------------------------------"<<endl;

        do
        {
            cout<<" "<<aux->tarea<<"\t"<<aux->tam<<"\t\t"<<aux->locPMT<<endl;
            aux = aux->sgt;
            i++;

        }
        while(aux!=listaTareas);
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void insertarPMT(int tarea,int loc)
{
    Paginas *nuevo;
    nuevo=new struct Paginas;
    nuevo->numpag=tarea;
    nuevo->dirmarco=loc;
    nuevo->sgt=NULL;

    if(listaPaginas==NULL)
    {
        listaPaginas=nuevo;
        listaPaginas->sgt=listaPaginas;
        finPaginas=nuevo;
    }
    else
    {
        finPaginas->sgt = nuevo;
        nuevo->sgt = listaPaginas;
        finPaginas = nuevo;
    }
}

void asignarTarea(int loc,int tarea) //esta funcion muestra la posicion del primer dato coincidente encontrado en la lista
{
    Tareas *aux;
    int i = 1 , flag = 0;
    if(listaTareas !=NULL)
    {
        aux = listaTareas;
        do
        {
            if(aux->tarea == tarea)
            {
                flag=1;
                aux->locPMT =loc;
                //localidadmemor = aux->locinicial;
                break;
            }
            else
            {
                aux = aux->sgt;
                i++;
            }
        }
        while(aux!=listaTareas);
        if(flag==0) cout<<"\aMemoria llena!"<<endl;
    }
    else
        cout<<"\a\n\n\tLista vacia!"<<endl;
}

void mostrarsecuencia()
{
    cout<<"\nSECUENCIA INGRESADA\n"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<secuencia[i]<<" , ";
    }
    cout<<endl;
}
