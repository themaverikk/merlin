#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char **args)
{
    try
    {
        std::cout << "MERLIN 0.1\n"
                  << endl;
        if (argc < 2)
        {
            throw runtime_error("Expected a file name/path in the command");
        }
        FILE *fh = fopen(*(args + 1), "r");
        if (!fh)
        {
            cerr << "Can't find file. " << *(args + 1) << endl;
            return 1;
        }
        fseek(fh, 0, SEEK_END);
        size_t fileSize = ftell(fh);
        fseek(fh, 0, SEEK_SET);
        string fileContents(fileSize, ' ');
        fread(fileContents.data(), 1, fileSize, fh);

        //    cout << fileContents << endl << endl;

        Tokenizer tokenizer;
        vector<Token> tokens = tokenizer.parse(fileContents);

        //    for(Token currToken : tokens) {
        //        currToken.debugPrint();
        //    }

        Parser parser;
        parser.parse(tokens);
        // cout << "Parser Tree Starts Here:" << endl;
        // cout << "--------------------------------------------------------------------------" << endl;
        // parser.debugPrint();
        // cout << "--------------------------------------------------------------------------" << endl;
        // cout << "Parser Tree Ends Here:" << endl;
        Interpretor interpreter;
        interpreter.interpreat(parser.mFunctions["main"].mStatements);
        cout << "Interpreted Results" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        interpreter.debugPrint();
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "END OF PROGRAM" <<endl;
    }
    catch (exception &err)
    {
        cerr << "Error: " << err.what() << endl;
        return 2;
    }
    catch (...)
    {
        cerr << "Unknown Error." << endl;
        return 3;
    }

    return 0;
}
