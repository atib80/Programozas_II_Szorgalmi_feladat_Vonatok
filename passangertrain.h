#ifndef _SZEMELYVONAT_H_
#define _SZEMELYVONAT_H_
// #pragma once

#include "train.h"

class passanger_train : public train
{
public:
	explicit passanger_train(const std::wstring&);
	passanger_train(const passanger_train&);
	passanger_train(passanger_train&&) noexcept;
	~passanger_train();

	passanger_train& operator=(const passanger_train&);
	passanger_train& operator=(passanger_train&&) noexcept;

	size_t calculate_train_ticket_price(const std::wstring&, const std::wstring&, const float) const override;

private:

};

#endif

