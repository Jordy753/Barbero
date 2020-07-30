#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

std::mutex mtx;

struct Cliente{
    int id;
    int esperando; //wait
    string estado;
    vector<Cliente*>* sofa;
    vector<Cliente*>* sala_esp;
    vector<Cliente*>* silla;

    Cliente(int ext_id,vector<Cliente*>* ext_silla,vector<Cliente*>* ext_sofa,vector<Cliente*>* ext_sala){  //uf Punt
        id=ext_id;
        silla=ext_silla;
        sofa=ext_sofa;
        sala_esp=ext_sala;
        estado="esperando";
    }

    int lleno(vector<Cliente*> &buffer){   //uf Punt
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

    void C_accion(){
        int aux;
        int aux2;
        if( (aux=lleno(*sofa))!= 1000 ){          //uf Punt. Realizamos cambio ahora cuando en False(hay espacios vacios)
            //int aux=lleno(*silla);                       //da un indice y cuando es True(esta lleno) nos da 1000
            cout<<"hay espacio Sofa\n";

            while(lleno(*silla)== 1000){
                cout<<"Esperando en el sofa por mi turno\n";
                Sleep(500);
            }
            (*sofa)[aux]=NULL;
            cout<<"me sente Servicio!\n";

            /*if(lleno(*silla)!= 1000){
                (*sofa)[aux]=NULL;
                cout<<"me sente ¡Servicio!\n";
            }*/

        }
        else if( (aux2=lleno(*sala_esp))!= 1000 ){ //uf Punt
            int aux3;
            cout<<"hay espacio Sala\n";

            while((aux3=lleno(*sofa))== 1000){
                cout<<"Esperando en la sala para ir al sofa\n";
                Sleep(500);
            }
            (*sala_esp)[aux2]=NULL;
            cout<<"Al fin en el sofa\n";

            while(lleno(*silla)== 1000){
                cout<<"Esperando en el sofa por mi turno\n";
                Sleep(500);
            }
            (*sofa)[aux3]=NULL;
            cout<<"me sente ¡Servicio!\n";

        }
        else{
            cout<<"Regreso magnana\n";
        }
    }

};

struct Barbero{
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
                Sleep(700);                 //Este sleep tomamos como si estuviera trabajando
                //(*silla)[aux]=NULL;
                cout<<"Terminamos ahora procederemos a la caja\n";
            }
            cout<<"esta vacia descansare\n";
            Sleep(500);
        }
    }
};

int main(){
    //threads.push_back(std::thread(agregar,0,productos));
    vector<Cliente*> silla;
    vector<Cliente*> sofa;                  //uf Punt
    vector<Cliente*> espera;                //uf Punt
    Cliente c7(7,&silla,&sofa,&espera);            //prueba

    for(int i=0;i<3;i++){
        //null &c7
        silla.push_back(NULL);
    }
    for(int i=0;i<4;i++){
        //null &c7
        sofa.push_back(NULL);
    }
    for(int i=0;i<40;i++){
        //null &c7
        espera.push_back(NULL);
    }
        //regreso magnana
    /*
    Cliente c1(22,&silla,&sofa,&espera);            //uf Punt
    c1.C_accion();
    */
    Barbero b1("A",&silla);
    Barbero b2("B",&silla);
    Cliente c1(1,&silla,&sofa,&espera);
    Cliente c2(2,&silla,&sofa,&espera);
    Cliente c3(3,&silla,&sofa,&espera);
    Cliente c4(4,&silla,&sofa,&espera);
    Cliente c5(5,&silla,&sofa,&espera);
    Cliente c6(6,&silla,&sofa,&espera);

    vector<std::thread> threads;
    threads.push_back(std::thread( [&c1](){
                                  c1.C_accion();
                                  } ));
    threads.push_back(std::thread( [&c2](){
                                  c2.C_accion();
                                  } ));
    threads.push_back(std::thread( [&c3](){
                                  c3.C_accion();
                                  } ));
    threads.push_back(std::thread( [&c4](){
                                  c4.C_accion();
                                  } ));

    threads.push_back(std::thread( [&b1](){
                                  b1.B_accion();
                                  } ));
    threads.push_back(std::thread( [&b2](){
                                  b2.B_accion();
                                  } ));

    for(auto& thread : threads){
        thread.join();
    }

    cout<<"\n---------------------------------\n";
    cout<<"SILLA\n";
    for(int i=0;i<silla.size();i++){
        if(silla[i]==NULL){
        cout<<silla[i]<<" ";
        }
        else{
        cout<<silla[i]->id<<" ";
        }
    }
    cout<<"\n---------------------------------\n";
    cout<<"SOFA\n";
    for(int i=0;i<sofa.size();i++){
        if(sofa[i]==NULL){
        cout<<sofa[i]<<" ";
        }
        else{
        cout<<sofa[i]->id<<" ";
        }
    }
    cout<<"\n---------------------------------\n";
    cout<<"SALA\n";
    for(int i=0;i<espera.size();i++){
        if(espera[i]==NULL){
        cout<<espera[i]<<" ";
        }
        else{
        cout<<espera[i]->id<<" ";
        }
    }

    return 0;
}
