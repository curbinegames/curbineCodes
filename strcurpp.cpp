/**
 * @file strcur.cpp
 * @brief 文字列操作で便利なものを集めたコード
 * @author curbine
 * @date 2026/9/9
 * @note 個人が趣味で製作したものなので、品質は保証しません。このコードを使用したことによるトラブルの責任は負いかねます。
 * @note strcur.cppのstd::string版です。
 * @sa strcur.h
 */

/**
 * strcurにある以下の機能は関数化するまでもないので自分で書いてください。
 * strcopy系->string::copy()、または=でOK。
 * strmods系->string::erase(0, n)でOK。
 * strcats系->string::append()、または+=でOK。
 * strlens系->string::size()でOK。
 * strnums系->std::to_string(val)でOK。
 */

#pragma once

#include <stdexcept>
#include <cmath>
#include <string>
#include <strcurpp.h>

/**
 * p1の先頭にp2があるかどうかを調べる
 * @param[in] p1 探す場所
 * @param[in] p2 探す文字列
 * @return bool あったらtrue、なかったらfalse
 */
bool strandspp(const std::string& p1, const std::string& p2) {
	if (p2.size() > p1.size()) { return false; }
	return (p1.compare(0, p2.size(), p2) == 0);
}

/**
 * 次の指定の文字があるところまで消す
 * @param[out] p1 対象となる文字列
 * @param[in] c 指定の文字
 * @return bool cがあったらtrue、なかったらfalse
 * @note '/'または':'を検索するstrcur.cppとは違い、cを指定する必要があります。
 */
bool strnexpp(std::string& p1, char c) {
	size_t pos = p1.find(c);
	if (pos == std::string::npos) { return false; }
	p1.erase(0, pos + 1);
	return true;
}

/**
 * 文字列を整数に変換する
 * @param[in] p1 変換する文字列
 * @param[in] default_val 変換失敗時のデフォルト値
 * @return int 変換結果
 */
int strsanpp(const std::string& p1, int default_val) {
	try {
		return std::stoi(p1);
	}
	catch (const std::invalid_argument&) {
		return default_val;
	}
	catch (const std::out_of_range&) {
		return default_val;
	}
}

/**
 * 文字列をdouble数値に変換する
 * @param[in] p1 変換する文字列
 * @param[in] under 小数点以下の桁数
 * @param[in] default_val 変換失敗時のデフォルト値
 * @return double 変換結果
 */
double strsanDpp(const std::string& p1, int under, double default_val) {
	if (under < 0) { under = 0; }
	if (under > 15) { under = 15; }
	try {
		double val = std::stod(p1);
		if (under == 0) {
			return std::round(val);
		}
		double scale = 1.0;
		for (int i = 0; i < under; i++) { scale *= 10.0; }
		return std::round(val * scale) / scale;
	}
	catch (const std::invalid_argument&) {
		return default_val;
	}
	catch (const std::out_of_range&) {
		return default_val;
	}
}

/* strbox 未実装 */
