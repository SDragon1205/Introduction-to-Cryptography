#pragma comment(lib,"cryptlib.lib")
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include<vector>
using namespace std;
using namespace CryptoPP;

int main()
{
    SHA256 hash;
    string message = "Bitcoin is a cryptocurrency, a form of electronic cash.";
    string digest;

    StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));

    cout << digest << "\n";
    digest.clear();

    ////////////////////////

    string s1 = "B4056DF6691F8DC72E56302DDAD345D65FEAD3EAD9299609A826E2344EB63AA4";
    string s2, s3, s4;
    stringstream ss;
    int c;

    cout << ss.str() << endl;
    int ii;
    for (int i = 0; i < 64; i++)
    {
        ii = i + 1;
        for (int j = 0; j <= 2147483647; j++)
        {
            ss << hex << setw(8) << setfill('0') << j;
            ss >> s2;
            ss.str("");
            ss.clear();
            s3 = s1 + s2;
            StringSource sss(s3, true, new HexDecoder(new StringSink(s4)));
            StringSource ssss(s4, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
            c = 0;
            for (int x = 0; x <= ii; x++)
            {
                if (digest[i] != '0')
                {
                    c = x;
                    break;
                }
            }

            s2.clear();
            s3.clear();
            s4.clear();
            
            if (c > i)
            {
                cout << i << "\n" << digest << "\n";
                s1.clear();
                s1 = digest;
                digest.clear();
                break;
            }

            digest.clear();
        }
    }

    return 0;
}