#include "funcoes.hpp"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void cadastrarLivro(Livro livros[], int &qtdLivros)
{
    cout << "Cadastrando livro\n";
    cout << "Titulo: ";
    cin.ignore();
    getline(cin, livros[qtdLivros].titulo);
    cout << "Autor: ";
    getline(cin, livros[qtdLivros].autor);
    cout << "Ano de publicacao: ";
    cin >> livros[qtdLivros].ano;
    cout << "Numero de copias: ";
    cin >> livros[qtdLivros].copias;
    livros[qtdLivros].emprestados = 0;
    livros[qtdLivros].numEmprestimos = 0; // Inicializa contador de empréstimos
    qtdLivros++;
}

void cadastrarUsuario(Usuario usuarios[], int &qtdUsuarios)
{
    cout << "Cadastrando usuário\n";
    cout << "Nome: ";
    cin.ignore();
    getline(cin, usuarios[qtdUsuarios].nome);
    usuarios[qtdUsuarios].numLivrosEmprestados = 0;
    usuarios[qtdUsuarios].multa = 0.0;
    qtdUsuarios++;
}

int encontrarUsuario(Usuario usuarios[], int qtdUsuarios, const string &nomeUsuario)
{
    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (usuarios[i].nome == nomeUsuario)
            return i;
    }
    return -1;
}

int encontrarLivro(Livro livros[], int qtdLivros, const string &tituloLivro)
{
    for (int i = 0; i < qtdLivros; i++)
    {
        if (livros[i].titulo == tituloLivro)
            return i;
    }
    return -1;
}

void emprestarLivro(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios)
{
    string nomeUsuario, tituloLivro;
    cout << "Nome do usuário: ";
    cin.ignore();
    getline(cin, nomeUsuario);
    cout << "Título do livro: ";
    getline(cin, tituloLivro);

    int indexUsuario = encontrarUsuario(usuarios, qtdUsuarios, nomeUsuario);
    int indexLivro = encontrarLivro(livros, qtdLivros, tituloLivro);

    if (indexUsuario != -1 && indexLivro != -1 && livros[indexLivro].emprestados < livros[indexLivro].copias)
    {
        if (usuarios[indexUsuario].numLivrosEmprestados < 10)
        {
            livros[indexLivro].emprestados++;
            livros[indexLivro].numEmprestimos++;
            usuarios[indexUsuario].historicoLivros[usuarios[indexUsuario].numLivrosEmprestados] = tituloLivro;
            usuarios[indexUsuario].numLivrosEmprestados++;
            usuarios[indexUsuario].datasEmprestimo.push_back(time(0)); // Data do empréstimo   
            cout << "Livro emprestado com sucesso!\n";
        }
        else
        {
            cout << "Usuário já atingiu o limite de 10 livros emprestados.\n";
        }
    }
    else
    {
        cout << "Usuário ou livro não encontrado, ou todas as cópias já estão emprestadas.\n";
    }
}

void devolverLivro(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios)
{
    string nomeUsuario, tituloLivro;
    cout << "Nome do usuário: ";
    cin.ignore(); 
    getline(cin, nomeUsuario);

    int indexUsuario = encontrarUsuario(usuarios, qtdUsuarios, nomeUsuario);

    if (indexUsuario == -1)
    {
        cout << "Usuário não encontrado.\n";
        return;
    }

    cout << "Lista de livros na posse de " << nomeUsuario << ":\n";
    for (int i = 0; i < usuarios[indexUsuario].numLivrosEmprestados; i++)
    {
        cout << "- " << usuarios[indexUsuario].historicoLivros[i] << endl;
    }

    cout << "Título do livro a devolver: ";
    getline(cin, tituloLivro);

    int indexLivro = encontrarLivro(livros, qtdLivros, tituloLivro);

    if (indexLivro != -1)
    {
        livros[indexLivro].emprestados--;
        cout << "Livro devolvido com sucesso!\n";

        int dia, mes;
        cout << "Digite o dia da devolução: ";
        cin >> dia;
        cout << "Digite o mês da devolução: ";
        cin >> mes;

        struct tm dataDevolucao = {};
        dataDevolucao.tm_year = 2024 - 1900;
        dataDevolucao.tm_mon = mes - 1;
        dataDevolucao.tm_mday = dia;

        time_t dataAtual = mktime(&dataDevolucao);
        time_t dataEmprestimo = usuarios[indexUsuario].datasEmprestimo.back();
        int diasAtraso = difftime(dataAtual, dataEmprestimo) / (60 * 60 * 24) - 7;

        if (diasAtraso > 0)
        {
            float multa = diasAtraso * 1.0;
            usuarios[indexUsuario].multa += multa;
            cout << "Devolução em atraso. Multa acumulada: R$ " << usuarios[indexUsuario].multa << endl;
        }

        // Remover livro do histórico de empréstimos do usuário
        for (int i = 0; i < usuarios[indexUsuario].numLivrosEmprestados; i++)
        {
            if (usuarios[indexUsuario].historicoLivros[i] == tituloLivro)
            {
                usuarios[indexUsuario].historicoLivros[i].clear(); // Remove o livro
                break;
            }
        }

        usuarios[indexUsuario].numLivrosEmprestados--;
    }
    else
    {
        cout << "Livro não encontrado.\n";
    }
}

void pesquisarLivro(Livro livros[], int qtdLivros)
{
    string pesquisa;
    cout << "Digite o título ou autor para pesquisar: ";
    cin.ignore();
    getline(cin, pesquisa);

    for (int i = 0; i < qtdLivros; i++)
    {
        if (livros[i].titulo == pesquisa || livros[i].autor == pesquisa)
        {
            cout << "Livro encontrado: " << livros[i].titulo << " por " << livros[i].autor << endl;
            return;
        }
    }
    cout << "Livro não encontrado.\n";
}

void listarLivros(Livro livros[], int qtdLivros)
{
    cout << "Lista de livros:\n";
    for (int i = 0; i < qtdLivros; i++)
    {
        cout << livros[i].titulo << " (" << livros[i].ano << "), " << livros[i].copias - livros[i].emprestados << " cópias disponíveis\n";
    }
}

void relatorioEmprestimos(Livro livros[], int qtdLivros, Usuario usuarios[], int qtdUsuarios)
{
    int totalEmprestimos = 0;
    Livro livroMaisPopular = livros[0];
    Usuario usuarioMaisAtivo = usuarios[0];

    for (int i = 0; i < qtdLivros; i++)
    {
        totalEmprestimos += livros[i].numEmprestimos;
        if (livros[i].numEmprestimos > livroMaisPopular.numEmprestimos)
        {
            livroMaisPopular = livros[i];
        }
    }

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (usuarios[i].numLivrosEmprestados > usuarioMaisAtivo.numLivrosEmprestados)
        {
            usuarioMaisAtivo = usuarios[i];
        }
    }

    cout << "Relatório de Empréstimos:\n";
    cout << "Total de empréstimos: " << totalEmprestimos << endl;
    cout << "Livro mais popular: " << livroMaisPopular.titulo << " (" << livroMaisPopular.numEmprestimos << " empréstimos)\n";
    cout << "Usuário mais ativo: " << usuarioMaisAtivo.nome << " (" << usuarioMaisAtivo.numLivrosEmprestados << " livros emprestados)\n";
}

void menu(Livro livros[], int &qtdLivros, Usuario usuarios[], int &qtdUsuarios)
{
    int opcao;

    do
    {
        cout << "\nSistema de Gerenciamento de Biblioteca\n";
        cout << "1. Cadastrar livro\n";
        cout << "2. Cadastrar usuário\n";
        cout << "3. Emprestar livro\n";
        cout << "4. Devolver livro\n";
        cout << "5. Pesquisar livro\n";
        cout << "6. Pesquisar livros por usuário\n";
        cout << "7. Listar todos os livros\n";
        cout << "8. Verificar multas\n";
        cout << "9. Relatório de empréstimos\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cadastrarLivro(livros, qtdLivros);
            break;
        case 2:
            cadastrarUsuario(usuarios, qtdUsuarios);
            break;
        case 3:
            emprestarLivro(livros, qtdLivros, usuarios, qtdUsuarios);
            break;
        case 4:
            devolverLivro(livros, qtdLivros, usuarios, qtdUsuarios);
            break;
        case 5:
            pesquisarLivro(livros, qtdLivros);
            break;
        case 7:
            listarLivros(livros, qtdLivros);
            break;
        case 9:
            relatorioEmprestimos(livros, qtdLivros, usuarios, qtdUsuarios);
            break;
        case 0:
            cout << "Saindo do sistema.\n";
            break;
        default:
            cout << "Opção inválida.\n";
        }
    } while (opcao != 0);
}


