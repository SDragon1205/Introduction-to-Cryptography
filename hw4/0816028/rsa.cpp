#pragma comment(lib, "cryptlib.lib")
#include <CryptoPP/integer.h>
#include <CryptoPP/nbtheory.h>
#include <CryptoPP/osrng.h>
#include <CryptoPP/rsa.h>
#include <CryptoPP/sha.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::runtime_error;
using namespace std;
using namespace CryptoPP;

Integer c1, c2;
string r1;

void aaa()
{
    Integer e("0x11"), n("0xb2c8d1404ed5fc2f7ad1254bb428f0d5");
    RSA::PublicKey pubKey;
    pubKey.Initialize(n, e);

    string message, recovered;
    Integer m, c, r;

    message = "Hello World!";
    //cout << "message: " << message << endl;

    // Treat the message as a big endian array
    m = Integer((const byte*)message.data(), message.size());//
    //cout << "m: " << hex << m << endl;

    // Encrypt
    c1 = pubKey.ApplyFunction(m);//

}

void bbb()
{
    Integer e("0x10001"), n("0xcf625a8e47bc1cf9a3b517b31d870108c0cd97466003842a3b394d6cd857e9b7");
    RSA::PublicKey pubKey;
    pubKey.Initialize(n, e);

    string message, recovered;
    Integer m, c, r;

    message = "RSA is public key.";
    //cout << "message: " << message << endl;

    // Treat the message as a big endian array
    m = Integer((const byte*)message.data(), message.size());
    //cout << "m: " << hex << m << endl;

    // Encrypt
    c2 = pubKey.ApplyFunction(m);

}

void ccc()
{
    AutoSeededRandomPool prng;
    Integer d("0x12e6a85100b889c9905a939b274a91bc57ca85d52e6c464fb455c86a29d63c89"), n("0xd6361e40b2d619970ead338912a273adb75a4ce21356304834753fe94e6de24b"), e("0x11");
    RSA::PrivateKey privKey;
    privKey.Initialize(n, e, d);

    string recovered;
    Integer c("0xa1676afd68a2fc67dac32c633600b76fa90aca9f9cca5201490a20c8b01a061a"), r;

    // Decrypt
    r = privKey.CalculateInverse(prng, c);
    //cout << "r: " << hex << r << endl;

    // Round trip it
    size_t req = r.MinEncodedSize();
    r1.resize(req);
    r.Encode((byte*)&r1[0], r1.size());

}

int main(int argc, char* argv[])
{
    ofstream out("out.txt");
    aaa();
    bbb();
    ccc();

    out << hex << c1 << endl;
    out << hex << c2 << endl;
    out << r1 << endl;
    out << "11h" << endl;

    return 0;
}