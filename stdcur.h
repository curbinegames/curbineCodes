#pragma once

#include <stdint.h>
#include <type_traits>
#include <stack>
#include <string>
#include <vector>

#define MAX_CONTAIN_SIZE 1000000 /* 一度に読み書きするファイルの上限。バイト単位 */

template<typename T>
std::vector<T> CopyStackToVector(const std::stack<T> &src) {
    size_t data_count = src.size();
    std::stack<T> buf = src;
    std::vector<T> ret(data_count);
    for (size_t i = 0; i < data_count; i++) {
        ret[data_count - i - 1] = buf.top();
        buf.pop();
    }
    return ret;
}

template<typename T>
std::vector<T> MoveStackToVector(std::stack<T> &src) {
    size_t data_count = src.size();
    std::vector<T> ret(data_count);
    for (size_t i = 0; i < data_count; i++) {
        ret[data_count - i - 1] = std::move(src.top());
        src.pop();
    }
    return ret;
}

template<typename T>
std::stack<T> CopyVectorToStack(const std::vector<T> &src) {
    size_t data_count = src.size();
    std::stack<T> ret;
    for (size_t i = 0; i < data_count; i++) {
        ret.push(src[i]);
    }
    return ret;
}

/**
 * vectorをファイルに読み書きする関数群。
 * [vectorの要素数], [要素0], [要素1], [要素2]... という風に書かれる。
 * <typename T>はintとかdoubleとかstruct{int}とかを想定。ポインタを含んでいたりstd::vectorだったりすると失敗する。
 */
#if 1 /* ファイルで std::vector<any> を扱う関連 */

/**
 * @brief FILEからvectorを読み込む。
 * @tparam T vectorの型
 * @param Buffer 保存先
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
template<typename T>
bool ReadFileForVector(std::vector<T> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */
    if (!std::is_trivially_copyable_v<T>) { return false; } /* コピー可能チェック */

    uint32_t data_count = 0;
    size_t read_count = 0;

    if (fread(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
    if (data_count == 0) { /* 読み込むデータなし */
        Buffer.clear();
        return true;
    }
    else {
        if (MAX_CONTAIN_SIZE / sizeof(T) < data_count) { return false; } /* 読み込みサイズチェック */

        std::vector<T> read_buf(data_count);
        read_count = fread(read_buf.data(), sizeof(T), data_count, Stream);
        if (read_count != data_count) { return false; } /* 読み込み成功チェック */
        Buffer.swap(read_buf);
    }
    return true;
}

/**
 * @brief vectorをFILEに書き込む。
 * @tparam T vectorの型
 * @param Buffer 保存するデータ
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
template<typename T>
bool WriteFileForVector(const std::vector<T> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */
    if (!std::is_trivially_copyable_v<T>) { return false; } /* コピー可能チェック */

    uint32_t data_count = 0;
    size_t write_count = 0;

    if (Buffer.size() == 0) { /* "0" だけ書いて終わり */
        data_count = 0;
        if (fwrite(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = 0;
    }
    else {
        if (std::numeric_limits<uint32_t>::max() < Buffer.size()) { return false; } /* 書き込みサイズチェック */
        if (MAX_CONTAIN_SIZE / sizeof(T) < Buffer.size()) { return false; } /* 書き込みサイズチェック */

        data_count = (uint32_t)Buffer.size();
        if (fwrite(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = fwrite(Buffer.data(), sizeof(T), data_count, Stream);
    }
    return (write_count == data_count);
}

#endif /* ファイルで std::vector<any> を扱う関連 */

/**
 * stringをファイルに読み書きする関数群。
 * [stringの文字数], [文字0], [文字1], [文字2]... という風に書かれる。
 * sizeof(char)は常に1としてコーディング。
 */
#if 1 /* ファイルで std::string を扱う関連 */

/**
 * @brief FILEからstringを読み込む。
 * @param Buffer 保存先
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
bool ReadFileForString(std::string &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */

    uint32_t data_len = 0;
    size_t read_count = 0;

    if (fread(&data_len, sizeof(uint32_t), 1, Stream) != 1) { return false; }
    if (data_len == 0) { /* 読み込むデータなし */
        Buffer.clear();
        return true;
    }
    else {
        if (MAX_CONTAIN_SIZE < data_len) { return false; } /* 読み込みサイズチェック */

        std::string read_buf(data_len, '\0');
        read_count = fread(read_buf.data(), 1, data_len, Stream);
        if (read_count != data_len) { return false; } /* 読み込み成功チェック */
        Buffer = read_buf;
    }
    return true;
}

/**
 * @brief stringをFILEに書き込む。
 * @param Buffer 保存するデータ
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
bool WriteFileForString(const std::string &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */

    uint32_t data_len = 0;
    size_t write_count = 0;

    if (Buffer.size() == 0) { /* "0" だけ書いて終わり */
        data_len = 0;
        if (fwrite(&data_len, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = 0;
    }
    else {
        if (std::numeric_limits<uint32_t>::max() < Buffer.size()) { return false; } /* 書き込みサイズチェック */
        if (MAX_CONTAIN_SIZE < Buffer.size()) { return false; } /* 書き込みサイズチェック */

        data_len = (uint32_t)Buffer.size();
        if (fwrite(&data_len, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = fwrite(Buffer.data(), 1, data_len, Stream);
    }
    return (write_count == data_len);
}

#endif /* ファイルで std::string を扱う関連 */

template<typename T>
bool ReadFileForStack(std::stack<T> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */
    std::vector<T> buf;
    if (ReadFileForVector(buf, Stream) == false) { return false; }
    /* vector -> stack */
    return true;
}

template<typename T>
bool WriteFileForStack(const std::stack<T> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */
    std::vector<T> buf = CopyStackToVector(Buffer);
    return WriteFileForVector(buf, Stream);
}
