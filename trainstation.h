#ifndef TRAINSTATION_H
#define TRAINSTATION_H
// #pragma once

#include <string>
#include <vector>
#include <set>
#include "train.h"

class train_station {	

public:
	train_station();
	explicit train_station(const size_t);
	train_station(const train_station&);
	train_station(train_station&&) noexcept;
	~train_station();

	train_station& operator=(const train_station&);
	train_station& operator=(train_station&&) noexcept;
	
	const std::wstring& get_trainstation_name() const;
	size_t get_number_of_railways() const;
	const std::vector<train*>& get_railways() const;
	
	void set_trainstation_name(const std::wstring&);

	void arrives(train&);
	train& departs(const size_t);

	void list_out_railway_tracks() const;
	std::set<size_t> buy_train_ticket(const std::wstring&, const float) const;

private:
	size_t number_of_railway_lines_;
	std::vector<train*> railway_lines_;
	std::wstring trainstation_name_;

};

#endif /* TRAINSTATION_H */
