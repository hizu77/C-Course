#include "FileInfo.h"

namespace sse {
WordInfo::WordInfo(size_t idx, const std::vector<size_t>& lines)
        : file_index(idx), words_lines(lines) {}


MetaFileInfo::MetaFileInfo(const std::string& file, size_t words)
        : filename(file), words_counter(words) {}

FileScore::FileScore(const WordInfo& word, double score)
        : word_(word), score_(score) {}

} //end of namespace sse

