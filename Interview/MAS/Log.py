import re
import chardet

def detect_encoding(file_path):
    with open(file_path, 'rb') as file:
        raw_data = file.read()
    result = chardet.detect(raw_data)
    return result['encoding']

def process_output_file(input_file, output_file):
    encoding = detect_encoding(input_file)
    with open(input_file, 'r', encoding=encoding) as file:
        lines = file.readlines()
    
    processed_lines = []
    for line in lines:
        processed_lines.append(line)
        
        # Add the Description line after lines containing Timestamp:
        if re.match(r'\s*Timestamp:', line):
            processed_lines.append('  Description: This is a test description.\n')

    with open(output_file, 'w', encoding=encoding) as file:
        file.writelines(processed_lines)

# Update the paths to your input and output files
input_file = r'D:\C-development\Interview\MAS\Output.txt'
output_file = r'D:\C-development\Interview\MAS\output_LOG.txt'
process_output_file(input_file, output_file)
