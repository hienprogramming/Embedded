'''
    This script checks the range of an Intel Hex file.
    Start Address and End Address of .hex file is printed.
'''

class hexfile():
    @staticmethod
    def check_hex_file_range(file_path):
        with open(file_path, 'r') as file:
            min_address = None
            max_address = None
            for line in file:
                if line.startswith(':'):
                    byte_count = int(line[1:3], 16)
                    address = int(line[3:7], 16)
                    if min_address is None or address < min_address:
                        min_address = address
                    if max_address is None or (address + byte_count) > max_address:
                        max_address = address + byte_count

        if min_address is not None and max_address is not None:
            print("Range of Intel Hex file:")
            print("Start Address:", hex(min_address))
            print("End Address:", hex(max_address))
        else:
            print("Invalid Intel Hex file or empty file.")

    @staticmethod
    def extract_c_code_from_hex(hex_file):
        c_code = ""
        with open(hex_file, 'r') as f:
            lines = f.readlines()
            for line in lines:
                if line.startswith(':'):
                    # Loại bỏ các ký tự đầu tiên (:), độ dài dữ liệu và checksum từ mỗi dòng
                    data = line[9:-2]
                    # Kiểm tra dữ liệu hex trước khi chuyển đổi
                    try:
                        # Chuyển đổi dữ liệu từ hex sang ASCII và thêm vào mã nguồn C
                        c_code += bytes.fromhex(data).decode('utf-8')
                    except ValueError:
                        # Bỏ qua các ký tự không hợp lệ
                        pass
        return c_code

if __name__ == '__main__':
    # Thay đổi đường dẫn file_path_hex thành đường dẫn của tệp Intel Hex trên máy tính của bạn
    file_path_hex = "D:\\C_Learning\\hexfile_upwork.hex"
    hexfile.extract_c_code_from_hex(file_path_hex)
    c_code = hexfile.extract_c_code_from_hex(file_path_hex)
    print(c_code)




