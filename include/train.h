#ifndef TRAIN_H
#define TRAIN_H

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

    virtual ~train();

    [[nodiscard]] const std::string &get_train_name() const;

    void set_train_name(const std::string &) const;

    void display_information_about_train() const;

    [[nodiscard]] virtual size_t calculate_train_ticket_price(const std::string &, const std::string &, float) const;

    [[nodiscard]] impl *get_impl() const { return impl_.get(); }
};

#endif /* TRAIN_H */
