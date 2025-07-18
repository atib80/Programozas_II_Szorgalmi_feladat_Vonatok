#include "train.h"
#include "passenger_train.h"
#include "intercity.h"
#include "trainstation.h"
#include "string_helper_functions.h"

#include <conio.h>
#include <iostream>
#include <format>

using namespace std;

int main() {
    const auto tr1 = std::make_shared<train>("regular_train_data.lst");
    const auto pt = std::make_shared<passenger_train>("passanger_train_data.lst");
    const auto ict = std::make_shared<inter_city>("intercity_train_data.lst");

    while (true) {
        system("cls");
        cout << "Information on train 'tr1':\n\n";
        tr1->display_information_about_train();

        cout << "\nInformation on passanger_train 'pt':\n\n";
        pt->display_information_about_train();

        cout << "\nInformation on inter_city 'ict':\n\n";
        ict->display_information_about_train();

        train_station trainstation(5);
        trainstation.set_trainstation_name("Szeged");
        trainstation.arrives(tr1, cout);
        trainstation.arrives(pt, cout);
        trainstation.arrives(ict, cout);

        cout << "\nEnter destination railway station's name: ";
        string destination;
        getline(cin, destination);
        destination = trim(destination);

        float discount{};
        while (true) {
            cout << "Enter discount rate (in percentage [%]): ";
            for (string line; getline(cin, line);) {
                try {
                    discount = stof(trim(line));
                    break;
                } catch (std::exception &) {
                    cerr <<
                            "You entered an invalid discount value!\n A valid discount value is a number between 0.0 and 89.9.\nPress any key to continue...";
                    _getch();
                }
            }

            if (discount >= 90.f) {
                cerr << "Discount rate must less than 90!\nPress any key to continue...";
                _getch();
                continue;
            }

            break;
        }

        cout << "\n*" << trainstation.get_trainstation_name() << "* -> *" << destination << "*\n\n";

        // trainstation.buy_train_ticket(L"Budapest", 10.f);
        const auto found_trains = trainstation.buy_train_ticket(destination, discount);
        string available_trains{};

        if (found_trains.empty()) {
            available_trains = std::format("There's no train departures scheduled for '{}'!", destination);
        } else {
            for (const auto i: found_trains) {
                available_trains += to_string(i);
                available_trains += ", ";
            }
        }

        available_trains += " d -> Specify new destination, x -> Exit program\n";

        if (!found_trains.empty()) {
            cout << "Which of the available trains would you like to travel by to " << destination <<
                    " railway station?\n" << available_trains;
        } else {
            cout << available_trains << '\n';
        }

        cout << "Your choice: ";

        string chosen_railway_line_index{};
        getline(cin, chosen_railway_line_index);
        chosen_railway_line_index = trim(chosen_railway_line_index);

        chosen_railway_line_index = trim(chosen_railway_line_index);
        if (chosen_railway_line_index == "x" || chosen_railway_line_index == "X") break;
        if (chosen_railway_line_index == "d" || chosen_railway_line_index == "D") continue;

        size_t railway_line_index{};
        while (!chosen_railway_line_index.empty() && chosen_railway_line_index[0] >= '1' && chosen_railway_line_index[0]
               <= '9') {
            railway_line_index = stoul(chosen_railway_line_index);

            if (found_trains.contains(railway_line_index)) {
                const auto departed_train = trainstation.departs(railway_line_index - 1, cout);
                cout << std::format("Train {} left railway station {} and is going to railway station {}.\n",
                                    departed_train->get_train_name(), trainstation.get_trainstation_name(),
                                    destination);
            }
        }
    }

    cout << "Exiting program...\n";

    return 0;
}
