#include "chadbot.h"
#include <room.h>
#include "quaternionroom.h"


#include <iostream>
#include <vector>



ChadBot::ChadBot(QuaternionRoom* room): _room(room) {}



//Un comando "almacenar" que acepta dos pedazos de texto. 
//El primero se utiliara como indice y el segundo es el texto a ser guardado. 
//Si un indice ya fue almacenado, se debe substituir por el valor nuevo.


void ChadBot::almacenar(std::string great, std::string value) {

    //sobreescribir valor en array
    for(int i =0; i<_numGreat; i++) {
        if(great == _great[i]) {
            _value[i] == value;
            return;
        }
    }


    //agregar indice y valor en array
    std::string* temg = new std::string[_numGreat +1];
    std::string* temv = new std::string[_numGreat +1];

    temg[0] = great;
    temv[0] = value;

    for(int i =0; i<_numGreat; i++) {
        temg[i+1] = _great[i];
        temv[i+1] = _value[i];
    }


    delete[] _great; 
    delete[] _value;

    _great = temg;
    _value = temv;
    _numGreat++;

}



//SI EXISTE INDICE EN _GREAT

bool ChadBot::existe(std::string great) {
    for(int i =0; i<_numGreat; i++) {
        if(great == _great[i]) {
            return true;
        }    
    }

    return false;
}






//Un comando "recuperar" que acepta una palabra y la busca en el indice de palabras. 
//En caso de encontrar dicha palabra, 
//se debe responder un mensaje con el valor almacenado con dicho indice

std::string ChadBot::recuperar(std::string great) {
    
    for(int i =0; i<_numGreat; i++) {
        if(great == _great[i]) {
            return _value[i];
        }    
    }
    return "";
}





//Un comando "buscar" que debe aceptar una palabra y 
//retorna todos los indices que tengan algún parecido a la misma. 
//Por ejemplo:
//"buscar, dir"
//Responde "direccion, direccion trabajo"

std::vector<std::string> ChadBot::buscar(std::string great) {

    //en temp se almacenan todos los great encontrados
    std::vector<std::string> temp;

    for(int i =0; i<_numGreat; i++) {
        size_t pos =  _great[i].find(great);

        //If no matches were found, the .find returns string::npos
        if(pos != std::string::npos) {
            temp.push_back(_great[i]);
        }
    
    }
    return temp;
}







//BASICALLY EL MAIN

//lo que acepta el checkforhiglights
void ChadBot::procesar(const Quotient::TimelineItem& ti ) {

    //se extrae el mensaje
    auto* e = ti.viewAs<Quotient::RoomMessageEvent>();
    if(e) {
        const auto& text = e->plainBody();
        std::string mensaje = text.toStdString();

        auto alm = mensaje.find("~save ");
        auto rec = mensaje.find("~in ");
        auto bus = mensaje.find("~find ");
        auto hel = mensaje.find("~help");

        //~save direccion/mixco
        if(alm == 0){
            std::cout << "using almacenar\n";
            std::string alm_great = mensaje.substr(6, mensaje.find("/")-6);  
            std::string alm_value = mensaje.substr(mensaje.find("/") + 1);
            almacenar(alm_great, alm_value);
            _room->postHtmlText(
                    QString::fromStdString("Indice almacenado :)"),
                    QString::fromStdString("<p> <b> <i> Indice almacenado :) </i> </b> </p>")
                    
                );
        }

        //~in direccion

        if(rec == 0) {
            std::cout << "using recuperar\n";
            std::string rec_great = mensaje.substr(4);  
            if(existe(rec_great)) {
                _room->postHtmlText(
                    QString::fromStdString(recuperar(rec_great)), 
                    QString::fromStdString("<p> <b> <i>" + recuperar(rec_great) + " </i> </b> </p>")
                );
            } else {
                _room->postHtmlText(
                    QString::fromStdString("Indice no encontrado :( "),
                    QString::fromStdString("<p> <b> <i> Indice no encontrado :( </i> </b> </p>")
                    
                );
            }
        }


        //~find dire

        if(bus == 0) {
            std::cout << "using buscar\n";
            std::string bus_great = mensaje.substr(6);
            std::vector<std::string> encontrados = buscar(bus_great);
            for (std::string bus_great : encontrados) { //por cada elemento de encontrados se va imprimir
                _room->postHtmlText(
                    QString::fromStdString(bus_great),
                    QString::fromStdString("<p> <b> <i>" + bus_great + " </i> </b> </p>")
                );
            }

            if(encontrados.size() == 0) {
                _room->postHtmlText(
                    QString::fromStdString("Indice no encontrado :( "),
                    QString::fromStdString("<p> <b> <i> Indice no encontrado :( </i> </b> </p>")
                );
            }
        }



        if(hel == 0) {
            std::cout << "using help \n";
            _room->postHtmlText(
                    QString::fromStdString("Comandos:  utilizan prefijo ~ "),
                    QString::fromStdString("<p> <b> Comandos: </b> utilizan prefijo <b> ~ </b> </p>")
                );
            _room->postHtmlText(
                    QString::fromStdString(" ~save indice/valor  (guarda un indice y valor)"),
                    QString::fromStdString("<p>  <b> ~save </b> indice/valor  (guarda un indice y valor) </p>")
                );
            _room->postHtmlText(
                    QString::fromStdString(" ~in indice  (recupera lo que esta dentro del indice)"),
                    QString::fromStdString("<p>  <b> ~in </b> indice  (recupera lo que esta dentro del indice) </p>")
                );
            _room->postHtmlText(
                    QString::fromStdString(" ~find indice  (encuentra si indice existe)"),
                    QString::fromStdString("<p>  <b> ~find </b> indice  (encuentra si indice existe) </p>")
                );
        }




    }


}