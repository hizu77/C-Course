#pragma once

#include <cstdint>
#include <string>
#include <fstream>

static const int8_t kFileHeaderSize = 14;
static const int8_t kInfoHeaderSizeWithColors = 60;
static const uint8_t kBmpWidthLeveling = 4;
static const uint8_t kShiftOneByte = 8;
static const uint8_t kShiftTwoByte = 16;
static const uint8_t kShiftThreeByte = 24;
static const uint8_t kBitsPerPixel = 4;
static const uint8_t kAmountColors = 16;
static const uint8_t kAmountPlanes = 1;
static const uint8_t kSizeOfInfoHeader = 40;

static const uint16_t kCodeOfColor255 = 255;
static const uint16_t kCodeOfColor139 = 139;
static const uint16_t kCodeOfColor0 = 0;


void White(uint8_t *inf);

void Green(uint8_t *inf);

void Yellow(uint8_t *inf);

void Purple(uint8_t *inf);

void ConvertToBmp(int64_t x, int64_t y, int64_t start_x, int64_t start_y, int64_t **array, const std::string& Output);


