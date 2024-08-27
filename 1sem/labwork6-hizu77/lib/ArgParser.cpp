#include "ArgParser.h"

void Parser::Manipulating(std::string& argument, std::vector<std::string>& files) {
    if (argument == "c" || argument == "create") {
        create_flag_ = true;
        return;
    }

    if (argument == "f" || argument == "file") {
        path_of_archive_ = files.back();
        files.clear();
        return;
    }

    if (argument == "l" || argument == "list") {
        list_flag_ = true;
        return;
    }

    if (argument == "x" || argument == "extract") {
        extract_flag_ = true;
        files_to_extract_ = files;
        files.clear();
        return;
    }

    if (argument == "a" || argument == "append") {
        append_flag_ = true;
        if (files.size() == 1) {
            file_to_append_ = files.back();
        } else {
            throw std::runtime_error("Append must have 1 file");

        }
        files.clear();
        return;

    }

    if (argument == "d" || argument == "delete") {
        delete_flag_ = true;
        if (files.size() == 1) {
            files_to_delete_ = files;
        }
        files.clear();
        return;
    }

    if (argument == "A" || argument == "concatenate") {
        concatenate_flag_ = true;
        if (files.size() == 2) {
            archives_to_concatenate_ = files;
        } else {
            throw std::runtime_error("Concatenate must have 2 archives");
        }
        files.clear();
        return;
    }

    if (argument == "r" || argument == "restore") {
        std::cout << "Flag of restore bits was turned off\n";
        restore_flag = false;
        return;
    }

    if (argument == "p" || argument == "parity") {
        std::cout << "Total parity bit was turned off\n";
        parity_flag = false;
        return;
    }

}

std::vector<std::string> ParseMonoOption(const std::string& arg) {
    std::vector<std::string> result;
    std::string temp_buffer;
    for (char i : arg) {
        if (i == '=') {
            result.push_back(temp_buffer);
            temp_buffer.clear();
        } else {
            temp_buffer += i;
        }
    }
    if (!temp_buffer.empty()) {
        result.push_back(temp_buffer);
    }
    if (result.size() < 2) {
        result.emplace_back("");
    }
    return result;
}


void Parser::Parse(int argc, char **argv) {
    std::vector<std::string> args(argc);

    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }
    return Parse(args);
}


void Parser::Parse() {
    Help();

    if (path_of_archive_.empty()) {
        throw std::runtime_error("Incorrect input");
    }

    std::cout << "Current archive has filepath : " << path_of_archive_ << '\n';
    Archiver archive(path_of_archive_, block_size_, restore_flag, parity_flag);

    if (create_flag_) {
        std::cout << "Creating archive with path : " << path_of_archive_ << '\n';
        archive.CreateArchive();
    }

    if (list_flag_) {
        std::cout << "List of files of current archive : ";
        for (auto& i : archive.List()) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }

    if (extract_flag_) {
        std::cout << "Extract files from archive : ";
        for (auto& i : files_to_extract_) {
            std::cout << i << " ";
        }
        std::cout << '\n';
        archive.Extract(files_to_extract_);
    }

    if (append_flag_) {
        std::cout << "Append file : " << file_to_append_ << '\n';
        archive.AppendFile(file_to_append_);
    }

    if (delete_flag_) {
        std::cout << "Delete files\n";
        for (auto& i : files_to_delete_) {
            std::cout << i << " ";
        }
        std::cout << '\n';
        archive.Delete(files_to_delete_);
    }

    if (concatenate_flag_) {
        std::filesystem::path archive_1 = archives_to_concatenate_[0];
        std::filesystem::path archive_2 = archives_to_concatenate_[1];
        std::cout << "Concatenating archives : " << archive_1 << " " << archive_2 << '\n';
        archive.Concatenate(archive_1, archive_2);
    }


}

void Parser::Parse(const std::vector<std::string>& args) {
    std::vector<std::string> files;

    for (size_t i = args.size() - 1; i > 0; --i) {
        if (args[i][0] == '-') {
            bool full_name_argument = true;
            if (args[i][1] != '-') {
                full_name_argument = false;
            }
            std::vector<std::string> params;

            params = ParseMonoOption(args[i]);

            if (full_name_argument) {
                params[0] = params[0].substr(2);
                if (params[0] == "file") {
                    files.push_back(params[1]);
                }

                if (params[0] == "bloсk") {
                    block_size_ = std::stoi(params[1]);
                } else {
                    Manipulating(params[0], files);
                }

            } else {
                params[0] = params[0].substr(1);
                Manipulating(params[0], files);
            }
        } else {
            files.push_back(args[i]);
        }
    }
    Parse();
}

void Parser::Help() const {
    std::cout << "All arguments: " << std::endl;

    std::cout << "-c (--create) - create archive\n";
    std::cout << "-f (--file)=[ARCHIVE_NAME] - name of a  archive\n";
    std::cout << "-l (--list) - print files in archive\n";
    std::cout << "-x (--extract) - extract files out of archive\n";
    std::cout << "-a (--append) - add the file to the archive\n";
    std::cout << "-d (--delete) - delete the file\n";
    std::cout << "-A (--concatenate) - merge two archives\n";

    std::cout << "There are default archive methods. Also you can choose mode of HammingCoder\nDefault flags were turned on\n\n";
}
