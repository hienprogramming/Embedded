#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16
#define BUFFER_SIZE 128

void add_padding(unsigned char *data, int original_len, int *padded_len) {
    int padding_len = BLOCK_SIZE - (original_len % BLOCK_SIZE);
    for (int i = 0; i < padding_len; ++i) {
        data[original_len + i] = padding_len;
    }
    *padded_len = original_len + padding_len;
}

int remove_padding(unsigned char *data, int padded_len) {
    int padding_len = data[padded_len - 1];
    return padded_len - padding_len;
}

void generate_aes_key(unsigned char *key) {
    RAND_bytes(key, BLOCK_SIZE);
}

void encrypt_aes(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *iv, unsigned char *ciphertext, int *cipher_len) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    unsigned char padded_plaintext[BUFFER_SIZE];
    memset(padded_plaintext, 0, BUFFER_SIZE);
    int actual_len;
    add_padding(padded_plaintext, plaintext_len, &actual_len);
    memcpy(padded_plaintext, plaintext, plaintext_len);

    AES_cbc_encrypt(padded_plaintext, ciphertext, actual_len, &aes_key, iv, AES_ENCRYPT);
    *cipher_len = actual_len;
}

void decrypt_aes(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *iv, unsigned char *decryptedtext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    AES_cbc_encrypt(ciphertext, decryptedtext, ciphertext_len, &aes_key, iv, AES_DECRYPT);

    int unpadded_len = remove_padding(decryptedtext, ciphertext_len);
    decryptedtext[unpadded_len] = '\0';
}

void send_command(const char *command, const unsigned char *key) {
    printf("[ECU_Sender] Sending command: %s\n", command);

    unsigned char iv[BLOCK_SIZE];
    RAND_bytes(iv, BLOCK_SIZE);
    unsigned char iv_backup[BLOCK_SIZE];
    memcpy(iv_backup, iv, BLOCK_SIZE); // Lưu IV để dùng lại

    unsigned char ciphertext[BUFFER_SIZE];
    memset(ciphertext, 0, BUFFER_SIZE);
    int len = strlen(command);
    int cipher_len;

    encrypt_aes((const unsigned char *)command, len, key, iv, ciphertext, &cipher_len);

    printf("[ECU_Sender] Encrypted command: ");
    for (int i = 0; i < cipher_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    receive_command(ciphertext, cipher_len, key, iv_backup);
}

void receive_command(const unsigned char *ciphertext, int len, const unsigned char *key, unsigned char *iv) {
    printf("[ECU_Receiver] Received encrypted message: ");
    for (int i = 0; i < len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    unsigned char decryptedtext[BUFFER_SIZE];
    memset(decryptedtext, 0, BUFFER_SIZE);

    decrypt_aes(ciphertext, len, key, iv, decryptedtext);

    printf("[ECU_Receiver] Decrypted command: %s\n", decryptedtext);
}

int main() {
    unsigned char shared_key[BLOCK_SIZE];
    generate_aes_key(shared_key);

    const char *control_command = "Activate_Headlights";

    send_command(control_command, shared_key);

    return 0;
}
