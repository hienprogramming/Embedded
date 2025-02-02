#include <iostream>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/rand.h>

// Hàm thêm padding theo chuẩn PKCS#7
void add_padding(unsigned char* data, int original_len, int block_size) {
    int padding_len = block_size - (original_len % block_size);
    for (int i = 0; i < padding_len; ++i) {
        data[original_len + i] = padding_len;
    }
}

// Hàm loại bỏ padding theo chuẩn PKCS#7
int remove_padding(unsigned char* data, int padded_len) {
    int padding_len = data[padded_len - 1];
    return padded_len - padding_len;
}

// Hàm tạo khóa AES ngẫu nhiên
void generate_aes_key(unsigned char* key) {
    RAND_bytes(key, AES_BLOCK_SIZE); // Tạo khóa AES 128-bit
}

// Hàm mã hóa AES-CBC
void encrypt_aes(const unsigned char* plaintext, int plaintext_len, const unsigned char* key, unsigned char* iv, unsigned char* ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Sao chép plaintext vào buffer tạm thời để thêm padding
    unsigned char padded_plaintext[128];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    add_padding(padded_plaintext, plaintext_len, AES_BLOCK_SIZE);

    // Mã hóa dữ liệu đã padding
    AES_cbc_encrypt(padded_plaintext, ciphertext, 128, &aes_key, iv, AES_ENCRYPT);
}

// Hàm giải mã AES-CBC
void decrypt_aes(const unsigned char* ciphertext, int ciphertext_len, const unsigned char* key, unsigned char* iv, unsigned char* decryptedtext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    // Giải mã dữ liệu
    AES_cbc_encrypt(ciphertext, decryptedtext, ciphertext_len, &aes_key, iv, AES_DECRYPT);

    // Loại bỏ padding
    int unpadded_len = remove_padding(decryptedtext, ciphertext_len);
    decryptedtext[unpadded_len] = '\0'; // Đảm bảo chuỗi kết thúc bằng null
}

// Mô phỏng ECU
class ECU {
public:
    ECU(const std::string& name, const unsigned char* key) : name(name) {
        memcpy(this->key, key, AES_BLOCK_SIZE);
    }

    void send_command(const std::string& command) {
        std::cout << "[" << name << "] Sending command: " << command << std::endl;

        // Khởi tạo IV ngẫu nhiên
        unsigned char iv[AES_BLOCK_SIZE];
        RAND_bytes(iv, AES_BLOCK_SIZE);

        // Sao chép IV để sử dụng trong quá trình mã hóa/giải mã
        unsigned char iv_copy[AES_BLOCK_SIZE];
        memcpy(iv_copy, iv, AES_BLOCK_SIZE);

        // Mã hóa lệnh
        unsigned char ciphertext[128];
        int len = command.size();
        encrypt_aes(reinterpret_cast<const unsigned char*>(command.c_str()), len, key, iv, ciphertext);

        std::cout << "[" << name << "] Encrypted command: ";
        for (int i = 0; i < 128; ++i) {
            printf("%02x", ciphertext[i]);
        }
        std::cout << std::endl;

        // Giả lập gửi dữ liệu qua CAN bus
        receive_command(ciphertext, 128, iv_copy);
    }

    void receive_command(const unsigned char* ciphertext, int len, unsigned char* iv) {
        std::cout << "[" << name << "] Received encrypted message: ";
        for (int i = 0; i < len; ++i) {
            printf("%02x", ciphertext[i]);
        }
        std::cout << std::endl;

        // Giải mã lệnh
        unsigned char decryptedtext[128];
        decrypt_aes(ciphertext, len, key, iv, decryptedtext);

        std::cout << "[" << name << "] Decrypted command: " << decryptedtext << std::endl;
    }

private:
    std::string name;
    unsigned char key[AES_BLOCK_SIZE];
};

int main() {
    // Tạo khóa chung cho cả hai ECU
    unsigned char shared_key[AES_BLOCK_SIZE];
    generate_aes_key(shared_key);

    // Khởi tạo hai ECU
    ECU ecu_sender("ECU_Sender", shared_key);
    ECU ecu_receiver("ECU_Receiver", shared_key);

    // Lệnh điều khiển cần gửi
    std::string control_command = "Activate_Headlights";

    // ECU_Sender mã hóa và gửi lệnh qua CAN bus
    ecu_sender.send_command(control_command);

    return 0;
}


/*
Giải thích code
Khởi tạo khóa AES:
Sử dụng hàm RAND_bytes() từ OpenSSL để tạo một khóa ngẫu nhiên 128-bit (16 byte).
Mã hóa (Enscrypt):
Sử dụng thuật toán AES với chế độ CBC (Cipher Block Chaining).
Vector khởi tạo (IV) được tạo ngẫu nhiên và sử dụng cùng với khóa để mã hóa dữ liệu.
Giải mã (Descrypt):
Sử dụng cùng khóa và IV để giải mã dữ liệu.
Mô phỏng giao tiếp:
Hai ECU (ecu_sender và ecu_receiver) sử dụng cùng một khóa chung để mã hóa và giải mã.
ecu_sender gửi lệnh điều khiển đã mã hóa.
ecu_receiver nhận và giải mã lệnh.
*/