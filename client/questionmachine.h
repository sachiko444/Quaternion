#pragma once

#include <string>
#include <vector>

enum Estado {
    Pregunta,
    Respuestas
};

class QuestionMachine
{
    public:
        void imprimirEstado();
        void imprimirTodo();
        void procesar(std::string mensaje);

    private:
        Estado _estado = Pregunta;

        std::string _pregunta = "";
        std::vector<std::string> _respuestas;

};