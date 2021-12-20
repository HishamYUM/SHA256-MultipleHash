#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>

#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>



char * read_binary(const char* filename) {


    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open\n");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = malloc(sb.st_size);
    read(fd, file_contents, sb.st_size);
    close(fd);
     return file_contents;
}




void main(int argc, char *argv[])
{

if (argc !=5){
				fprintf(stderr, "Something went wrong");
    exit(EXIT_FAILURE);}
char *file1 = read_binary(argv[3]);
char *file2 = read_binary(argv[4]);
EVP_MD_CTX mdctx;
const EVP_MD *md;
char *mess1 = strcat(file1, file2);
//printf("%s", mess1);
int nm = atoi(argv[2]);

unsigned char md_value[EVP_MAX_MD_SIZE];
int md_len, i;
char hash[1024];
OpenSSL_add_all_digests();

if(!argv[1]) {
       printf("Usage: mdtest digestname\n");
       exit(1);
}

md = EVP_get_digestbyname(argv[1]);

if(!md) {
       printf("Unknown message digest %s\n", argv[1]);
       exit(1);
}
 
// First hash:

EVP_MD_CTX_init(&mdctx);
EVP_DigestInit_ex(&mdctx, md, NULL);
EVP_DigestUpdate(&mdctx, mess1, strlen(mess1));
//EVP_DigestUpdate(&mdctx, mess2, strlen(mess2));
EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
EVP_MD_CTX_cleanup(&mdctx);
if (nm==1){
printf("The first hash value is :  ");
for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);
printf("\n");
}
/******************************************/

for (int k=0, j=0; k<md_len; k++){
			sprintf((char*)(hash+j), "%02x", md_value[k]);
		//	printf("%02x", md_value[k]);
   j += 2;
}


if (nm>1) {
for(int l =1; l<nm; l++){
EVP_MD_CTX_init(&mdctx);
EVP_DigestInit_ex(&mdctx, md, NULL);

EVP_DigestUpdate(&mdctx, hash, strlen(hash));
EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
EVP_MD_CTX_cleanup(&mdctx);


for (int k=0, j=0; k<md_len; k++){
			sprintf((char*)(hash+j), "%02x", md_value[k]);
			//printf("%02x", md_value[k]);
   j += 2;


}}}

printf("Digest is: ");
for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);
printf("\n");}
/*for(i = 0; i < md_len; i++) printf("%02x", hash[i]);

for(i = 0; i < md_len; i++) printf("%02x", hash[i]);
printf("\n%s", hash);*/

