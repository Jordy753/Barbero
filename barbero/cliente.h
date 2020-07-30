#ifndef CLIENTE_H
#define CLIENTE_H

#include"librerias.h"

struct Cliente:public QThread
{
    Q_OBJECT

signals:
    void barra1(int);
    void barra2(int);
    void barra3(int);
    void tiem_esper(double);
    void insert_text(QString);

public:
    int id;
    int *a1;
    int *a2;
    int *a3;
    string estado;
    vector<Cliente*>* sofa;
    vector<Cliente*>* sala_esp;
    vector<Cliente*>* silla;
    QMutex mtx;

    Cliente(int ext_id=0,vector<Cliente*>* ext_silla=nullptr,vector<Cliente*>* ext_sofa=nullptr,
            vector<Cliente*>* ext_sala=nullptr,int* a=nullptr,int* b=nullptr,int* c=nullptr,
            QObject *parent=nullptr):QThread(parent){
        a1=a;
        a2=b;
        a3=c;
        silla=ext_silla;
        sofa=ext_sofa;
        sala_esp=ext_sala;
        estado="esperando";
    }

    //QObject *parent=nullptr

    int lleno(vector<Cliente*> &buffer){
        for(int i=0;i<buffer.size();i++){
            if(buffer[i]==NULL){
                    buffer[i]=this;
                    return i;
                    //return false;
            }
        }
        return 1000;
        //return true;
    }

    void run(){
        int aux;
        int aux2;
        mtx.lock();
        if( (aux=lleno(*sofa))!= 1000 ){          //uf Punt. Realizamos cambio ahora cuando en False(hay espacios vacios)
            qDebug() <<"hay espacio Sofa\n";
            emit barra2((*a2)++);
            while(lleno(*silla)== 1000){
                qDebug() <<"Esperando en el sofa por mi turno\n";
                sleep(500);
            }
            (*sofa)[aux]=NULL;
            qDebug() <<"me sente Servicio!\n";
        }
        else if( (aux2=lleno(*sala_esp))!= 1000 ){ //uf Punt
            int aux3;
            qDebug() <<"hay espacio Sala\n";

            while((aux3=lleno(*sofa))== 1000){
                qDebug() <<"Esperando en la sala para ir al sofa\n";
                sleep(500);
            }
            (*sala_esp)[aux2]=NULL;
            qDebug() <<"Al fin en el sofa\n";

            while(lleno(*silla)== 1000){
                qDebug() <<"Esperando en el sofa por mi turno\n";
                sleep(500);
            }
            (*sofa)[aux3]=NULL;
            qDebug() <<"me sente ¡Servicio!\n";

        }
        else{
            qDebug() <<"Regreso magnana\n";
        }
        mtx.unlock();
    }

};



#endif // CLIENTE_H
