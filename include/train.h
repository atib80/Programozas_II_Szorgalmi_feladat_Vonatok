#ifndef TRAIN_H
#define TRAIN_H

#include <concepts>
#include <memory>
#include <string>

class train {

    struct impl;
    std::unique_ptr<impl> impl_;

public:

    train();

    explicit train(const std::string &);

    train(const train &rhs);

    train(train &&rhs) noexcept = default;

    train &operator=(const train &rhs);

    train &operator=(train &&rhs) noexcept = default;

    ~train();

    const std::string &get_train_name() const;

    void set_train_name(const std::string &) const;

    void display_information_about_train() const;

    virtual size_t calculate_train_ticket_price(const std::string &, const std::string &, float) const;

    impl *get_impl() const { return impl_.get(); }

};

template <typename T>
concept train_type = requires (T& t)
{
    { t.get_train_name() } -> std::convertible_to<std::string>;
    { t.set_train_name(std::string{}) };
    { t.display_information_about_train() };
    { t.calculate_train_ticket_price(std::string{}, std::string{}, float{}) };
};

#endif /* TRAIN_H */
