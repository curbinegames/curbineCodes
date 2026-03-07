#pragma once

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
		datacur_cursor_vector<DataBase>::push_back(val);
		if (!this->isfull()) {
			this->time.push_back(a_time);
		}
	}

	void pop_back(void) {
		datacur_cursor_vector<DataBase>::pop_back();
		this->time.pop_back();
	}

	/* 今Noが差している基準時間を取得する */
	int nowDataTime(void) const {
		return this->time[betweens(0, this->No, this->data.size() - 1)];
	}

	/* 時間を見てNoを進める */
	void stepNoTime(int Ntime) {
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
