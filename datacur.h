#pragma once

#include <algorithm>
#include <vector>

#include <sancur.h>
#include <stdcur.h>

template<typename DataBase>
class datacur_cursor_vector {
protected:
	std::vector<DataBase>data; /* データベース */
	size_t limit_size = 2000; /* データ数の上限 */
	size_t No = 0; /* 今見ているデータ番号 */

public:
	datacur_cursor_vector(void) {}
	datacur_cursor_vector(size_t sz) : limit_size(sz) {}

	const DataBase& operator[](size_t n) const {
		return this->data[betweens(0, n, this->data.size() - 1)];
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

	void insert(size_t i, DataBase val) {
		if (!this->isfull()) {
			this->data.insert(this->data.begin() + i, val);
		}
	}

#endif /* std::vector準拠関連 */

	/* 今Noが差しているデータを取得する */
	const DataBase& nowData(void) const {
		return this->at(this->No);
	}

	/* 今のNoからn個分ずれた先のデータを取得する */
	const DataBase& offsetData(int n) const {
		return this->at(this->No + n);
	}

	/* 最後のデータを取得する */
	const DataBase& lastData(void) const {
		return this->at(this->data.size() - 1);
	}

	/* データ数が上限に達したかを取得する */
	bool isfull(void) const {
		return (this->limit_size <= this->data.size());
	}

	/* Noを一つ進める */
	void stepNo(void) {
		if (this->No + 1 < this->size()) {
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

	/* 今のNoが終端に達しているかを取得する */
	bool isEndNo(void) const {
		return ((this->No + 1) == this->data.size());
	}

	/* ファイルから情報を読み込む */
	bool fread(FILE *fp) {
		return ReadFileForVector<DataBase>(this->data, fp);
	}

	/* ファイルに情報を書き込む */
	bool fwrite(FILE *fp) const {
		return WriteFileForVector<DataBase>(this->data, fp);
	}
};

template<typename DataBase>
class datacur_timeline_vector : public datacur_cursor_vector<DataBase> {
private:
	std::vector<int>time; /* 基準時間 */

public:
	datacur_timeline_vector(void) {}
	datacur_timeline_vector(size_t sz) : datacur_cursor_vector<DataBase>(sz) {}

	void clear(void) {
		datacur_cursor_vector<DataBase>::clear();
		this->data.clear();
	}

	void push_back(int a_time, DataBase val) {
		if (!this->isfull()) {
			datacur_cursor_vector<DataBase>::push_back(val);
			this->time.push_back(a_time);
		}
	}

	void pop_back(void) {
		datacur_cursor_vector<DataBase>::pop_back();
		this->time.pop_back();
	}

	/* 時間順になるように挿入する */
	void insert(int a_time, DataBase val) {
		if (this->isfull()) { return; }

		/* そもそも空なら普通にpush_back */
		if (this->empty()) {
			this->push_back(a_time, val);
			return;
		}

		/* 末尾に追加されるようならpush_back */
		if (this->lastDataTime() <= a_time) {
			this->push_back(a_time, val);
			return;
		}

		/* 探索して挿入 */
		auto it = std::lower_bound(this->time.begin(), this->time.end(), a_time);
		size_t idx = std::distance(this->time.begin(), it);
		datacur_cursor_vector<DataBase>::insert(idx, val);
		this->time.insert(it, a_time);
	}

	/* 今Noが差している基準時間を取得する */
	int nowDataTime(void) const {
		return this->time[betweens(0, this->No, this->time.size() - 1)];
	}

	/* 今のNoからn個分ずれた先の基準時間を取得する */
	int offsetDataTime(int n) const {
		return this->time[betweens(0, this->No + n, this->time.size() - 1)];
	}

	/* 最後の基準時間を取得する */
	int lastDataTime(void) const {
		return this->time[this->time.size() - 1];
	}

	/* 時間を見てNoを進める */
	void stepNoTime(int Ntime) {
		if (this->empty()) { return; }
		while (!this->isEndNo() && this->time[this->nowNo() + 1] <= Ntime) { this->stepNo(); }
	}

	/* 時間を見てNoを取得する */
	size_t searchTime(int Ntime) const {
		size_t ret = 0;
		while ((ret + 1) < this->size() && this->time[ret + 1] <= Ntime) { ret++; }
		return ret;
	}

	/* 時間を見てNoを取得する。今のNo以降のデータしか見ない */
	size_t searchTimeFront(int Ntime) const {
		size_t ret = this->nowNo();
		while ((ret + 1) < this->size() && this->time[ret + 1] <= Ntime) { ret++; }
		return ret;
	}

	/* 時間を見てデータを取得する */
	const DataBase& searchData(int Ntime) const {
		size_t index = this->searchTime(Ntime);
		return this->data[betweens(0, index, this->data.size() - 1)];
	}

	/* 時間を見てデータを取得する。今のNo以降のデータしか見ない */
	const DataBase& searchDataFront(int Ntime) const {
		size_t index = this->searchTimeFront(Ntime);
		return this->data[betweens(0, index, this->data.size() - 1)];
	}

	/* ファイルから情報を読み込む */
	bool fread(FILE *fp) {
		bool ret = false;
		ret = ReadFileForVector<int>(this->time, fp);
		if (ret == false) { return false; }
		return ReadFileForVector<DataBase>(this->data, fp);
	}

	/* ファイルに情報を書き込む */
	bool fwrite(FILE *fp) const {
		bool ret = false;
		ret = WriteFileForVector<int>(this->time, fp);
		if (ret == false) { return false; }
		return WriteFileForVector<DataBase>(this->data, fp);
	}
};
