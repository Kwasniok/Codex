//
//  io_pair.h
//  Codex
//
//  Created by Jens Kwasniok on 24.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef Codex_io_pair_h
#define Codex_io_pair_h

#include <iostream>
#include <utility>

template<class K, class V>
std::ostream& operator<<(std::ostream& os, std::pair<K, V>& p);

template<class K, class V>
std::istream& operator>>(std::istream& is, std::pair<K, V>& p);

// V =  std::string
template<class K>
std::ostream& operator<<(std::ostream& os, std::pair<K, std::string>& p)
{
	os << p.first << ", \"" << p.second << '\"';
	return os;
}

template<class K>
std::istream& operator>>(std::istream& is, std::pair<K, std::string>& p)
{
	std::pair<K, std::string> tmp;
	char c;

	if (!is.good()) return is;
	is >> tmp.first;

	is >> c;
	if (c != '\"')
	{
		is.setf(std::ios_base::badbit);
		return is;
	}
	while (c = is.get(), c != '\"') {
		if (!is.good()) return is;
		tmp.second += c;
	}
	if (!is.good()) return is;

	p = std::move(tmp);
	return is;
}

// K = std::string
template<class V>
std::ostream& operator<<(std::ostream& os, std::pair<std::string, V>& p)
{
	os << p.first << ", " << p.second;
	return os;
}

template<class V>
std::istream& operator>>(std::istream& is, std::pair<std::string, V>& p)
{
	std::pair<std::string, V> tmp;
	char c;

	if (!is.good()) return is;
	is >> tmp.first;

	if (tmp.first[tmp.first.size() - 1] == ',') is.putback(',');

	if (!is.good()) return is;
	if (c != ',')
	{
		is.setf(std::ios_base::badbit);
		return is;
	}

	is >> tmp.second;
	if (!is.good()) return is;

	p = std::move(tmp);
	return is;
}

// general
template<class K, class V>
std::ostream& operator<<(std::ostream& os, std::pair<K, V>& p)
{
	os << p.first << ", " << p.second;
	return os;
}

template<class K, class V>
std::istream& operator>>(std::istream& is, std::pair<K, V>& p)
{
	std::pair<K, V> tmp;
	char c;

	if (!is.good()) return is;
	is >> tmp.first;

	if (!is.good()) return is;
	if (c != ',')
	{
		is.setf(std::ios_base::badbit);
		return is;
	}

	is >> tmp.second;
	if (!is.good()) return is;

	p = std::move(tmp);
	return is;
}

#endif
