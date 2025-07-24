#ifndef TRAINSTATION_H
#define TRAINSTATION_H

#include "train.h"
#include "intercity.h"
#include "passenger_train.h"

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>
#include <set>

static_assert(train_type<train>);
static_assert(train_type<inter_city>);
static_assert(train_type<passenger_train>);


class train_station {
    struct impl;
    std::unique_ptr<impl> pimpl_;

public:
    train_station();

    explicit train_station(const size_t);

    train_station(const train_station &);

    train_station(train_station &&) noexcept;

    ~train_station();

    train_station &operator=(const train_station &);

    train_station &operator=(train_station &&) noexcept;

    [[nodiscard]] const std::string &get_trainstation_name() const;

    [[nodiscard]] size_t get_number_of_railways() const;

    [[nodiscard]] const std::vector<std::shared_ptr<train>> &get_railways() const;

    void set_trainstation_name(const std::string &) const;

    void arrives(const std::shared_ptr<train> &, std::ostream &os) const;

    std::shared_ptr<train> departs(const size_t, std::ostream &os) const;

    void list_out_railway_tracks() const;

    [[nodiscard]] std::set<size_t> buy_train_ticket(const std::string &, float) const;
};

#endif /* TRAINSTATION_H */
