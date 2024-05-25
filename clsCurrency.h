#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsCurrency{
private:
    enum enMode {EmptyMode = 1, UpdateMode = 2};
    enMode _Mode;
    string _Country;
    double _ChangeRate;
    string _CurrencyCode;
    string _CurrencyName;

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#"){
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Separator);
        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1],
                             vCurrencyData[2], stod(vCurrencyData[3]));
    }

    static vector<string> _ConvertCurrencyDataToVector(clsCurrency Currency){
        vector<string> vCurrencyData(4);
        vCurrencyData[0] = Currency.Country();
        vCurrencyData[1] = Currency.CurrencyCode();
        vCurrencyData[2] = Currency.CurrencyName();
        vCurrencyData[3] = to_string(Currency.ChangeRate());
        return vCurrencyData;
    }

    static string _ConvertCurrencyDataToLine(clsCurrency &Currency){
        vector<string> vCurrencyData;
        vCurrencyData = clsCurrency::_ConvertCurrencyDataToVector(Currency);
        string Line;
        Line = clsString::JoinString(vCurrencyData, "#//#");
        return Line;
    }

    static vector<clsCurrency> _LoadCurrenciesDataFromFile(){
        vector<clsCurrency> Currencies;
        fstream File;
        File.open("Currencies.txt", ios::in);
        if (File.is_open()){
            string Line;
            while(getline(File, Line)){
                clsCurrency Currency = clsCurrency::_ConvertLineToCurrencyObject(Line);
                Currencies.push_back(Currency);
            }
            File.close();
        }
        return Currencies;
    }

    void _SaveCurrenciesDataToFile(vector<clsCurrency> vCurrencies){
        fstream File;
        File.open("Currencies.txt", ios::out);
        if (File.is_open()){
            for (clsCurrency &C : vCurrencies){
                string CurrencyData = clsCurrency::_ConvertCurrencyDataToLine(C);
                File << CurrencyData << "\n";
            }
            File.close();
        }
    }

    void _Update(){
        vector<clsCurrency> vCurrencies;
        vCurrencies = _LoadCurrenciesDataFromFile();
        for (clsCurrency &C: vCurrencies){
            if (C.Country() == Country()){
                C = *this;
                break;
            }
        }
        _SaveCurrenciesDataToFile(vCurrencies);
    }

    void _AddDataLineToFile(string Line){
        fstream File;
        File.open("Currencies.txt", ios::out | ios::app);
        if (File.is_open()){
            File << Line << "\n";
            File.close();
        }
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertCurrencyDataToLine(*this));
    }

    static clsCurrency _GetEmptyCurrencyObject(){
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double ChangeRate){
        _Mode = Mode;
        _Country = Country;
        _CurrencyName = CurrencyName;
        _CurrencyCode = CurrencyCode;
        _ChangeRate = ChangeRate;
    }

    bool IsEmpty(){
        return (_Mode == clsCurrency::enMode::EmptyMode);
    }

    string Country(){
        return _Country;
    }

    string CurrencyName(){
        return _CurrencyName;
    }

    string CurrencyCode(){
        return _CurrencyCode;
    }

    void SetChangeRate(double ChangeRate){
        _ChangeRate = ChangeRate;
        _Update();
    }

    double ChangeRate(){
        return _ChangeRate;
    }

    void Print(){
        cout << "\n         Currency Card:    \n";
        cout << "----------------------------------\n";
        cout << "Country: " << Country() << "\n";
        cout << "Currency Code: " << CurrencyCode() << "\n";
        cout << "Currency Name: " << CurrencyName() << "\n";
        cout << "Change Rate(1$): " << ChangeRate() << "\n";
        cout << "----------------------------------\n";
    }

    static clsCurrency FindByCountry(string Country){
        fstream File;
        File.open("Currencies.txt", ios::in);
        string Line;
        if (File.is_open()){
            while (getline(File, Line)){
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.Country() == Country){
                    File.close();
                    return Currency;
                }
            }
            File.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCurrencyCode(string CurrencyCode){
        fstream File;
        File.open("Currencies.txt", ios::in);
        string Line;
        if (File.is_open()){
            while (getline(File, Line)){
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode){
                    File.close();
                    return Currency;
                }
            }
            File.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCodeOrCountry){
        clsCurrency C1 = clsCurrency::FindByCurrencyCode(CurrencyCodeOrCountry);
        clsCurrency C2 = clsCurrency::FindByCountry(CurrencyCodeOrCountry);
        return (!C1.IsEmpty() || !C2.IsEmpty());
    }

    static vector<clsCurrency> GetCurrenciesList(){
        return _LoadCurrenciesDataFromFile();
    }

};