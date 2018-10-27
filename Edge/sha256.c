#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
void PrintHex(unsigned char a)
{
	unsigned char buf = a>>4;
	if(buf >= 10)
		printf("%c", buf-10+'A');
	else
		printf("%hhu", buf);
	buf = a&0xf;
	if(buf >= 10)
		printf("%c", buf-10+'A');
	else
		printf("%hhu", buf);
}
void sha256_hash(const char str[])
{
    size_t len = strlen(str);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, len);
    SHA256_Final(hash, &sha256);
    int i;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        PrintHex(hash[i]);
	printf(" ");
    }
}

int main() {
    sha256_hash("ggwp");
    puts("");
    return 0;
}
