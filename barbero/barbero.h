#ifndef BARBERO_H
#define BARBERO_H

#include"cliente.h"

struct Barbero:public QThread{
    Q_OBJECT
signals:

public:
    string id;
    int descanso; //wait
    vector<Cliente*>* silla;

    Barbero(string ext_id,vector<Cliente*>* ext_silla){  //uf Punt
        id=ext_id;
        silla=ext_silla;
    }

    int tenemos(vector<Cliente*> &buffer){   //uf Punt
        for(int i=0;i<buffer.size();i++){
            if(buffer[i]!=NULL && buffer[i]->estado=="esperando"){
                    buffer[i]->estado=="atendiendo";  // !!
                    buffer[i]=NULL;
                    return i;
                    //return true; tenemos clientes
            }
        }
        return 1000;
        //return false; esta vacio
    }

    void B_accion(){
        int aux;
        int aux2;
        for(int i=0;i<10;i++){
            while((aux=tenemos(*silla))!= 1000 ){
                cout<<"Tenemos trabajo que hacer!\n";
                sleep(700);                 //Este sleep tomamos como si estuviera trabajando
                //(*silla)[aux]=NULL;
                cout<<"Terminamos ahora procederemos a la caja\n";
            }
            cout<<"esta vacia descansare\n";
            sleep(500);
        }
    }
};

#endif // BARBERO_H
