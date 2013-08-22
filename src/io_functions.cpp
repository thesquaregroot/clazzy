
#include "h/io_functions.h"
#include <sys/stat.h>
using namespace std;

bool clazzy::chk_mkdir(const string &dir_name)
{
        struct stat sb;
        if (stat(dir_name.c_str(), &sb) != 0 && !S_ISDIR(sb.st_mode)) {
                return (mkdir(dir_name.c_str(), S_IRWXU|S_IRWXG) == 0);
        } else {
                return true;
        }
}

