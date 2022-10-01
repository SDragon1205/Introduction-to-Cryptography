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
    ofstream out("out.txt");
    SHA256 hash;
    string message = "Bitcoin is a cryptocurrency, a form of electronic cash.";
    string digest;

    StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));

    out << digest << "\n";
    digest.clear();

    ////////////////////////
    out << "0" << "\n" << "B4056DF6691F8DC72E56302DDAD345D65FEAD3EAD9299609A826E2344EB63AA4" << "\n" << "00000000" << "\n" << "2767667C2AF3BE01EFAC4FB387EC27C10B9D3BEE9C5D48CFF4CFB9F523560B24" << "\n";

    string s1 = "2767667C2AF3BE01EFAC4FB387EC27C10B9D3BEE9C5D48CFF4CFB9F523560B24";
    string s2, s3, s4;
    stringstream ss;
    int c;

    //cout << ss.str() << endl;
    for (int i = 1; i < 64; i++)
    {
        for (int j = 0; j < 2147483647; j++)
        {
            ss << hex << setw(8) << setfill('0') << j;
            ss >> s2;
            //cout << s2 << ": ";
            ss.str("");
            ss.clear();
            s3 = s1 + s2;
            //cout << s3 << "\n";
            StringSource sss(s3, true, new HexDecoder(new StringSink(s4)));
            StringSource ssss(s4, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
            c = 0;
            //cout << digest << " ";
            for (int x = 0; x <= i; x++)
            {
                if (digest[x] != '0')
                {
                    c = x;
                    break;
                }
            }
            //cout << ", c: " << c << "\n";

            s3.clear();
            s4.clear();

            if (c == i)
            {
                out << i << "\n" << s1 << "\n" << s2 << "\n" << digest << "\n";
                s1.clear();
                s1 = digest;
                s2.clear();
                digest.clear();
                break;
            }

            s2.clear();
            digest.clear();
        }
    }

    return 0;
}
