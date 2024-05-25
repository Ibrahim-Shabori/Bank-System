#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen{
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
    static void ShowCurrencyCalculatorScreen(){
        _DrawScreenHeader("\tCurrency Exchange Screen");
        string CurrencyName;
        cout << "\nPlease Enter Currency or Country Name You Want To Convert From: ";
        CurrencyName = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyName))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyName = clsInputValidate::ReadString();
        }

        clsCurrency Currency1 = clsCurrency::FindByCountry(CurrencyName);
        if (Currency1.IsEmpty()) Currency1 = clsCurrency::FindByCurrencyCode(CurrencyName);

        _PrintCurrency(Currency1);

        cout << "\nPlease Enter Currency or Country Name You Want To Convert To: ";
        CurrencyName = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyName))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyName = clsInputValidate::ReadString();
        }

        clsCurrency Currency2 = clsCurrency::FindByCountry(CurrencyName);
        if (Currency2.IsEmpty()) Currency2 = clsCurrency::FindByCurrencyCode(CurrencyName);

        _PrintCurrency(Currency2);

        cout << "\n Enter The Amount To Exchange: ";
        double Amount = clsInputValidate::ReadDoubleNumber();
        double Converted = Amount * Currency2.ChangeRate() / Currency1.ChangeRate();
        cout << "\n " << Amount << " Of " << Currency1.CurrencyName() << "s Equals "
             << Converted << " Of " << Currency2.CurrencyName() << "s!.\n";
    }
};

