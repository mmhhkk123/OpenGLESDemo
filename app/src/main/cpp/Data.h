//
// Created by zhzl on 2018/2/5.
//

#ifndef MYAPP1_DATA_H
#define MYAPP1_DATA_H

class Data {
public:
    Data();
    Data(const Data& other);
    ~Data();

    Data&operator=(const Data& other);
    unsigned char* getBytes() const;
    unsigned int getSize() const;
    void copy(const unsigned char* bytes, const unsigned int size);
    void clear();
    bool isNull() const;

private:
    unsigned char* m_bytes;
    unsigned int m_size;
};


#endif //MYAPP1_DATA_H
