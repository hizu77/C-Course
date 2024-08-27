#include <gtest/gtest.h>
#include "ProgramManager.h"

using namespace sse;
TEST(ParserTestSuit, PrefixTest1) {
    OpController parse;
    std::string input = "and AND day";
    std::string OK = "A and day";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest2) {
    OpController parse;
    std::string input = "and OR day";
    std::string OK = "O and day";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest3) {
    OpController parse;
    std::string input = "(and)";
    std::string OK = "and";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest4) {
    OpController parse;
    std::string input = "(and AND day)";
    std::string OK = "A and day";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest5) {
    OpController parse;
    std::string input = "(and OR day)";
    std::string OK = "O and day";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest6) {
    OpController parse;
    std::string input = "(and AND day)";
    std::string OK = "A and day";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest7) {
    OpController parse;
    std::string input = "(and OR day) AND yes";
    std::string OK = "A O and day yes";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest8) {
    OpController parse;
    std::string input = "for AND and";
    std::string OK = "A for and";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest9) {
    OpController parse;
    std::string input = "for AND and";
    std::string OK = "A for and";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest10) {
    OpController parse;
    std::string input = "((for OR and)) AND yes OR no";
    std::string OK = "O A O for and yes no";
    std::string output = parse.Convert(input);
    ASSERT_EQ(OK, output);
}

TEST(ParserTestSuit, PrefixTest11) {
    OpController parse;
    std::string input = "for AND";
    ASSERT_ANY_THROW(parse.Convert(input));
}

TEST(ParserTestSuit, PrefixTest12) {
    OpController parse;
    std::string input = "vector list";
    ASSERT_ANY_THROW(parse.Convert(input));
}

TEST(ParserTestSuit, PrefixTest13) {
    OpController parse;
    std::string input = "for AND OR list";
    ASSERT_ANY_THROW(parse.Convert(input));
}

TEST(ParserTestSuit, PrefixTest14) {
    OpController parse;
    std::string input = "vector Or list";
    ASSERT_ANY_THROW(parse.Convert(input));
}

TEST(EncodeVarintTestSuit, VarintTest1) {
    VarintController varint;
    size_t index = 1;
    std::vector<size_t> files = {414, 235, 631, 531};
    std::vector<size_t> result = {1, 414, 235, 631, 531};
    ASSERT_EQ(varint.Decode(varint.Encode(index, files)), result);
}

TEST(EncodeVarintTestSuit, VarintTest2) {
    VarintController varint;
    size_t index = 1;
    std::vector<size_t> files = {41411144, 23500000000, 631111111111, 531222222222};
    std::vector<size_t> result = {1, 41411144, 23500000000, 631111111111, 531222222222};
    ASSERT_EQ(varint.Decode(varint.Encode(index, files)), result);
}

TEST(EncodeVarintTestSuit, IndexTest1) {
    IndexManager index_manager;
    std::stringstream output;
    std::stringstream input("lol kek balbes ahahaha \n lol \n lol kek molodec c++ 42");
    index_manager.IndexFiles("name", input, output);
    std::string ok = "1 7 1 name 10 42 1 2 \x1\x3 ahahaha 1 2 \x1\x1 molodec 1 2 \x1\x3 balbes 1 2 \x1\x1 c++ 1 2 \x1\x3 kek 1 3 \x1\x1\x2 lol 1 4 \x1\x1\x1\x1 ";
    ASSERT_EQ(ok, output.str());
}

TEST(EncodeVarintTestSuit, SearchByIndexTest) {
    std::stringstream index("1 7 1 name 10 42 1 2 \x1\x3 ahahaha 1 2 \x1\x1 molodec 1 2 \x1\x3 balbes 1 2 \x1\x1 c++ 1 2 \x1\x3 kek 1 3 \x1\x1\x2 lol 1 4 \x1\x1\x1\x1 ");
    std::stringstream output;

    std::string command = "lol";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : name\nLines : 1 2 3 \n";
    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, SearchFull1) {
    std::stringstream input("lol kek balbes ahahaha \n lol \n lol kek molodec c++ 42");

    IndexManager indexer;
    std::stringstream index;
    indexer.IndexFiles("name", input, index);
    std::stringstream output;

    std::string command = "lol";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : name\nLines : 1 2 3 \n";
    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, SearchFull2) {
    std::stringstream input("#include <iostream>\n"
                            "\n"
                            "int main() {\n"
                            "    std::cout << \"Hello World!\";\n"
                            "    return 0;\n"
                            "}");

    IndexManager indexer;
    std::stringstream index;
    indexer.IndexFiles("HelloWorld", input, index);
    std::stringstream output;

    std::string command = "iostream";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : HelloWorld\nLines : 1 \n";

    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, SearchFullNotFind) {
    std::stringstream input("#include <iostream>\n"
                            "\n"
                            "int main() {\n"
                            "    std::cout << \"Hello World!\";\n"
                            "    return 0;\n"
                            "}");

    IndexManager indexer;
    std::stringstream index;
    indexer.IndexFiles("HelloWorld", input, index);
    std::stringstream output;

    std::string command = "vector";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Word not found\n";
    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, MultySearchTest) {
    std::stringstream index("2 11 2 3.txt 10 1 2.txt 9 genii 1 2 \u0002\u0001 ahahahah 1 2 \u0002\u0002 a 1 2 \u0001\u0003 maladec 2 2 \u0001\u0004 2 \u0002\u0001 net 1 2 \u0001\u0003 ti 2 2 \u0001\u0003 2 \u0002\u0002 ya 2 3 \u0001\u0003\u0001 2 \u0002\u0001 balbes 2 2 \u0001\u0003 2 \u0002\u0002 lol 2 2 \u0001\u0002 2 \u0002\u0002 c++ 1 2 \u0002\u0001 kek 2 2 \u0001\u0001 3 \u0002\u0003\u0001 ");
    std::stringstream output;

    std::string command = "lol";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : 3.txt\nLines : 2 \nFilename : 2.txt\nLines : 2 \n";
    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, MultySearchTestMultyCommand) {
    std::stringstream index("2 11 2 3.txt 10 1 2.txt 9 genii 1 2 \u0002\u0001 ahahahah 1 2 \u0002\u0002 a 1 2 \u0001\u0003 maladec 2 2 \u0001\u0004 2 \u0002\u0001 net 1 2 \u0001\u0003 ti 2 2 \u0001\u0003 2 \u0002\u0002 ya 2 3 \u0001\u0003\u0001 2 \u0002\u0001 balbes 2 2 \u0001\u0003 2 \u0002\u0002 lol 2 2 \u0001\u0002 2 \u0002\u0002 c++ 1 2 \u0002\u0001 kek 2 2 \u0001\u0001 3 \u0002\u0003\u0001 ");
    std::stringstream output;

    std::string command = "lol AND kek";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : 2.txt\nLines : 1 2 \nFilename : 3.txt\nLines : 2 3 4 \n";
    ASSERT_EQ(output.str(), OK);
}

TEST(EncodeVarintTestSuit, MultySearchTestMultyHardCommand) {
    std::stringstream index("2 11 2 3.txt 10 1 2.txt 9 genii 1 2 \u0002\u0001 ahahahah 1 2 \u0002\u0002 a 1 2 \u0001\u0003 maladec 2 2 \u0001\u0004 2 \u0002\u0001 net 1 2 \u0001\u0003 ti 2 2 \u0001\u0003 2 \u0002\u0002 ya 2 3 \u0001\u0003\u0001 2 \u0002\u0001 balbes 2 2 \u0001\u0003 2 \u0002\u0002 lol 2 2 \u0001\u0002 2 \u0002\u0002 c++ 1 2 \u0002\u0001 kek 2 2 \u0001\u0001 3 \u0002\u0003\u0001 ");
    std::stringstream output;

    std::string command = "(kek AND net) OR c++";
    SearchManager manager("in", 5, 1, 1);
    manager.Search(index, output, command);

    std::string OK = "Searching...\nFilename : 3.txt\nLines : 1 \nFilename : 2.txt\nLines : 1 3 \n";
    ASSERT_EQ(output.str(), OK);
}