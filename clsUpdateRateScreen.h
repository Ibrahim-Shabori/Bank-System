#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateRateScreen :protected clsScreen

{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n         Currency Card:    \n";
        cout << "----------------------------------\n";
        cout << "Country: " << Currency.Country() << "\n";
        cout << "Currency Code: " << Currency.CurrencyCode() << "\n";
        cout << "Currency Name: " << Currency.CurrencyName() << "\n";
        cout << "Change Rate(1$): " << Currency.ChangeRate() << "\n";
        cout << "----------------------------------\n";

    }

public:

    static void ShowUpdateRateScreen()
    {

        _DrawScreenHeader("\tUpdate Rate Screen");

        string CurrencyName = "";

        cout << "\nPlease Enter Currency Code or Country: ";
        CurrencyName = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyName))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyName = clsInputValidate::ReadString();
        }

        clsCurrency Currency1 = clsCurrency::FindByCountry(CurrencyName);
        if (Currency1.IsEmpty()) Currency1 = clsCurrency::FindByCurrencyCode(CurrencyName);

        _PrintCurrency(Currency1);

        cout << "\nAre you sure you want to update this Currency y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";
            cout << "\n Enter The new Rate(1$): ";
            double Rate;
            Rate = clsInputValidate::ReadDoubleNumber();
            Currency1.SetChangeRate(Rate);
            _PrintCurrency(Currency1);
            cout << "\n Saved Successfully!\n";
        }

    }
};

