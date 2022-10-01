#pragma comment(lib, "cryptlib.lib")
#include <sstream>
#include <iostream>
#include <string>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>
#include <cryptopp/SHA.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "cryptopp/randpool.h"
#include <cryptopp/osrng.h>
#include <iomanip>
using namespace std;
using namespace CryptoPP;
int main()
{
    ofstream out("out.txt");
    SHA256 hash1;
    string message1 = "Bitcoin is a cryptocurrency, a form of electronic cash.";
    string digest1;

    StringSource sss(message1, true, new HashFilter(hash1, new HexEncoder(new StringSink(digest1))));

    cout << digest1 << endl;
    out << digest1 << endl;
    SHA256 hash;


    string message = "B4056DF6691F8DC72E56302DDAD345D65FEAD3EAD9299609A826E2344EB63AA4";
    string digest;
    int nonce = 0;
    int zero = -1;
    int j = 0;
    while (nonce < INT_MAX)
    {

        int nzero =0;
        stringstream sstream;
        sstream << hex << setw(8) << setfill('0') << nonce;
        string result = sstream.str();
        
        string temp = message + result;
        string decoded;
        StringSource ss(temp, true,new HexDecoder(new StringSink(decoded)));
        StringSource s(decoded, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
        for (int i = 0; i < digest.size(); i++)
        {
            if (digest[i] != '0')
            {
                nzero = i;
                break;
            }
        }
        if (nzero > zero)
        {           
            cout << j << endl;
            cout << message << endl;
            cout << result << endl;
            out << j << endl;
            out << message << endl;
            out << result << endl;
            zero = nzero;
            message = digest;
            nonce = -1;
            digest.clear();
            j++;
            cout  << message << endl;
            out << message << endl;
            continue;

        }
        digest.clear();
        nonce += 1;
    }


}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
