
#include "h/language.h"
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <map>
using namespace clazzy;
using namespace std;

// mutex *_io_mutex
// bool _debug_enabled

const char language::TWO_SPACES[] = "  ";
const char language::FOUR_SPACES[] = "    ";
const char language::EIGHT_SPACES[] = "        ";

language::language(mutex *io, bool debug) {
        _io_mutex = io;
        _debug_enabled = debug;
}

void language::debug(const string &s) const {
        if (_debug_enabled) {
                _io_mutex->lock();
                cout << "[DEBUG:" << this->get_name() << "] " << s << endl;
                _io_mutex->unlock();
        }
}

void language::warn(const string &s) const {
        _io_mutex->lock();
        cout << "[WARN:" << this->get_name() << "] " << s << endl;
        _io_mutex->unlock();
}

void language::error(const string &s) const {
        _io_mutex->lock();
        cerr << "[ERROR:" << this->get_name() << "] " << s << endl;
        _io_mutex->unlock();
}

