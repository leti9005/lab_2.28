#include <iostream>
#include <fstream>

struct TString {
    const char end_marker = '$';
    static const size_t max_len = 80;
    char data[max_len + 1];

    size_t _next_search_pos;

    TString() {
        _next_search_pos = 0;
    };

    TString(const char *str, size_t len) {
        size_t new_len = len < max_len ? len : max_len;
        for (size_t i = 0; i < new_len; i++) {
            data[i] = str[i];
        }
        if(len < max_len) {
            data[len] = end_marker;
        } else {
            data[max_len] = end_marker;
        }
        _next_search_pos = 0;
    }

    size_t get_marker_pos() const {
        size_t i = 0;
        while(data[i] != end_marker && i < max_len) {
            i++;
        }
        return i;
    }

    ~TString() = default;

    bool _cmp(const char *s0, const char *s1, size_t len) {
        size_t i = 0;
        for(i = 0;i<len;i++) {
            if(s0[i] != s1[i] || (s0[i] == end_marker || s1[i] == end_marker)) {
                return false;
            }
        }
        return true;
    }

    int find(TString *what) {
        size_t search_len = get_marker_pos() - what->get_marker_pos();
        for(size_t i = _next_search_pos;i<=search_len;i++) {
            if(_cmp(&data[i], &what->data[0], what->get_marker_pos())) {
                return i;
            }
        }
        return -1;
    }

    void replace(TString *what, TString *replacer) {
        int find_position = find(what);
        while(find_position > 0 && find_position < max_len) {
            size_t newlen = get_marker_pos() - what->get_marker_pos() + replacer->get_marker_pos();
            if (newlen > max_len) {
                newlen = max_len;
            }
            char *tmp_data = new char[newlen + 1];
            if(newlen < max_len) {
                tmp_data[newlen] = end_marker;
            } else {
                tmp_data[max_len] = end_marker;
            }

            for(size_t i = 0;i<(size_t ) find_position;i++) {
                tmp_data[i] = data[i];
            }

            size_t replacer_len = replacer->get_marker_pos();
            for(size_t i=0;i<replacer_len;i++) {
                tmp_data[find_position + i] = replacer->data[i];
            }

            size_t old_tail_start = find_position + what->get_marker_pos();
            size_t new_tail_start = find_position + replacer->get_marker_pos();
            size_t tail_len = get_marker_pos() - old_tail_start;
            if(tail_len + new_tail_start > max_len) {
                tail_len = max_len - new_tail_start;
            }
            for(size_t i = 0;i<tail_len;i++) {
                tmp_data[new_tail_start + i] = data[old_tail_start + i];
            }
            size_t i = 0;
            while(tmp_data[i] != end_marker) {
                data[i] = tmp_data[i];
                i++;
            }
            data[i] = end_marker;

            delete []tmp_data;
            _next_search_pos = find_position + replacer->get_marker_pos();
            find_position = find(what);
        }
        _next_search_pos = 0;
    }

    std::string to_string(bool save_marker = false) const {
        if(save_marker) {
            return std::string(data, get_marker_pos() + 1);
        }
        return std::string(data, get_marker_pos());
    }

};

int main() {

    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Author: Dmitrii Tochanskii, 9005"  << std::endl;
    std::cout << "Start date: 01.06.2020. End date: 01.06.2020 Version 1.0.0" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::ifstream inputfile;
    inputfile.open("input.txt");
    if (!inputfile.good()) {
        std::cerr << "Input file error!" << std::endl;
        return -1;
    }

    std::string line;

    std::getline(inputfile, line);
    TString *source_line = new TString(line.data(), line.length());

    std::getline(inputfile, line);
    TString *what_to_replace = new TString(line.data(), line.length());

    std::getline(inputfile, line);
    TString *replace_with = new TString(line.data(), line.length());

    source_line->replace(what_to_replace, replace_with);

    std::ofstream outfile("output.txt");
    outfile << source_line->to_string(true);

    return 0;
}
