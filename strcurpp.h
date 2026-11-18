/**
 * @file strcur.cpp
 * @brief 文字列操作で便利なものを集めたコード
 * @author curbine
 * @date 2026/4/3
 * @note 個人が趣味で製作したものなので、品質は保証しません。このコードを使用したことによるトラブルの責任は負いかねます。
 * @note strcur.hのstd::string版です。
 */

/**
 * stdcurにあった以下の機能は関数化するまでもないので自分で書いてください。
 * strcopy系->string::copy()、または=でOK。
 * strmods系->string::erase(0, n)でOK。
 * strcats系->string::append(p2)、または+=p2でOK。
 * strlens系->string::size()でOK。
 * strnums系->std::to_string(val)でOK。
 */

#pragma once

#include <string>
#include <tchar.h>

/* std::string の TCHAR 版 */
using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;

extern bool strandspp(const tstring& p1, const tstring& p2);
extern bool strnexpp(tstring& p1, char c);
extern int strsanpp(const tstring& p1, int default_val);
extern double strsanDpp(const tstring& p1, int under, double default_val);

/* strbox 未実装 */

/* 一応用意はするけど非推奨関数。このくらい自分で書いてね */
#define strcopypp(p1, p2) ((p2) = (p1))
#define strmodspp(p1, a)  ((p1).erase(0, (a)))
#define strcatspp(p1, p2) ((p1) += (p2))
#define strlenspp(s)      ((s).size())
#define strnumspp(val)    (std::to_string(val))
