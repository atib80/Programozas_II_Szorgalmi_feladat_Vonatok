#ifndef INTERCITY_H
#define INTERCITY_H

#include "train.h"

class inter_city : public train {

public:
	explicit inter_city(const std::string&);
	inter_city(const inter_city&) = default;
	inter_city(inter_city&&) noexcept = default;
	~inter_city() override = default;

	inter_city& operator=(const inter_city&) = default;
	inter_city& operator=(inter_city&&) noexcept = default;

	[[nodiscard]] size_t calculate_train_ticket_price(const std::string&, const std::string&, float) const override;

};

#endif /* INTERCITY_H */
