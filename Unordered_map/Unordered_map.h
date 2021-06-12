#pragma once

#include <unordered_map>
#include <forward_list>
#include <vector>


#define DEFAULT_CAPACITY 8


template <typename _Kty, typename _Ty, typename _Hasher = std::hash<_Kty>>
class Unordered_map {
private:
	std::vector<std::forward_list<std::pair<const _Kty, _Ty>>> buckets;
	_Hasher hash;
	size_t unorderedMapSize;

	bool _contains(std::forward_list<std::pair<const _Kty, _Ty>> obj, _Kty _Value) const {
		for (auto& item : obj) {
			if (item.first == _Value) return true;
		}
		return false;
	}

	class del {
	public:
		del(_Kty k) : key(k) {};
		_Kty key;
		bool operator()(const std::pair<const _Kty, _Ty> pr) {
			return pr.first == key;
		}
	};

	_Ty* _find(_Kty _Keyval) const {
		size_t currentIndex = hash(_Keyval) % buckets.capacity();
		for (auto item : buckets[currentIndex]) {
			if (item.first == _Keyval) return &item.second;
		}
	}

public:
	Unordered_map(size_t map = DEFAULT_CAPACITY) : buckets(), unorderedMapSize(0) {
		buckets.resize(map);
	}

	void insert(std::pair<const _Kty, _Ty> _Val) {
		if (unorderedMapSize == buckets.capacity()) rehash(buckets.capacity() * DEFAULT_CAPACITY);
		size_t ñurrentIndex = hash(_Val.first) % buckets.capacity();
		if (_contains(this->buckets[ñurrentIndex], _Val.first)) return;
		unorderedMapSize++;
		this->buckets[ñurrentIndex].push_front(_Val);
	}

	void rehash(size_t _Buckets) {
		std::vector<std::forward_list<std::pair<const _Kty, _Ty>>> temp;
		temp.resize(_Buckets);
		for (size_t i = 0; i < this->buckets.size(); i++) {
			for (auto& item : this->buckets[i]) {
				temp[i].push_front(item);
			}
		}
	}

	bool contains(const _Kty& _Keyval) const {
		size_t currentIndex = hash(_Keyval) % buckets.capacity();
		return _contains(this->buckets[currentIndex], _Keyval);
	}

	void erase(const _Kty& _Keyval) {
		size_t currentIndex = hash(_Keyval) % buckets.capacity();
		del d(_Keyval);
		if (contains(_Keyval)) {
			this->buckets[currentIndex].remove_if(d);
			unorderedMapSize--;
		}
	}

	_Ty& operator[](const _Kty _Keyval) {
		size_t currentIndex = hash(_Keyval) % buckets.capacity();
		for (auto it = buckets[currentIndex].begin(); it != buckets[currentIndex].end(); it++) {
			if ((*it).first == _Keyval) {
				return (*it).second;
			}
		}
		insert(std::pair<const _Kty, _Ty>(_Keyval, _Ty()));
		for (auto it = buckets[currentIndex].begin(); it != buckets[currentIndex].end(); it++) {
			if ((*it).first == _Keyval) {
				return (*it).second;
			}
		}
	}

	_Ty operator[](const _Kty _Keyval) const {
		size_t currentIndex = hash(_Keyval) % buckets.capacity();
		for (auto it = buckets[currentIndex].begin(); it != buckets[currentIndex].end(); it++) {
			if ((*it).first == _Keyval) {
				return (*it).second;
			}
		}
	}

	void clear() {
		unorderedMapSize = 0;
		buckets.resize(0);
		buckets.resize(DEFAULT_CAPACITY);
	}
};