#ifndef PASSENGER_TRAIN_H
#define PASSENGER_TRAIN_H

#include "train.h"

class passenger_train : public train
{
public:
	explicit passenger_train(const std::string&);
	passenger_train(const passenger_train&) = default;
	passenger_train(passenger_train&&) noexcept = default;
	~passenger_train() override = default;

	passenger_train& operator=(const passenger_train&) = default;
	passenger_train& operator=(passenger_train&&) noexcept = default;

	[[nodiscard]] size_t calculate_train_ticket_price(const std::string&, const std::string&, float) const override;
};

#endif /* PASSENGER_TRAIN_H */

