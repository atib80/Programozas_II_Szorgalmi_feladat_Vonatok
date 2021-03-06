#include "train.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <string>
#include <algorithm>
#include "string_helper_functions.h"


using namespace std;


train::train(const wstring& file_path) {

	// wprintf(L"Train::Train(const wstring&)\n");

	// You need to open the file in binary mode
	wifstream input_file(file_path, ios::binary); 

	// Imbue the file stream with a codecvt facet that uses UTF-16 as the external multibyte encoding

	input_file.imbue(locale(input_file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

	if (!input_file) return;
	
	wstring line{};

	getline(input_file, train_name_);
	
	// train_name_ = trim(line);

	input_file >> number_of_railway_stations_;

	railway_station_names_ = new wstring[number_of_railway_stations_];
	railway_station_distances_ = new float[number_of_railway_stations_];

	for (size_t i = 0u; i < number_of_railway_stations_; i++) {
		
		input_file >> line;
		railway_station_names_[i] = trim(line);		
		input_file >> railway_station_distances_[i];
	}

}

// copy constructor
train::train(const train& rhs) : number_of_railway_stations_{ rhs.number_of_railway_stations_ }, train_name_{ rhs.train_name_ } {

	// wprintf(L"Train::Train(const Train&)\n");

	railway_station_names_ = new wstring[number_of_railway_stations_];
	
	for (size_t i = 0; i < number_of_railway_stations_; i++) railway_station_names_[i] = rhs.railway_station_names_[i];

	railway_station_distances_ = new float[number_of_railway_stations_];

	for (size_t i = 0; i < number_of_railway_stations_; i++) railway_station_distances_[i] = rhs.railway_station_distances_[i];

}

// move constructor
train::train(train&& rhs) noexcept : number_of_railway_stations_ { rhs.number_of_railway_stations_}, train_name_ {move(rhs.train_name_)},
							railway_station_names_{rhs.railway_station_names_}, railway_station_distances_{rhs.railway_station_distances_}
{
	// wprintf(L"Train::Train(Train&&)\n");

	rhs.number_of_railway_stations_ = 0;
	rhs.railway_station_names_ = nullptr;
	rhs.railway_station_distances_ = nullptr;

}

train::~train() {

	// wprintf(L"Train::~Train()\n");

	if (railway_station_names_) {
		delete[] railway_station_names_;
		railway_station_names_ = nullptr;
	}

	if (railway_station_distances_) {
		delete[] railway_station_distances_;
		railway_station_distances_ = nullptr;
	}

}

train& train::operator=(const train& rhs) {

	// wprintf(L"Train& Train::operator=(const Train&)\n");

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

train& train::operator=(train&& rhs) noexcept
{
	// wprintf(L"Train& Train::operator=(Train&&)\n");

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

size_t train::get_number_of_railway_stations() const { return number_of_railway_stations_; }
void train::set_number_of_railway_stations(const size_t number_of_railway_stations) { number_of_railway_stations_ = number_of_railway_stations; }

const wstring& train::get_train_name() const { return train_name_; }
void train::set_train_name(const wstring& train_name) { train_name_ = train_name; }

const wstring* train::get_names_of_railway_stations() const { return railway_station_names_; }

const wstring& train::get_name_of_railway_station(const size_t index) const {

	if (index < number_of_railway_stations_) return railway_station_names_[index];

	throw out_of_range("Specified index value cannot be greater than the number of available railway stations ('number_of_railway_stations_') - 1!");

}

size_t train::get_railway_station_index(const wstring& allomas_nev) const {

	for (size_t i = 0u; i < number_of_railway_stations_; i++) {

		if (allomas_nev == railway_station_names_[i]) return i;
	}

	return wstring::npos;

}

const float* train::get_railway_station_distances() const { return railway_station_distances_; }

float train::get_distance_of_railway_station(const size_t index) const {

	if (index < number_of_railway_stations_) return railway_station_distances_[index];

	throw out_of_range("Specified index value cannot be greater than the number of available railway stations ('number_of_railway_stations_') - 1!");

}

pair<wstring, float> train::operator[](const size_t index) const {

	if (index < number_of_railway_stations_) return make_pair(railway_station_names_[index], railway_station_distances_[index]);

	throw out_of_range("Specified index value cannot be greater than the number of available railway stations ('number_of_railway_stations_') - 1!");

}

void train::display_information_about_train() const {

	for (size_t i = 0; i < number_of_railway_stations_; i++) wcout << railway_station_names_[i] << L' ' << railway_station_distances_[i] << L'\n';
	wcout << L'\n';

}

size_t train::calculate_train_ticket_price(const wstring&, const wstring&, const float) const {
	
	return static_cast<size_t>(0);
}
