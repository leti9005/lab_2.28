#include <iostream>
#include <fstream>

struct TString {
    char *_ptr;
    size_t _len;
    size_t _next_search_pos;
    int _found_pos;
    int what_len;

    TString() {
        _ptr = nullptr;
        _len = 0;
        _next_search_pos = 0;
        _found_pos = -1;
        what_len = 0;
    };

    TString(const char *str, size_t len) {
        _len = len;
        _ptr = new char[len];
        for (size_t i = 0; i < len; i++) {
            _ptr[i] = str[i];
        }
        _next_search_pos = 0;
    }

    ~TString(){
        delete _ptr;
    }

    bool _cmp(const char *s0, const char *s1, size_t len) {
        size_t i = 0;
        for(i = 0;i<len;i++) {
            if(s0[i] != s1[i]) {
                return false;
            }
        }
        return true;
    }

    void find(TString *what) {
        what_len = what->_len;
        size_t search_len = _len - what_len;
        for(size_t i = _next_search_pos;i<=search_len;i++) {
            if(_cmp(&_ptr[i], &what->_ptr[0], what->_len)) {
        	_found_pos = i;
		_next_search_pos = i;
		std::cerr << _found_pos << std::endl;
                return;
            }
        }
	std::cerr << "Not found"<< std::endl;
        _found_pos = -1;
        return;
    }
    
    bool replace(TString *replacer) {
	if(_found_pos == -1) {
	    return false;
	}
	
        size_t newlen = _len - what_len + replacer->_len;
        char *newptr = new char[newlen];
        for(size_t i = 0;i<(size_t ) _found_pos;i++) {
            newptr[i] = _ptr[i];
        }

        for(size_t i=0;i<replacer->_len;i++) {
            newptr[_found_pos+i] = replacer->_ptr[i];
        }
        size_t old_tail_start = _found_pos + what_len;
        size_t new_tail_start = _found_pos + replacer->_len;
        size_t tail_len = _len - old_tail_start;

        for(size_t i = 0;i<tail_len;i++) {
            newptr[new_tail_start+i] = _ptr[old_tail_start+i];
        }
        delete _ptr;
        _ptr = newptr;
        _len = newlen;
        _next_search_pos = _found_pos+replacer->_len;
	return true;
    }

    std::string to_string() const {
        std::string result(_ptr, _len);
        return result;
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

    do {
	source_line->find(what_to_replace);
    } while(source_line->replace(replace_with));

    std::ofstream outfile("output.txt");
    outfile << source_line->to_string();

    return 0;
}
