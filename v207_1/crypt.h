#pragma once

enum HashType
{
    HashSha1, HashMd5, HashSha256
};


std::string GetHashText(const void* data, const size_t data_size, HashType hashType);