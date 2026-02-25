#pragma once

#include <vector>

#include <sancur.h>

template<typename DataBase>
class datacur_cursor_vector {
private:
	std::vector<DataBase>data; /* データベース */
	const size_t limit_size = 2000; /* データ数の上限 */
	size_t No = 0; /* 今見ているデータ番号 */

public:
	datacur_cursor_vector(void) {}

	datacur_cursor_vector(size_t sz) : limit_size(sz) {}

	const DataBase& operator[](int n) const {
		return this->data[betweens(0, n, this->data.size())];
	}

#if 1 /* std::vector準拠関連 */

	const DataBase& at(size_t n) const {
		return this->data[betweens(0, n, this->data.size() - 1)];
	}

	void clear(void) {
		this->data.clear();
		this->No = 0;
	}

	bool empty(void) const {
		return (this->data.empty());
	}

	size_t size(void) const {
		return this->data.size();
	}

	void push_back(DataBase val) {
		if (!this->isfull()) {
			this->data.push_back(val);
		}
	}

	void pop_back(void) {
		this->data.pop_back();
	}

#endif /* std::vector準拠関連 */

	/* 今Noが差しているデータを取得する */
	const DataBase& nowData(void) const {
		return this->data[betweens(0, this->No, this->data.size() - 1)];
	}

	/* 今のNoからn個分ずれた先のデータを取得する */
	const DataBase& offsetData(int n) const {
		return this->data[betweens(0, this->No + n, this->data.size() - 1)];
	}

	/* 最後のデータを取得する */
	const DataBase& lastData(void) const {
		return this->data[this->data.size() - 1];
	}

	/* データ数が上限に達したかを取得する */
	bool isfull(void) const {
		return (this->limit_size <= this->data.size());
	}

	/* Noを一つ進める */
	void stepNo(void) {
		if (this->No < this->limit_size) {
			this->No++;
		}
	}

	/* Noを一つ戻す */
	void backNo(void) {
		if (0 < this->No) {
			this->No--;
		}
	}

	/* Noを0にする */
	void resetNo(void) {
		this->No = 0;
	}

	/* 今のNoを取得する */
	size_t nowNo(void) const {
		return this->No;
	}
};
