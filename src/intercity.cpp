#include "intercity.h"
#include "impl.cpp"

#include <iostream>
#include <string>

using namespace std;

inter_city::inter_city(const string &file_path) : train{file_path} {
}

size_t inter_city::calculate_train_ticket_price(const string &src_railway_station, const string &dst_railway_station,
                                                float discount) const {
    // 0   - 19  km: 400Ft
    // 20  - 99  km: 1000Ft
    // 100 - 199 km: 1800Ft
    // above 200 km: 5000Ft

    if (src_railway_station == dst_railway_station) return 0u;

    const size_t first_railway_station_index = get_railway_station_index(src_railway_station);

    const size_t last_railway_station_index = get_railway_station_index(dst_railway_station);


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

    cout << "Total travel distance: " << distance << '\n';

    const auto discount_factor = discount / 100.f;

    if (distance <= 19.f) return 400u;

    if (distance <= 99.f) return static_cast<size_t>(1000.f - (1000.f * discount_factor));

    if (distance <= 199.f) return static_cast<size_t>(1800.f - (1800.f * discount_factor));

    if (distance >= 200.f) return static_cast<size_t>(5000.f - (5000.f * discount_factor));

    return 0u;
}
