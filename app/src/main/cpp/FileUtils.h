//
// Created by zhzl on 2018/2/3.
//

#ifndef MYAPP1_FILEUTILS_H
#define MYAPP1_FILEUTILS_H

#include <string>
#include "Data.h"

class FileUtils {

public:
    static FileUtils* getInstance();
    Data readDataFromAssets(std::string path);
private:
    static FileUtils* s_instance;

};


#endif //MYAPP1_FILEUTILS_H
