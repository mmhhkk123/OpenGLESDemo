//
// Created by zhzl on 2018/2/5.
//

#include <malloc.h>
#include <string.h>
#include "Data.h"

Data::Data() :
m_bytes(nullptr),
m_size(0)
{
}

Data::Data(const Data &other) {
    copy(other.m_bytes, other.m_size);
}

Data::~Data() {
    clear();
}

Data& Data::operator=(const Data &other) {
    copy(other.m_bytes, other.m_size);
    return *this;
}

unsigned char *Data::getBytes() const {
    return m_bytes;
}

unsigned int Data::getSize() const {
    return m_size;
}

void Data::copy(const unsigned char *bytes, const unsigned int size) {
    clear();
    if (size > 0)
    {
        m_size = size;
        m_bytes = (unsigned char*)malloc(sizeof(unsigned char) * m_size);
        memcpy(m_bytes, bytes, m_size);
    }
}

void Data::clear() {
    free(m_bytes);
    m_bytes = nullptr;
    m_size = 0;
}

bool Data::isNull() const {
    return (m_bytes == nullptr || m_size == 0);
}
