#include "trainstation.h"
#include "PassangerTrain.h"
#include "intercity.h"
#include <iostream>

using namespace std;

// default constructor
train_station::train_station() : number_of_railway_lines_{ 1 }, railway_lines_{ {nullptr} } {
	// wprintf(L"default ctor -> TrainStation::TrainStation()\n");
}

// parameterized constructor
train_station::train_station(const size_t vaganyok_szama) : number_of_railway_lines_{ vaganyok_szama }, railway_lines_(vaganyok_szama, nullptr) {
	
	// wprintf(L"parameterized ctor -> TrainStation::TrainStation(const size_t)\n");

}

// copy constructor
train_station::train_station(const train_station& rhs) : number_of_railway_lines_{ rhs.number_of_railway_lines_ }, railway_lines_(number_of_railway_lines_, nullptr), trainstation_name_{ rhs.trainstation_name_ } {
	
	// wprintf(L"copy ctor -> TrainStation::TrainStation(const TrainStation&)\n");
	
	// railway_lines_.resize(rhs.number_of_railway_lines_);	

}

// move constructor
train_station::train_station(train_station&& rhs) noexcept : number_of_railway_lines_{ rhs.number_of_railway_lines_ }, railway_lines_{ move(rhs.railway_lines_) }, trainstation_name_{ move(rhs.trainstation_name_) }
{	
	// wprintf(L"move ctor -> TrainStation::TrainStation(TrainStation&&)\n");

	rhs.number_of_railway_lines_ = 0;
}

train_station& train_station::operator=(const train_station& rhs) {

	// wprintf(L"copy assigment operator -> TrainStation& TrainStation::operator=(const TrainStation&)\n");

	if (this == &rhs) return *this;	

	railway_lines_.clear();
	railway_lines_.resize(rhs.number_of_railway_lines_);
	number_of_railway_lines_ = rhs.number_of_railway_lines_;
	trainstation_name_ = rhs.trainstation_name_;	

	return *this;

}

// move assignment operator
train_station& train_station::operator=(train_station&& rhs) noexcept {

	// wprintf(L"move assigment operator -> TrainStation& TrainStation::operator=(TrainStation&&)\n");

	if (this == &rhs) return *this;	

	number_of_railway_lines_ = rhs.number_of_railway_lines_;

	rhs.number_of_railway_lines_ = 0;

	railway_lines_ = move(rhs.railway_lines_);

	trainstation_name_ = move(rhs.trainstation_name_);

	return *this;

}

train_station::~train_station() {

	// wprintf(L"destructor TrainStation::~TrainStation()\n");
	railway_lines_.clear();
	number_of_railway_lines_ = 0;

}

const wstring& train_station::get_trainstation_name() const { return trainstation_name_; }
size_t train_station::get_number_of_railways() const { return number_of_railway_lines_; }
const vector<train*>& train_station::get_railways() const { return railway_lines_; }

void train_station::set_trainstation_name(const wstring& allomas_nev) { trainstation_name_ = allomas_nev; }

void train_station::arrives(train& vonat) {

	if (!railway_lines_.empty()) {

		for (size_t i = 0u; i < number_of_railway_lines_; i++) {	
			
			if (!railway_lines_[i]) {
				railway_lines_[i] = &vonat;
				wcout << L"Train " << railway_lines_[i]->get_train_name() << L" arrived on " << (i + 1) << L". railway track.\n";
				return;
			}
		}	
	}

	wcout << L"There are no unused railway lines available at the moment.\n";

}

train& train_station::departs(const size_t railway_line_index) {

	static train vonat{};	

	if (railway_line_index > (number_of_railway_lines_ - 1)) {

		static train ures_vagany{};

		return ures_vagany;

	}

	vonat = *(railway_lines_[railway_line_index]);

	if (!vonat.get_train_name().empty()) 
		if (railway_line_index == 0 || railway_line_index == 4)
			wcout << L"\nAz " << (railway_line_index + 1) << L". vágányról " << vonat.get_train_name() << L" vonat indul.\n";
		else
			wcout << L"\nA " << (railway_line_index + 1) << L". vágányról " << vonat.get_train_name() << L" vonat indul.\n";

	
	railway_lines_[railway_line_index] = nullptr;

	return vonat;

}

void train_station::list_out_railway_tracks() const
{

	for (size_t i = 0u; i < number_of_railway_lines_; i++)
	{	
		if (!railway_lines_[i])
		{
			wcout << (i + 1) << L". vágány: üres\n";
			continue;
		}

		if (railway_lines_[i]->get_train_name().empty())
			wcout << (i + 1) << L". vágány: üres\n";
		else
			wcout << (i + 1) << L". vágány: " << railway_lines_[i]->get_train_name() << L'\n';
	}
}

set<size_t> train_station::buy_train_ticket(const std::wstring& cel_allomas, const float kedvezmeny_szazalek) const
{
	set<size_t> vagany_poziciok{};
	size_t si, ci;
	
	bool found{false};
		
	for (auto i = 0u; i < number_of_railway_lines_; i++)
	{
		if (!railway_lines_[i]) continue;

		if (!(dynamic_cast<passanger_train*>(railway_lines_[i])) && !(dynamic_cast<inter_city*>(railway_lines_[i]))) continue;

		if (!railway_lines_[i]->get_train_name().empty()) {

			if (((si = railway_lines_[i]->get_railway_station_index(trainstation_name_)) != string::npos) && ((ci = railway_lines_[i]->get_railway_station_index(cel_allomas)) != string::npos)
				&& (si < ci)) {
					
				found = true;
				vagany_poziciok.insert(i + 1);
				wcout << (i + 1) << L". vágány: " << railway_lines_[i]->get_train_name() << L"\nJegyár: " << railway_lines_[i]->calculate_train_ticket_price(trainstation_name_, cel_allomas, kedvezmeny_szazalek) << L" Ft\n\n";
				
			}
		}
	}
	
	if (!found) wcout << L"\nJelenleg nem indul vonat " << cel_allomas << " felé.\n";

	return vagany_poziciok;
}
