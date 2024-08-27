#include "lib/ArgParser.h"
#include <gtest/gtest.h>

TEST(HamArcTestSuite, HammingEncodeTest) {
    Hamming hamming;
    std::vector<uint8_t> data = {1, 0, 0, 1, 0, 1, 0, 0};
    data = hamming.HammingEncode(data);
    std::vector<uint8_t> result = {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0};
    ASSERT_EQ(data, result);
}

TEST(HamArcTestSuite, HammingDecodeTest) {
    Hamming hamming;
    std::vector<uint8_t> data = {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0};
    data = hamming.HammingDecode(data);
    std::vector<uint8_t> result = {1, 0, 0, 1, 0, 1, 0, 0};
    ASSERT_EQ(data, result);
}

TEST(HamArcTestSuite, HammingFixBitDecodeTest) {
    Hamming hamming;
    std::vector<uint8_t> data = {0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0};
    data[6] ^= 1;
    data = hamming.HammingDecode(data);
    std::vector<uint8_t> result = {1, 0, 0, 1, 0, 1, 0, 0};
    ASSERT_EQ(data, result);
}

TEST(HamArcTestSuite, CreateArchive) {
    std::string path = "../ham.haf";
    Archiver archiver(path);
    archiver.CreateArchive();
    ASSERT_TRUE(std::filesystem::exists(path));
}

TEST(HamArcTestSuite, AppendFile) {
    std::string path = "../ham.haf";
    Archiver archiver(path);
    archiver.CreateArchive();
    std::string path_of_file = "../b.txt";
    std::string path_of_file2 = "../c.txt";
    std::ofstream ofs1(path_of_file);
    ofs1 << "qwerty";
    std::ofstream ofs2(path_of_file2);
    ofs2 << "asdf";
    archiver.AppendFile(path_of_file);
    archiver.AppendFile(path_of_file2);
    std::vector<std::string> all_files = archiver.List();
    bool contains_file = (all_files[0] == "b.txt" && all_files[1] == "c.txt");
    ASSERT_TRUE(contains_file);
}

TEST(HamArcTestSuite, DeleteFile) {
    std::string path = "../ham.haf";
    Archiver archiver(path);
    archiver.CreateArchive();
    std::string path_of_file = "../b.txt";
    std::string path_of_file2 = "../c.txt";
    std::ofstream ofs1(path_of_file);
    ofs1 << "qwerty";
    std::ofstream ofs2(path_of_file2);
    ofs2 << "asdf";
    archiver.AppendFile(path_of_file);
    archiver.AppendFile(path_of_file2);
    std::vector<std::string> delete_files = {"b.txt"};
    archiver.Delete(delete_files);
    std::vector<std::string> answer = {"c.txt"};
    ASSERT_TRUE(answer == archiver.List());
}

TEST(HamArcTestSuite, List) {
    std::string path = "../ham.haf";
    Archiver archiver(path);
    archiver.CreateArchive();
    std::string path_of_file = "../b.txt";
    std::string path_of_file2 = "../c.txt";
    std::ofstream ofs1(path_of_file);
    ofs1 << "qwerty";
    std::ofstream ofs2(path_of_file2);
    ofs2 << "asdf";
    archiver.AppendFile(path_of_file);
    archiver.AppendFile(path_of_file2);
    std::vector<std::string> list = {"b.txt", "c.txt"};
    std::vector<std::string> answer = archiver.List();
    ofs1.close();
    ofs2.close();
    ASSERT_TRUE(list == answer);
}