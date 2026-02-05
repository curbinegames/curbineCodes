
#include <vector>
#include <sancur.h>
#include <datacur.h>

#if 1 /* datacur_cursor_vector */

template<typename DataBase>
datacur_cursor_vector<DataBase>::datacur_cursor_vector(void) {}

template<typename DataBase>
datacur_cursor_vector<DataBase>::datacur_cursor_vector(size_t sz) : limit_size(sz) {}

template<typename DataBase>
const DataBase& datacur_cursor_vector<DataBase>::operator[](int n) const {
	return this->data[betweens(0, n, this->data.size())];
}

#if 1 /* std::vectorèÄãíä÷òA */

template<typename DataBase>
const DataBase& datacur_cursor_vector<DataBase>::at(size_t n) const {
	return this->data[betweens(0, n, this->data.size())];
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::clear(void) {
	this->data.clear();
	this->No = 0;
}

template<typename DataBase>
bool datacur_cursor_vector<DataBase>::empty(void) const {
	return (this->data.empty());
}

template<typename DataBase>
size_t datacur_cursor_vector<DataBase>::size(void) const {
	return this->data.size();
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::push_back(DataBase val) {
	if (!this->isfull()) {
		this->data.push_back(val);
	}
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::pop_back(void) {
	this->data.pop_back();
}

#endif /* std::vectorèÄãíä÷òA */

template<typename DataBase>
const DataBase& datacur_cursor_vector<DataBase>::nowData(void) const {
	return this->data[this->No];
}

template<typename DataBase>
const DataBase& datacur_cursor_vector<DataBase>::lastData(void) const {
	return this->data[this->data.size() - 1];
}

template<typename DataBase>
bool datacur_cursor_vector<DataBase>::isfull(void) const {
	return (this->limit_size <= this->data.size());
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::stepNo(void) {
	if (this->No < this->limit_size) {
		this->No++;
	}
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::backNo(void) {
	if (0 < this->No) {
		this->No--;
	}
}

template<typename DataBase>
void datacur_cursor_vector<DataBase>::resetNo(void) {
	this->No = 0;
}

template<typename DataBase>
size_t datacur_cursor_vector<DataBase>::nowNo(void) const {
	return this->No;
}

#endif /* datacur_cursor_vector */
