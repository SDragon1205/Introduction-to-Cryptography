#pragma comment(lib, "cryptlib.lib")
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cryptoPP/cryptlib.h>
#include <cryptoPP/hex.h>
#include <cryptoPP/filters.h>
#include <cryptoPP/aes.h>
#include <cryptoPP/modes.h>
#include <fstream>
#include <vector>

using namespace std;
using namespace CryptoPP;

byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F' };
byte iv[CryptoPP::AES::BLOCKSIZE] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
byte iv2[CryptoPP::AES::BLOCKSIZE] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
byte iv3[CryptoPP::AES::BLOCKSIZE] = { '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9', '9' };
string plain = "AES is the block cipher standard.";
vector<string> ans;
vector<string> test;

void cfb()
{
    string cipher, encoded, recovered;
    CFB_Mode< AES >::Encryption enc(key, sizeof(key), iv, 4);

    StringSource ss1(plain, true, new StreamTransformationFilter(enc, new StringSink(cipher))); // StringSource
    StringSource ss2(cipher, true, new HexEncoder(new StringSink(encoded))); // StringSource
    ans.push_back(encoded);

	//StringSource ss87(cipher, true, new HexDecoder(new StringSink(encoded))); // StringSource
    CFB_Mode< AES >::Decryption dec(key, sizeof(key), iv, 4);
    //dec.SetKeyWithIV(key, sizeof(key), iv);

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource ss3(cipher, true,
        new StreamTransformationFilter(dec,
            new StringSink(recovered)
        ) // StreamTransformationFilter
    ); // StringSource
    test.push_back(recovered);
}

void cbc()
{
    string cipher, cipher2, encoded, encoded2, recovered, recovered2;
    CBC_Mode< AES >::Encryption e(key, sizeof(key), iv2);

    StringSource ss1(plain, true, new StreamTransformationFilter(e, new StringSink(cipher), StreamTransformationFilter::ZEROS_PADDING)); // StringSource
    StringSource ss2(cipher, true, new HexEncoder(new StringSink(encoded))); // StringSource
    ans.push_back(encoded);

    CBC_Mode< AES >::Encryption e2(key, sizeof(key), iv3);

    StringSource ss3(plain, true, new StreamTransformationFilter(e2, new StringSink(cipher2), StreamTransformationFilter::PKCS_PADDING)); // StringSource
    StringSource ss4(cipher2, true, new HexEncoder(new StringSink(encoded2))); // StringSource
    ans.push_back(encoded2);

    CBC_Mode< AES >::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv2);

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource ss5(cipher, true,
        new StreamTransformationFilter(d,
            new StringSink(recovered), StreamTransformationFilter::ZEROS_PADDING
        ) // StreamTransformationFilter
    ); // StringSource
    test.push_back(recovered);

    CBC_Mode< AES >::Decryption d2;
    d2.SetKeyWithIV(key, sizeof(key), iv3);

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource ss6(cipher2, true,
        new StreamTransformationFilter(d2,
            new StringSink(recovered2), StreamTransformationFilter::PKCS_PADDING
        ) // StreamTransformationFilter
    ); // StringSource
    test.push_back(recovered2);
}

void ecb()
{
    string cipher, encoded, recovered;
    ECB_Mode< AES >::Encryption e(key, sizeof(key));

    StringSource ss1(plain, true, new StreamTransformationFilter(e, new StringSink(cipher), StreamTransformationFilter::PKCS_PADDING)); // StringSource
    StringSource ss2(cipher, true, new HexEncoder(new StringSink(encoded))); // StringSource
    ans.push_back(encoded);

    //
    ECB_Mode< AES >::Decryption d;
    d.SetKey(key, sizeof(key));

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource ss3(cipher, true,
        new StreamTransformationFilter(d,
            new StringSink(recovered), StreamTransformationFilter::PKCS_PADDING
        ) // StreamTransformationFilter
    ); // StringSource
    test.push_back(recovered);
}

int main()
{
    //ofstream out("Out.txt");
    cfb();
    cbc();
    ecb();
    cout << "e:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << ans[i] << "\n";
    }
    cout << "d:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << test[i] << "\n";
    }

    return 0;
}
