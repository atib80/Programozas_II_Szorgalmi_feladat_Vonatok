#ifndef TRAIN_H
#define TRAIN_H
// #pragma once


#include <string>
#include <utility>
#include <stdexcept>

// enum class type_of_train { regular_train, passanger_train, intercity };

class train {

public:
	// default constructor
	train() : number_of_railway_stations_{}, railway_station_names_{}, railway_station_distances_{} { }

	// parameterized constructor
	explicit train(const std::wstring&);
	
	// copy constructor
	train(const train& rhs);
	
	// move constructor
	train(train&& rhs) noexcept;

	// virtual destructor
	virtual ~train();

	// overloadeded (user-defined) copy assigment operator
	train& operator=(const train& rhs);
	// overloadeded (user-defined) move assigment operator
	train& operator=(train&& rhs) noexcept;

	size_t get_number_of_railway_stations() const;
	void set_number_of_railway_stations(const size_t);

	const std::wstring& get_train_name() const;
	void set_train_name(const std::wstring&);
	
	size_t get_railway_station_index(const std::wstring&) const;

	std::pair<std::wstring, float> operator[](const size_t) const;

	void display_information_about_train() const;
	virtual size_t calculate_train_ticket_price(const std::wstring&, const std::wstring&, const float) const;

protected:

	const std::wstring* get_names_of_railway_stations() const;
	const std::wstring& get_name_of_railway_station(const size_t) const;
	const float* get_railway_station_distances() const;
	float get_distance_of_railway_station(const size_t) const;

	size_t number_of_railway_stations_{};
	std::wstring train_name_;
	std::wstring* railway_station_names_{};
	float* railway_station_distances_{};

};

#endif /* TRAIN_H */

