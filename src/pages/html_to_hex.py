#!/usr/bin/env python3
"""
Convert HTML file to C header file with gzipped content
Usage: python convert.py input.html output.h
"""

import sys
import gzip
import os


def html_to_header(input_file, output_file):
    """Convert HTML file to gzipped C header"""

    # Read HTML file
    with open(input_file, 'rb') as f:
        html_content = f.read()

    # Compress with gzip
    compressed = gzip.compress(html_content)

    # Create output directory if needed
    os.makedirs(os.path.dirname(output_file) or '.', exist_ok=True)

    # Write C header file
    with open(output_file, 'w') as f:
        f.write('#ifndef PAGE_INDEX_H\n')
        f.write('#define PAGE_INDEX_H\n\n')
        f.write('#ifdef __cplusplus\n')
        f.write('extern "C" {\n')
        f.write('#endif\n\n')

        # Write compressed data as byte array
        f.write('static const unsigned char page_index[] = {\n    ')

        # Write bytes in groups of 12 for readability
        for i, byte in enumerate(compressed):
            f.write(f'0x{byte:02x}')
            if i < len(compressed) - 1:
                f.write(', ')
            if (i + 1) % 12 == 0:
                f.write('\n    ')

        f.write('\n};\n\n')

        # Write length
        f.write(f'static const unsigned int page_index_len = {len(compressed)};\n\n')

        f.write('#ifdef __cplusplus\n')
        f.write('}\n')
        f.write('#endif\n\n')
        f.write('#endif /* PAGE_INDEX_H */\n')

    print(f"✅ Converted {input_file} -> {output_file}")
    print(f"   Original size: {len(html_content)} bytes")
    print(f"   Compressed size: {len(compressed)} bytes")
    print(f"   Compression ratio: {len(compressed) / len(html_content) * 100:.1f}%")


def main():


    input_file = input("Enter input file: ")
    output_file = input("Enter output file: ")

    if not os.path.exists(input_file):
        print(f"❌ Error: Input file '{input_file}' not found!")
        sys.exit(1)

    html_to_header(input_file, output_file)


if __name__ == '__main__':
    main()