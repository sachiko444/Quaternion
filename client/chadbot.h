#pragma once

#include <room.h>
#include <string>
#include <vector>


class QuaternionRoom;

class ChadBot {

    public:
        ChadBot(QuaternionRoom* room); //posthtmltext es de queternion room por eso se usa esta referencia

        void almacenar(std::string great, std::string value);
        std::string recuperar(std::string great);
        std::vector<std::string> buscar(std::string great);

        bool existe(std::string great);
        void procesar(const Quotient::TimelineItem& ti);


    private:
        std::string* _great = new std::string[1];
        std::string* _value = new std::string[1];
        int _numGreat= 0;
        QuaternionRoom* _room;
};