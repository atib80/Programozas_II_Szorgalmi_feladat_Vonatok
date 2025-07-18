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

    size_t get_number_of_railway_stations() const noexcept;

    void set_number_of_railway_stations(size_t number_of_railway_stations) noexcept;

    [[nodiscard]] size_t get_railway_station_index(const std::string &) const;

    std::pair<std::string, float> operator[](size_t) const;

    [[nodiscard]] const std::vector<std::string> &get_names_of_railway_stations() const;

    [[nodiscard]] const std::string &get_name_of_railway_station(size_t) const;

    [[nodiscard]] const std::vector<float> &get_railway_station_distances() const;

    [[nodiscard]] float get_distance_of_railway_station(size_t) const;

    size_t number_of_railway_stations_{};
    std::string train_name_;
    std::vector<std::string> railway_station_names_;
    std::vector<float> railway_station_distances_;
};

inline size_t train::impl::get_number_of_railway_stations() const noexcept { return number_of_railway_stations_; }

inline void train::impl::set_number_of_railway_stations(size_t number_of_railway_stations) noexcept {
    number_of_railway_stations_ = number_of_railway_stations;
}

inline size_t train::impl::get_railway_station_index(const string &allomas_nev) const {
    if (const auto found_iter = std::ranges::find(railway_station_names_, allomas_nev);
        found_iter != end(railway_station_names_)) {
        return static_cast<size_t>(found_iter - begin(railway_station_names_));
        }

    return string::npos;
}

inline pair<string, float> train::impl::operator[](size_t index) const {
    if (index < number_of_railway_stations_)
        return make_pair(railway_station_names_[index],
                         railway_station_distances_[index]);

    throw out_of_range(
        "Specified index value cannot be greater than the number of available railway stations ('number_of_railway_stations_') - 1!");
}

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
