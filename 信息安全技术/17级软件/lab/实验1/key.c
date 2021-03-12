#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  //EVP_CIPHER_CTX_set_padding(ctx, 0);

  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int append(char* buffer){
    int length = (int)strlen(buffer);
    if (length > 16)
        return False;
    memset(buffer+strlen(buffer),' ', 16-length);
    buffer[16] = '\0';
    return True;

}

int main(int argc, char const *argv[])
{
    char buffer[50];

    int i = 0;
    char iv[17];
    memset(iv, 0, 17);

    unsigned char *plaintext = "This is a top secret.";
    unsigned char ciphertext[100];
    unsigned char *cryptotext="8d20e5056a8d24d0462ce74e4904c1b513e10d1df4a2ef2ad4540fae1ca0aaf9";

    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    int ciphertext_len;
    int k=0;
    FILE *fp = fopen("words.txt", "r");
    while (fscanf(fp, "%s\n", buffer) != EOF){
        k++;
        if (!append(buffer))
            continue;

        ciphertext_len = encrypt(plaintext, strlen(plaintext), buffer, iv, ciphertext);

        unsigned char cryptohex[50];
        for (i = 0; i < ciphertext_len; i++)
        {
            sprintf(cryptohex+i*2,"%02x", ciphertext[i]);

        }
        cryptohex[ciphertext_len*2] = '\0';


        if (0 == strcmp(cryptohex, cryptotext)){
            printf("The key is: %s, cryptohex is %s\n", buffer, cryptohex);
            break;
        }
    }
    //printf("k is %d\n", k);

    EVP_cleanup();
    ERR_free_strings();
    return 0;
}

