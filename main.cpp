#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <io.h>
#include <codecvt>
#include "train.h"
#include "passangertrain.h"
#include "intercity.h"
#include "trainstation.h"

using namespace std;

int main()
{

	system("cls");
	// system("chcp 65001"); // for UTF-8 encoding

	// Enable Unicode UTF-16 output to console
	_setmode(_fileno(stdout), _O_U16TEXT); // for UCS2 LE BOM output
	_setmode(_fileno(stdin), _O_U16TEXT);  // for UCS2 LE BOM input

	train tr1 {L"regular_train_data.lst"};
	wcout << L"Information on train 'tr1':\n\n";
	tr1.display_information_about_train();

	passanger_train pt{ L"passanger_train_data.lst" };
	wcout << L"\nInformation on passanger_train 'pt':\n\n";
	pt.display_information_about_train();

	// PassangerTrain pt2 { move(pt) };

	inter_city ict { L"intercity_train_data.lst" };
	wcout << L"\nInformation on inter_city 'ict':\n\n";
	ict.display_information_about_train();

	// InterCity ict2 { move(ict) };	
	
	train_station trainstation(5);
	trainstation.set_trainstation_name(L"Szeged");
	trainstation.arrives(tr1);
	trainstation.arrives(pt);
	trainstation.arrives(ict);	
	
	wcout << L"\nEnter destination railway station's name: ";
	wstring destination;
	wcin >> destination;
	
	float discount{};
	wcout << L"Enter discount rate (in percentage [%]): ";
	wcin >> discount;
	
	if (discount >= 90.f) return 1;
	
	wcout << L"\n*" << trainstation.get_trainstation_name() << L"* -> *" << destination << L"*\n\n";

	// trainstation.buy_train_ticket(L"Budapest", 10.f);
	const auto found_trains = trainstation.buy_train_ticket(destination, discount);

	wstring available_trains{};

	for (const auto i : found_trains) {
		available_trains += to_wstring(i);
		available_trains += L", ";
	}

	available_trains += L" x|X -> Exit program\n";

	wcout << L"Which of the available trains would you like to travel by to " << destination << L" railway station?\n" << available_trains;

	wcout << L"Your choice: ";

	wstring chosen_railway_line_index{}; wcin >> chosen_railway_line_index;

	size_t railway_line_index{};

	do
	{
		if (!chosen_railway_line_index.empty() && ((chosen_railway_line_index[0] == L'x') || (chosen_railway_line_index[0] == L'X'))) {
			wcout << L"Exiting program...\n";
			return 0;
		}

		railway_line_index = stoul(chosen_railway_line_index);

		if (found_trains.count(railway_line_index))
		{

			trainstation.departs(railway_line_index - 1);			

		}
		
	} while (!found_trains.count(railway_line_index) && (chosen_railway_line_index[0] != L'x') && (chosen_railway_line_index[0] != L'X'));

	
	wcout << L'\n' << endl;

    return 0;
}
