#pragma comment(lib, "cryptlib.lib")
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include "cryptlib.h"
#include "hex.h"
#include "filters.h"
#include "aes.h"
#include "modes.h"

using namespace std;
using namespace CryptoPP;

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F"};
byte iv[ CryptoPP::AES::BLOCKSIZE ] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
byte iv2[ CryptoPP::AES::BLOCKSIZE ] = {"9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9", "9"};
string plain = "Hello World!";
string ans;

void cfb()
{
    string cipher, encoded;
    CFB_Mode< AES >::Encryption enc;
    enc.SetKeyWithIV( key, key.size(), iv );

    StringSource ss1( plain, true, new StreamTransformationFilter( enc,new StringSink( cipher ))); // StringSource
    StringSource ss2( cipher, true,new HexEncoder(new StringSink( encoded ))); // StringSource
    ans.pushback(encoded);
}

void cbc()
{
    string cipher, cipher2, encoded, encoded2;
    CBC_Mode< AES >::Encryption e;
    e.SetKeyWithIV( key, key.size(), iv );

    StringSource ss1( plain, true, new StreamTransformationFilter( e,new StringSink( cipher ))); // StringSource
    StringSource ss2( cipher, true,new HexEncoder(new StringSink( encoded ))); // StringSource
    ans.pushback(encoded);

    CBC_Mode< AES >::Encryption e2;
    e2.SetKeyWithIV( key, key.size(), iv2 );

    StringSource ss3( plain, true, new StreamTransformationFilter( e2,new StringSink( cipher2 ))); // StringSource
    StringSource ss4( cipher2, true,new HexEncoder(new StringSink( encoded2 ))); // StringSource
    ans.pushback(encoded2);
}

void ebc()
{
    string cipher, encoded;
    ECB_Mode< AES >::Encryption e;
    e.SetKey( key, key.size() );

    StringSource ss1( plain, true, new StreamTransformationFilter( e,new StringSink( cipher ))); // StringSource
    StringSource ss2( cipher, true,new HexEncoder(new StringSink( encoded ))); // StringSource
    ans.pushback(encoded);
}

int main()
{
    cfb();
    cbc();
    ebc();
    for(int i=0; i<4; i++)
    {
        cout << ans[i] << "\n";
    }

    return 0;
}