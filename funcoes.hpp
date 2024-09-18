#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <string>
#include <vector>

using namespace std;

struct Livro {
    string titulo;
    string autor;
    int ano;
    int copias;
    int emprestados;
    int numEmprestimos;  // Contador de quantas vezes o livro foi emprestado
};

struct Usuario {
    string nome;
    string historicoLivros[10];  // Limite de 10 livros emprestados por usuário
    int numLivrosEmprestados;
    float multa;  // Valor acumulado de multas
    vector<time_t> datasEmprestimo;  // Para controlar as datas de empréstimo
};

// Declarações de funções
void cadastrarLivro(Livro livros[], int &qtdLivros);
void cadastrarUsuario(Usuario usuarios[], int &qtdUsuarios);
void emprestarLivro(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios);
void devolverLivro(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios);
void pesquisarLivro(Livro livros[], int qtdLivros);
void pesquisarLivrosUsuario(Usuario usuarios[], int qtdUsuarios);
void listarLivros(Livro livros[], int qtdLivros);
void controleMultas(Usuario usuarios[], int qtdUsuarios);
void relatorioEmprestimos(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios);
void menu(Livro livros[], int &qtdLivros, Usuario usuarios[], int &qtdUsuarios);

#endif
