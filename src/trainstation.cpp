#include "trainstation.h"
#include "impl.cpp"

#include <format>
#include <iostream>
#include <set>

using namespace std;

struct train_station::impl {
    size_t number_of_railway_lines_{1};
    std::vector<std::shared_ptr<train>> railway_lines_{{nullptr}};
    std::string trainstation_name_;
};

train_station::train_station() : pimpl_{std::make_unique<impl>()} {
}

train_station::train_station(const size_t number_of_trackways) : pimpl_{std::make_unique<impl>()} {
    pimpl_->number_of_railway_lines_ = number_of_trackways;
    pimpl_->railway_lines_.resize(number_of_trackways, nullptr);
}

train_station::train_station(const train_station &rhs) : pimpl_{std::make_unique<impl>(*rhs.pimpl_)} {
}

train_station::train_station(train_station &&rhs) noexcept : pimpl_{std::move(rhs.pimpl_)} {
    rhs.pimpl_.reset();
}

train_station &train_station::operator=(const train_station &rhs) {
    if (this == &rhs) return *this;
    pimpl_ = std::make_unique<impl>(*rhs.pimpl_);
    return *this;
}


train_station &train_station::operator=(train_station &&rhs) noexcept {
    if (this == &rhs) return *this;
    pimpl_ = std::move(rhs.pimpl_);
    rhs.pimpl_.reset();
    return *this;
}

train_station::~train_station() {
    pimpl_->railway_lines_.clear();
    pimpl_->number_of_railway_lines_ = 0;
    pimpl_->trainstation_name_.clear();
}

const string &train_station::get_trainstation_name() const { return pimpl_->trainstation_name_; }
size_t train_station::get_number_of_railways() const { return pimpl_->number_of_railway_lines_; }

const std::vector<std::shared_ptr<train> > &train_station::get_railways() const {
    return pimpl_->railway_lines_;
}

void train_station::set_trainstation_name(const string &trainstation_name) const {
    pimpl_->trainstation_name_ = trainstation_name;
}

void train_station::arrives(const std::shared_ptr<train> &tr, std::ostream &os) const {
    if (!pimpl_->railway_lines_.empty()) {
        for (size_t i{0}; i < pimpl_->number_of_railway_lines_; ++i) {
            if (!pimpl_->railway_lines_[i]) {
                pimpl_->railway_lines_[i] = tr;
                os << "Train " << tr->get_train_name() << " arrived on " << (i + 1) <<
                        ". railway track.\n";

                return;
            }
        }
    }

    cout << "There's no available train departures scheduled at the moment.\n";
}

std::shared_ptr<train>
train_station::departs(const size_t railway_line_index, std::ostream &os) const {
    if (railway_line_index >= pimpl_->number_of_railway_lines_) {
        return {nullptr};
    }

    if (!pimpl_->railway_lines_[railway_line_index]) {
        return {nullptr};
    }

    auto tr = pimpl_->railway_lines_[railway_line_index];

    pimpl_->railway_lines_[railway_line_index] = nullptr;

    if (!tr->get_train_name().empty()) {
        os << std::format("\nTrain {} departs on railway track no. {}.\n", tr->get_train_name(),
                          railway_line_index + 1);
    }

    return tr;
}

void train_station::list_out_railway_tracks() const {
    for (size_t i{0}; i < pimpl_->number_of_railway_lines_; ++i) {
        if (!pimpl_->railway_lines_[i]) {
            cout << (i + 1) << ". railway track: empty\n";
        } else {
            auto &&tr = pimpl_->railway_lines_[i];
            if (!tr->get_train_name().empty()) {
                cout << (i + 1) << ". railway track: empty\n";
            } else {
                cout << (i + 1) << ". railway track: " << tr->get_train_name() << '\n';
            }
        }
    }
}

std::set<size_t> train_station::buy_train_ticket(const std::string &destination_trainstation,
                                                 float discount_in_percentage) const {
    std::set<size_t> trackway_numbers{};
    size_t si, ci;

    bool found{};

    for (size_t i{0}; i < pimpl_->number_of_railway_lines_; ++i) {
        if (!pimpl_->railway_lines_[i]) continue;

        auto &&tr = pimpl_->railway_lines_[i];

        if (!tr->get_train_name().empty()) {
            if ((si = tr->get_impl()->get_railway_station_index(pimpl_->trainstation_name_)) != string::npos
                && (ci = tr->get_impl()->get_railway_station_index(destination_trainstation)) != string::npos
                && si < ci) {
                found = true;
                trackway_numbers.emplace(i + 1);
                cout << (i + 1) << ". railway track: " << tr->get_train_name();
                const auto ticket_price = tr->calculate_train_ticket_price(
                            pimpl_->trainstation_name_, destination_trainstation, discount_in_percentage);
                cout << "Ticket price: " << ticket_price << " Ft\n\n";
            }
        }
    }

    if (!found) cout << "\nThere's no available train departures scheduled for " << destination_trainstation << ".\n";

    return trackway_numbers;
}
