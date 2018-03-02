//
// Created by zhzl on 2018/2/3.
//

#include <malloc.h>
#include "FileUtils.h"
#include "zip/zip.h"
#include "JNIHelper.h"

FileUtils* FileUtils::s_instance = nullptr;

FileUtils *FileUtils::getInstance() {
    if (s_instance == nullptr)
    {
        s_instance = new FileUtils();
    }
    return s_instance;
}

Data FileUtils::readDataFromAssets(std::string path) {
    unsigned char *buf = nullptr;
    unsigned int bufsize;
    std::string fileName = JNIHelper::getApkPath();
    struct zip_t *zip = zip_open(fileName.c_str(), 0, 'r');
    if (zip != nullptr)
    {
        zip_entry_open(zip, path.c_str());
        zip_entry_read(zip, (void**)&buf, &bufsize);
    }
    Data data;
    data.copy(buf, bufsize);
    free(buf);
    zip_close(zip);
    return data;
}
