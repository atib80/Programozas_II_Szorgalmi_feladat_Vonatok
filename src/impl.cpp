#include "train.h"
#include <format>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

struct train::impl {
    impl() = default;

    impl(const impl &rhs) = default;

    impl(impl &&rhs) noexcept = default;

    impl &operator=(const impl &rhs) = default;

    impl &operator=(impl &&rhs) noexcept = default;

    ~impl() = default;

    [[nodiscard]] const std::vector<std::string> &get_names_of_railway_stations() const;

    [[nodiscard]] const std::string &get_name_of_railway_station(size_t) const;

    [[nodiscard]] const std::vector<float> &get_railway_station_distances() const;

    [[nodiscard]] float get_distance_of_railway_station(size_t) const;

    size_t number_of_railway_stations_{};
    std::string train_name_;
    std::vector<std::string> railway_station_names_;
    std::vector<float> railway_station_distances_;
};

inline const std::vector<std::string> &train::impl::get_names_of_railway_stations() const {
    return railway_station_names_;
}

inline const string &train::impl::get_name_of_railway_station(size_t index) const {
    if (index < number_of_railway_stations_) return railway_station_names_[index];

    throw std::out_of_range(std::format(
        "Specified index value '{}' cannot be greater than the number of available railway stations '{} - 1'!", index,
        number_of_railway_stations_));
}

inline const std::vector<float> &train::impl::get_railway_station_distances() const {
    return railway_station_distances_;
}

inline float train::impl::get_distance_of_railway_station(size_t index) const {
    if (index < number_of_railway_stations_) return railway_station_distances_[index];

    throw std::out_of_range(std::format(
        "Specified index value '{}' cannot be greater than the number of available railway stations '{} - 1'!", index,
        number_of_railway_stations_));
}
