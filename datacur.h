#pragma once

#include <vector>

template<typename DataBase>
class datacur_cursor_vector {
	std::vector<DataBase>data; /* データベース */
	const size_t limit_size = 2000; /* データ数の上限 */
	size_t No = 0; /* 今見ているデータ番号 */

public:
	datacur_cursor_vector(void);
	datacur_cursor_vector(size_t sz);
	const DataBase& operator[](int n) const;

#if 1 /* std::vector準拠関連 */

	const DataBase& at(size_t n) const;
	void clear(void);
	bool empty(void) const;
	size_t size(void) const;
	void push_back(DataBase val);
	void pop_back(void);

#endif /* std::vector準拠関連 */

	const DataBase& nowData(void) const;
	const DataBase& lastData(void) const;
	bool isfull(void) const;
	void stepNo(void);
	void backNo(void);
	void resetNo(void);
	size_t nowNo(void) const;
};
