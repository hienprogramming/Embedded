# -*- coding: utf-8 -*-

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend
import os

BLOCK_SIZE = 16  # AES block size

# Hàm tạo khóa AES ngẫu nhiên
def generate_aes_key():
    return os.urandom(BLOCK_SIZE)

# Hàm mã hóa AES-CBC
def encrypt_aes(plaintext, key):
    iv = os.urandom(BLOCK_SIZE)  # Tạo IV ngẫu nhiên
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()

    # Thêm padding
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(plaintext.encode()) + padder.finalize()

    # Mã hóa dữ liệu
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    return iv, ciphertext

# Hàm giải mã AES-CBC
def decrypt_aes(iv, ciphertext, key):
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()

    # Giải mã dữ liệu
    decrypted_padded = decryptor.update(ciphertext) + decryptor.finalize()

    # Loại bỏ padding
    unpadder = padding.PKCS7(128).unpadder()
    decrypted_text = unpadder.update(decrypted_padded) + unpadder.finalize()
    
    return decrypted_text.decode()

# Mô phỏng ECU gửi lệnh
def send_command(command, key):
    print("[ECU_Sender] Sending command: {}".format(command))

    # Mã hóa lệnh
    iv, encrypted_command = encrypt_aes(command, key)

    print("[ECU_Sender] Encrypted command:", encrypted_command.hex())

    # Giả lập gửi dữ liệu qua CAN bus
    receive_command(iv, encrypted_command, key)

# Mô phỏng ECU nhận lệnh
def receive_command(iv, encrypted_command, key):
    print("[ECU_Receiver] Received encrypted message:", encrypted_command.hex())

    # Giải mã lệnh
    decrypted_command = decrypt_aes(iv, encrypted_command, key)

    print("[ECU_Receiver] Decrypted command: {}".format(decrypted_command))

# Chương trình chính
if __name__ == "__main__":
    shared_key = generate_aes_key()  # Tạo khóa chung cho ECU
    control_command = "Activate_Headlights"  # Lệnh điều khiển
    send_command(control_command, shared_key)
