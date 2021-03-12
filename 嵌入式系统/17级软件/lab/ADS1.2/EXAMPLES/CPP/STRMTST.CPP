/*
 * strmtst.cpp: A Very Basic Test of C++ streams.
 */

#include <fstream>

int main()
{
    char buf[40];
    int i = 0x12345678;
    char ch;

    cout << "\nFirst a very basic test of cout and cin\n\n";
    cout << "Please type in a string (no whitespace), an integer ";
    cout << "and then a char\n\n: ";

    cin >> buf >> i >> ch;

    cout << endl << endl;

    cout << "The string was \"" << buf << "\"\n";
    cout << "The integer was " << i;
    cout << " in decimal, " << hex << i << " in hex\n";
    cout << "The character was '" << ch << "' == ";
    cout << uppercase << showbase << (int)ch << " in hex\n";
    cout << "cin.good() is " << boolalpha << cin.good() << endl;
    cin.clear(); // in case a conversion failed
    while (cin.get() != '\n' && cin.good()) // remove any trailing stuff
        continue;

    cout << "\nNow please type in a string, a hex unsigned ";
    cout << "long and then a char \n\n: ";

    unsigned long j = 0xdeadbeef;
    cin >> buf >> hex >> j >> ch;

    cout << endl << endl;

    cout << "The string was \"" << buf << "\"\n";
    cout << "The unsigned hex was " << dec << j;
    cout << " in decimal, " << oct << j << " in octal\n";
    cout << "The character was '" << ch << "' == ";
    cout << nouppercase << showbase << hex << (int)ch << " in hex\n";
    cout << dec << (unsigned long)i << " < " << j << " == ";
    cout << (i < j) << " == " << noboolalpha << (i < j) << endl;
    cout << "cin.good() is " << boolalpha << cin.good() << endl;
    cin.clear();
    while (cin.get() != '\n' && cin.good())
        continue;

    cout << "\nNow we'll try opening a file and typing it\n\n";
    cout << "A path specification may be needed. \nTo display the C ";
    cout << "source file for this module enter  ..\\..\\strmtst.cpp";
    cout << endl << endl;

    int l = 0;

    for (;;)
    {
        cout << "Please type the name of a small file [* to quit]: ";
        cin >> buf;
        if (!cin || buf[0] == '*')
            break;
        ifstream in(buf);
        if (!in)
        {
            cout << "Can't open file '" << buf << "'\n\n";
            continue;
        }
        for (;;)
        {
            in.read(buf, sizeof(buf));        // read up to 40 chars...
            for (l = 0; l < 40; l++)
              cout << buf[l];
            if (in.eof()) break;
        }
        cout << "\nEND OF INPUT\n\n";
    }
    return 0;
}

