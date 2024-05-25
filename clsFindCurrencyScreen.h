#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen :protected clsScreen
{

private :
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

    static void ShowFindCurrencyScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange)) return;
        _DrawScreenHeader("\tFind Currency Screen");

        string CurrencyName;
        cout << "\nPlease Enter Currency or Country Name: ";
        CurrencyName = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyName))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyName = clsInputValidate::ReadString();
        }

        clsCurrency Currency1 = clsCurrency::FindByCountry(CurrencyName);
        if (Currency1.IsEmpty()) Currency1 = clsCurrency::FindByCurrencyCode(CurrencyName);

        if (!Currency1.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }

        _PrintCurrency(Currency1);

    }

};

