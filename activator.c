#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;

#define _BYTE  uint8
#define _DWORD uint32

#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define BYTE1(x)      BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)      BYTEn(x,  2)

char key_valid[] = "v4GzX5wH9RZe3K8Mp1Ay7iO0d6Sb2ToDQUnVaYcLgNhjkImqCrFPstBuEfWxJ";

unsigned int ciph2[25] = { 0xB0435, 0x11653, 0x180313, 0x60873, 0x141035, 0x100753,
 0x10D31, 0x11137, 0x111551, 0x957, 0x0C0F17, 0x131453, 0x80F15,
 0x30B75, 0x11313, 0x141671, 0x0E0E37, 0x30151, 0xC0237, 0x110053,
 0x40235, 0x70B13, 0x41273, 0x170371, 0x91435
};

int check_actkey(char* actkey, char* regkey)
{
    int v2;
    int64_t i;
    int actkeychar_idx;
    unsigned int v5;
    char* v6;
    int64_t v7;
    int v8;
    char* v9;
    int64_t v10;
    char* v11;


    LOBYTE(v2) = 1;
    for(i = 0; i < 25; ++i)
    {
        v11 = strchr(key_valid, actkey[(int)i + (int)i / 5]);
        if (v11)
            actkeychar_idx = v11 - key_valid;
        else
            actkeychar_idx = 0x3d;

        v5 = ciph2[i];
        v6 = strchr(key_valid, regkey[BYTE2(v5) / 5u + BYTE2(v5)]);
        if (v6)
            v7 = v6 - key_valid;
        else
            LODWORD(v7) = 0x3d;

        v8 = v7 * ((uint8_t)v5 >> 4);
        v9 = strchr(key_valid, regkey[BYTE1(v5) / 5u + BYTE1(v5)]);
        if (v9)
            v10 = v9 - key_valid;
        else
            LODWORD(v10) = 0x3d;

        v2 = ((v8 + (unsigned int)v10 * (v5 & 0xF)) % 0x3D == actkeychar_idx) & (uint8_t)v2;
    }
    return v2;
}

char* brute_force(char* regkey)
{
    char *actkey = malloc(sizeof(char) * 30);
    actkey[5] = '-';
    actkey[11] = '-';
    actkey[17] = '-';
    actkey[23] = '-';
    actkey[29] = '\0';

    int v2;
    int64_t i;
    int actkeychar_idx;
    unsigned int v5;
    char* v6;
    int64_t v7;
    int v8;
    char* v9;
    int64_t v10;
    char* v11;


    LOBYTE(v2) = 1;
    for (i = 0; i < 25; ++i)
    {
        for (int k = 0; k < strlen(key_valid); ++k)
        {
            actkey[(int)i + (int)i / 5] = key_valid[k];

            v11 = strchr(key_valid, actkey[(int)i + (int)i / 5]);
            if (v11)
                actkeychar_idx = v11 - key_valid;
            else
                actkeychar_idx = 0x3d;

            v5 = ciph2[i];
            v6 = strchr(key_valid, regkey[BYTE2(v5) / 5u + BYTE2(v5)]);
            if (v6)
                v7 = v6 - key_valid;
            else
                LODWORD(v7) = 0x3d;

            v8 = v7 * ((uint8_t)v5 >> 4);
            v9 = strchr(key_valid, regkey[BYTE1(v5) / 5u + BYTE1(v5)]);
            if (v9)
                v10 = v9 - key_valid;
            else
                LODWORD(v10) = 0x3d;

            v2 = ((v8 + (unsigned int)v10 * (v5 & 0xF)) % 0x3D == actkeychar_idx) & (uint8_t)v2;
            if(!v2)
            {
                LOBYTE(v2) = 1;
            }
            else
            {
                break;
            }
        }
    }
    return actkey;
}



int main()
{
    char regkey[29];
    printf("Welcome to Lingea Lexicon 7 activator\n");
    printf("Enter as your product key <THE INSTALLER NAME WITHOUT SUFFIX>-111111, ex. LX7ENCS3-111111\n");
    printf("Enter your registration key: ");
    for(int i = 0; i < 29; ++i)
        regkey[i] = (char)fgetc(stdin);
    
    char *actkey = brute_force(regkey);
    printf("Activation key: %s\n", actkey);
    free(actkey);
    return 0;
}