#include "intercity.h"
#include <iostream>

using namespace std;

inter_city::inter_city(const wstring& file_path) : train{file_path} {

	// wprintf(L"InterCity::InterCity(const string&)\n");

}

// copy constructor
inter_city::inter_city(const inter_city& rhs) : train{ rhs } {

	// wprintf(L"InterCity::InterCity(const InterCity&)\n");

}

// move constructor
inter_city::inter_city(inter_city&& rhs) noexcept : train{ forward<inter_city>(rhs) }
{
	// wprintf(L"InterCity::InterCity(InterCity&&)\n");

}

inter_city::~inter_city() { 

	// wprintf(L"InterCity::~InterCity\n");

}


inter_city& inter_city::operator=(const inter_city& rhs) {

	// wprintf(L"InterCity& InterCity::operator=(const InterCity&)\n");

	if (this == &rhs) return *this;

	if (this == &rhs) return *this;

	wstring* temp1 = new wstring[rhs.number_of_railway_stations_];
	float* temp2 = new float[rhs.number_of_railway_stations_];

	if (railway_station_names_) {

		delete[] railway_station_names_;
		railway_station_names_ = nullptr;

	}

	if (railway_station_distances_) {

		delete[] railway_station_distances_;
		railway_station_distances_ = nullptr;

	}

	number_of_railway_stations_ = rhs.number_of_railway_stations_;

	train_name_ = rhs.train_name_;

	railway_station_names_ = temp1;

	// copy(rhs.railway_station_names_, rhs.railway_station_names_ + number_of_railway_stations_, railway_station_names_);
	for (size_t i = 0; i < number_of_railway_stations_; i++) railway_station_names_[i] = rhs.railway_station_names_[i];

	railway_station_distances_ = temp2;

	// copy(rhs.railway_station_distances_, rhs.railway_station_distances_ + number_of_railway_stations_, railway_station_distances_);
	for (size_t i = 0; i < number_of_railway_stations_; i++) railway_station_distances_[i] = rhs.railway_station_distances_[i];

	return *this;

}

inter_city& inter_city::operator=(inter_city&& rhs) noexcept
{
	// wprintf(L"InterCity& InterCity::operator=(InterCity&&)\n");

	if (this == &rhs) return *this;

	number_of_railway_stations_ = rhs.number_of_railway_stations_;
	rhs.number_of_railway_stations_ = 0u;
	train_name_ = move(rhs.train_name_);
	railway_station_names_ = rhs.railway_station_names_;
	rhs.railway_station_names_ = nullptr;
	railway_station_distances_ = rhs.railway_station_distances_;
	rhs.railway_station_distances_ = nullptr;

	return *this;

}

size_t inter_city::calculate_train_ticket_price(const wstring& src_railway_station, const wstring& dst_railway_station, const float discount) const {

	// 0   - 19  km: 400Ft
	// 20  - 99  km: 1000Ft
	// 100 - 199 km: 1800Ft
	// above 200 km: 5000Ft

	if (src_railway_station == dst_railway_station) return 0u;

	const size_t first_railway_station_index = get_railway_station_index(src_railway_station);

	const size_t last_railway_station_index = get_railway_station_index(dst_railway_station);
	

	if ((first_railway_station_index == string::npos) || (last_railway_station_index == string::npos) || (first_railway_station_index > last_railway_station_index)) return 0u;

	float distance{0.0f};
	
	wcout << L'\n';

	for (size_t rsi = first_railway_station_index + 1; rsi <= last_railway_station_index; rsi++) {

		try {

			wcout << get_names_of_railway_stations()[rsi] << L" : " << get_distance_of_railway_station(rsi) << L'\n';
			distance += get_distance_of_railway_station(rsi);

		}
		catch (out_of_range&) {
			return 0u;
		}

	}

	wcout << L"Total distance: " << distance;

	const auto discount_factor = discount / 100.f;

	if (distance <= 19.f) return 400u;

	if (distance <= 99.f) return static_cast<size_t>(1000.f - (1000.f * discount_factor));

	if (distance <= 199.f) return static_cast<size_t>(1800.f - (1800.f * discount_factor));

	if (distance >= 200.f) return static_cast<size_t>(5000.f - (5000.f * discount_factor));

	return 0u;
	
}
