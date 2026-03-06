
#include <string>
#include <vector>
#include <stdcur.h>

/**
 * @brief FILEからfgetsしてstd::stringに格納する関数
 */
bool fgetsForString(std::string &str, int n, FILE *stream, bool erase_line_break) {
    if (stream == nullptr) { return false; }
    if (n <= 0) { return false; }
    char *ret;
    std::vector<char> buf(n + 1);
    ret = fgets(buf.data(), buf.size(), stream);
    if (ret == NULL) { return false; }
    str = buf.data();
    if (erase_line_break) {
        if (!str.empty()) {
            if (str.back() == '\n') {
                str.pop_back();
            }
        }
    }
    return true;
}

void StringToCharArray(const std::string &src, char dest[], size_t size) {
    for (size_t i = 0; i < src.size() && i < size; i++) {
        dest[i] = src[i];
    }
}

std::vector<char> CopyStringToVector(const std::string &src) {
    return { src.begin(), src.end() };
}

std::string CopyVectorToString(const std::vector<char> &src) {
    return std::string(src.begin(), src.end());
}

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
    std::vector<char> buf;
    if (ReadFileForVector<char>(buf, Stream) == false) { return false; }
    Buffer = CopyVectorToString(buf);
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
        if (UINT32_MAX < Buffer.size()) { return false; } /* 書き込みサイズチェック */
        if (MAX_CONTAIN_SIZE < Buffer.size()) { return false; } /* 書き込みサイズチェック */

        data_len = (uint32_t)Buffer.size();
        if (fwrite(&data_len, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = fwrite(Buffer.data(), 1, data_len, Stream);
    }
    return (write_count == data_len);
}

#endif /* ファイルで std::string を扱う関連 */

/**
 * @brief ReadFileForVectorのstd::vector<bool>版
 * @param Buffer 保存先
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
template<>
bool ReadFileForVector<bool>(std::vector<bool> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */

    uint32_t data_count = 0;
    size_t read_count = 0;

    if (fread(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
    if (data_count == 0) { /* 読み込むデータなし */
        Buffer.clear();
        return true;
    }
    else {
        if (MAX_CONTAIN_SIZE / sizeof(bool) < data_count) { return false; } /* 読み込みサイズチェック */

        std::vector<bool> read_buf;
        read_buf.reserve(data_count);
        for (uint32_t i = 0; i < data_count; i++) {
            bool bool_buf;
            if (fread(&bool_buf, sizeof(bool), 1, Stream) != 1) { return false; }
            read_buf.push_back(bool_buf);
        }
        Buffer.swap(read_buf);
    }
    return true;
}

/**
 * @brief WriteFileForVectorのstd::vector<bool>版
 * @param Buffer 保存するデータ
 * @param Stream ファイルポインタ
 * @return bool 成功判定
 */
template<>
bool WriteFileForVector<bool>(const std::vector<bool> &Buffer, FILE *Stream) {
    if (Stream == nullptr) { return false; } /* ファイル有効チェック */

    uint32_t data_count = 0;
    size_t write_count = 0;

    if (Buffer.size() == 0) { /* "0" だけ書いて終わり */
        data_count = 0;
        if (fwrite(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        write_count = 0;
    }
    else {
        if (UINT32_MAX < Buffer.size()) { return false; } /* 書き込みサイズチェック */
        if (MAX_CONTAIN_SIZE / sizeof(bool) < Buffer.size()) { return false; } /* 書き込みサイズチェック */

        data_count = (uint32_t)Buffer.size();
        if (fwrite(&data_count, sizeof(uint32_t), 1, Stream) != 1) { return false; }
        for (bool v : Buffer) {
            if (fwrite(&v, sizeof(bool), 1, Stream) != 1) { return false; }
        }
    }
    return true;
}
