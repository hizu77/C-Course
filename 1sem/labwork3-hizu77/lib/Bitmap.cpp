#include "Bitmap.h"

void White(uint8_t* inf) {
    inf[40] = kCodeOfColor255;
    inf[41] = kCodeOfColor255;
    inf[42] = kCodeOfColor255;
}

void Green(uint8_t* inf) {
    inf[44] = kCodeOfColor0;
    inf[45] = kCodeOfColor255;
    inf[46] = kCodeOfColor0;
}

void Yellow(uint8_t* inf) {
    inf[48] = kCodeOfColor0;
    inf[49] = kCodeOfColor255;
    inf[50] = kCodeOfColor255;
}

void Purple(uint8_t* inf) {
    inf[52] = kCodeOfColor255;
    inf[53] = kCodeOfColor0;
    inf[54] = kCodeOfColor139;
}

void ConvertToBmp(int64_t x, int64_t y, int64_t start_x, int64_t start_y, int64_t** array, const std::string& Output) {

    ++x; ++y;
    int64_t width = (x + 1) / 2; // ceil up
    int64_t padding_size = (kBmpWidthLeveling - width % kBmpWidthLeveling) % kBmpWidthLeveling; //padding
    int64_t fSize = kInfoHeaderSizeWithColors + kFileHeaderSize + y * (width + padding_size);

    uint8_t file_header[kFileHeaderSize] = {
            0, 0, // BM
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
    };

    uint8_t info_header[kInfoHeaderSizeWithColors] = {
            0, 0, 0, 0, // Size
            0, 0, 0, 0, // Width
            0, 0, 0, 0, // Height
            0, 0,
            0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,

            0, 0, 0, 0,
            0, 0, 0, 0, //color
            0, 0, 0, 0, // color
            0, 0, 0, 0, // color
            0, 0, 0, 0, // color
    };

    file_header[0] = (uint8_t) 'B';
    file_header[1] = (uint8_t) 'M';
    file_header[2] = (uint8_t) fSize;
    file_header[3] = (uint8_t) fSize >> kShiftOneByte;
    file_header[4] = (uint8_t) fSize >> kShiftTwoByte;
    file_header[5] = (uint8_t) fSize >> kShiftThreeByte;
    file_header[10] = (uint8_t) (kFileHeaderSize + kInfoHeaderSizeWithColors);

    info_header[0] = (uint8_t) kSizeOfInfoHeader;

    info_header[4] = (uint8_t) x;
    info_header[5] = (uint8_t) x >> kShiftOneByte;
    info_header[6] = (uint8_t) x >> kShiftTwoByte;
    info_header[7] = (uint8_t) x >> kShiftThreeByte;

    info_header[8] = (uint8_t) y;
    info_header[9] = (uint8_t) y >> kShiftOneByte;
    info_header[10] = (uint8_t) y >> kShiftTwoByte;
    info_header[11] = (uint8_t) y >> kShiftThreeByte;

    info_header[12] = (uint8_t) kAmountPlanes;
    info_header[14] = (uint8_t) kBitsPerPixel;
    info_header[32] = (uint8_t) kAmountColors;

    White(info_header);
    Green(info_header);
    Yellow(info_header);
    Purple(info_header);

    std::ofstream file_write_Output;
    file_write_Output.open(Output, std::ios::out | std::ios::binary);
    if (!file_write_Output.is_open()) {
        return;
    }

    file_write_Output.write(reinterpret_cast<char*>(file_header), kFileHeaderSize);
    file_write_Output.write(reinterpret_cast<char*>(info_header), kInfoHeaderSizeWithColors);

    uint8_t padding = 0;

    for (int64_t i = start_y; i < y + start_y; ++i) {
        for (int64_t j = start_x; j < x + start_x; j += 2) {
            uint8_t current_color;
            uint8_t previous_color;
            uint8_t nex_color = 0;

            previous_color = static_cast<char>(array[i][j]);
            nex_color = static_cast<char>(array[i][j + 1]);

            current_color = (previous_color << 4) | nex_color;
            file_write_Output.write(reinterpret_cast<char*>(&current_color), 1);
        }

        file_write_Output.write(reinterpret_cast<char*>(&padding), padding_size);

    }

    file_write_Output.close();
}
