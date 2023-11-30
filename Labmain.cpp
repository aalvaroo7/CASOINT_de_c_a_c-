#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <stdexcept>

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const std::string &text) { std::cout << text << std::endl; }
};

ConsoleBox* consoleBox = new ConsoleBox; // Suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    std::string script;
    FILE* f = fopen(filename, "rb");

    if (!f)
    {
        std::cerr << "Error de apertura de " << filename << ": " << strerror(errno) << std::endl;
        return;
    }

    try
    {
        char buf[4001];
        size_t bytesRead;

        while ((bytesRead = fread(buf, 1, sizeof(buf) - 1, f)) > 0)
        {
            buf[bytesRead] = '\0';
            script.append(buf);
        }

        if (show_script)
        {
            std::cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            std::cout << script << std::endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error desconocido durante la lectura del archivo" << std::endl;
    }

    if (f)
        fclose(f);
}

void load_script()
{
    char filename[500];
    std::cout << "Archivo: ";
    std::cin >> filename;
    load_script(filename, true);
}

int main()
{
    load_script();
    return 0;
}