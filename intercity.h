#ifndef INTERCITY_H
#define INTERCITY_H
//#pragma once

#include "train.h"

class inter_city : public train {

public:
	explicit inter_city(const std::wstring&);
	inter_city(const inter_city&);
	inter_city(inter_city&&) noexcept;
	~inter_city();

	inter_city& operator=(const inter_city&);
	inter_city& operator=(inter_city&&) noexcept;

	size_t calculate_train_ticket_price(const std::wstring&, const std::wstring&, const float) const override;

};

#endif /* INTERCITY_H */
