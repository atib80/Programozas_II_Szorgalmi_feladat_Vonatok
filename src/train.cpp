#include "train.h"
#include "impl.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "string_helper_functions.h"

using namespace std;

train::train() : impl_{std::make_unique<impl>()} {
}

train::train(const string &file_path) : impl_{std::make_unique<impl>()} {
    ifstream input_file(file_path.c_str());

    if (!input_file) return;

    string line{};

    getline(input_file, line);

    impl_->train_name_ = trim(line);

    input_file >> impl_->number_of_railway_stations_;

    impl_->railway_station_names_.resize(impl_->number_of_railway_stations_);
    impl_->railway_station_distances_.resize(impl_->number_of_railway_stations_);

    for (size_t i = 0u; i < impl_->number_of_railway_stations_; ++i) {
        input_file >> line;
        impl_->railway_station_names_[i] = trim(line);
        input_file >> impl_->railway_station_distances_[i];
    }
}

train::train(const train &rhs) : impl_{std::make_unique<impl>(*rhs.impl_)} {
}

train &train::operator=(const train &rhs) {
    if (this == &rhs) return *this;
    impl_ = std::make_unique<impl>(*rhs.impl_);
    return *this;
}

train::~train() = default;

const string &train::get_train_name() const { return impl_->train_name_; }
void train::set_train_name(const string &train_name) const { impl_->train_name_ = train_name; }

void train::display_information_about_train() const {
    for (size_t i{}; i < impl_->number_of_railway_stations_; i++) {
        cout << impl_->railway_station_names_[i] << ' ' << impl_->railway_station_distances_[i] << " km\n";
    }
    cout << '\n';
}

size_t train::calculate_train_ticket_price(const string & src_railway_station, const string & dst_railway_station, float) const {

    if (src_railway_station == dst_railway_station) return 0u;

    const size_t first_railway_station_index = get_impl()->get_railway_station_index(src_railway_station);

    const size_t last_railway_station_index = get_impl()->get_railway_station_index(dst_railway_station);

    if (first_railway_station_index == string::npos || last_railway_station_index == string::npos ||
        first_railway_station_index > last_railway_station_index)
        return 0u;

    float distance{0.0f};

    cout << '\n';

    for (size_t rsi = first_railway_station_index + 1; rsi <= last_railway_station_index; rsi++) {
        try {
            distance += get_impl()->get_distance_of_railway_station(rsi);
        } catch (std::out_of_range &) {
            return 0u;
        }
    }

    cout << "Total distance: " << distance << '\n';

    return 0u;
}
