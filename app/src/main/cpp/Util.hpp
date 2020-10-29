#pragma once

#include <string>
#include <cstdio>

std::string ReadFile(const std::string& filepath)
{
    FILE* fs = fopen(filepath.c_str(), "rb");

    fseek(fs, 0, SEEK_END);
    const int size = ftell(fs);
    const int allocSize = size + 1;
    char* buff = (char*)alloca(allocSize);
    rewind(fs);

    if (buff == nullptr)
    {
        fclose(fs);
        return "";
    }

    fread(buff, sizeof(char), size, fs);
    fclose(fs);
    buff[size] = 0;

    return buff;
}
void WriteFile(const std::string& filepath, const char* const text)
{
    FILE* fs = fopen(filepath.c_str(), "w+");

    fputs(text, fs);
    fflush(fs);

    fclose(fs);
}