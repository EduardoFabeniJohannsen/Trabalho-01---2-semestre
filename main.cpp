    #include "funcoes.hpp"
    #include <iostream>

    using namespace std;

    int main() {
        Livro livros[100];  // Capacidade p/ 100 livros
        Usuario usuarios[100];  // Capacidade p/ 100 usuários
        int qtdLivros = 0, qtdUsuarios = 0;

        cout << "teste";
        // Cadastrar alguns livros e usuários pré-definidos
        livros[qtdLivros++] = {"Teste", "Escritor de teste", 2020, 10, 0, 0};
        usuarios[qtdUsuarios++] = {"usuario", {}, 0, 0.0, {}};

        menu(livros, qtdLivros, usuarios, qtdUsuarios);

        return 0;
    }
