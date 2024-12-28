#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md5.h>

unsigned char result[MD5_DIGEST_LENGTH];

int main() {
	char prefix[] = "yzbqklnj";
	char buffer[256];

	for (int i = 0; i < 10000000; i++) {
		int len = snprintf(buffer, sizeof(buffer) - 1, "%s%d", prefix, i);
		MD5((unsigned char*) buffer, len, result);
		if (result[0] == 0 && result[1] == 0 && result[2] == 0) {
			for (int j = 0; j < MD5_DIGEST_LENGTH; j++)
				printf("%02x", result[j]);
			printf("\t%d\n", i);
		}
	}

	return 0;
}
