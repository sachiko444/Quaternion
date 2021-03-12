#include "questionmachine.h"

#include <iostream>
#include <string>

void QuestionMachine::imprimirEstado() {
    std::cout << "Estado: " << _estado << "\n\n";
}

void QuestionMachine::imprimirTodo() {

    std::cout << "Pregunta: " << _pregunta << "\n";

    std::cout << "Respuestas:\n";
    for(std::string resp : _respuestas) {
        std::cout << " - " << resp << "\n";
    }

}

void QuestionMachine::procesar(std::string mensaje) {
    switch(_estado) {

        case Pregunta:
            if (mensaje.rfind("Emitir pregunta: ", 0) == 0) {
                _pregunta = mensaje.substr(17);
                _estado = Respuestas;
            }
            break;
        case Respuestas:
            if (mensaje.rfind("Responder pregunta: ", 0) == 0) {
                std::string respuesta = mensaje.substr(20);

                _respuestas.push_back(respuesta);
            } else if (mensaje.rfind("Finalizar pregunta", 0) == 0) {
                imprimirTodo();

                _respuestas.clear();
                _pregunta = "";
                _estado = Pregunta;
            }
            break;
        default:
            std::cout << "u stupid bich how did u fuck up \n\n";

    }
}
