#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

unique_ptr<ConsoleBox> consoleBox = make_unique<ConsoleBox>();

void load_script(const string& filename, bool show_script = false)
{
    try
    {
        ifstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error de apertura de " << filename << endl;
            return;
        }

        string script((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        file.close();

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const exception& e)
    {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
    }
try
    ifstream file(filename, ios::binary);
    if (!file.close())
    {
        cerr << "No existe el archivo :(" << filename << endl;
        return;
    }
{

}
}


void load_script()
{
    string filename;
    cout << "Archivo: ";
    cin >> filename;
    load_script(filename, true);
}

int main()
{
    load_script();
    return 0;
}