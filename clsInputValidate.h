#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "clsDate.h"

using namespace std;

class clsInputValidate{
    public:
        static bool IsNumberBetween(int Number, int From, int To){
            if (To > From){
                return (Number>=From) && (Number<=To);
            } else {
                return (Number>=To) && (Number<=From);
            }
        }

        static bool IsNumberBetween(double Number, double From, double To){
            if (To > From){
                return (Number>=From) && (Number<=To);
            } else {
                return (Number>=To) && (Number<=From);
            }
        }

        static bool IsDateBetween(clsDate TestedDate, clsDate Date1, clsDate Date2){
            if (clsDate::IsValidDate(Date1) && clsDate::IsValidDate(Date2)){
                if (clsDate::IsDate1BeforeDate2(Date1, Date2)){
                    if(clsDate::IsDate1BeforeDate2(TestedDate, Date2) || clsDate::IsDate1EqualDate2(TestedDate, Date2)){
                        if (clsDate::IsDate1AfterDate2(TestedDate, Date1) || clsDate::IsDate1EqualDate2(TestedDate, Date1)){
                            return true;
                        } else return false;
                    }
                } else if (clsDate::IsDate1BeforeDate2(Date2, Date1)){
                    if(clsDate::IsDate1BeforeDate2(TestedDate, Date1) || clsDate::IsDate1EqualDate2(TestedDate, Date1)){
                        if (clsDate::IsDate1AfterDate2(TestedDate, Date2) || clsDate::IsDate1EqualDate2(TestedDate, Date2)){
                            return true;
                        } else return false;
                    }
                } else return clsDate::IsDate1EqualDate2(TestedDate, Date1);
            } else {
                return false;
            }
        }

        static bool isValidDate(clsDate Date1){
            return clsDate::IsValidDate(Date1);
        }

        static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n"){
            int Number;
            while(!(cin>>Number)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ErrorMessage;
            }
            return Number;
        }

        static double ReadDoubleNumber(string ErrorMessage = "Invalid Number, Enter again:\n"){
            double Number;
            while(!(cin>>Number)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ErrorMessage;
            }
            return Number;
        }

        static int ReadNumberBetween(int From, int To, string Errormessage = "Invalid Number, Enter again:\n"){
            int Number = ReadIntNumber(Errormessage);
            while (!IsNumberBetween(Number, From, To)){
                cout << Errormessage;
                Number = ReadIntNumber(Errormessage);
            }
            return Number;
        }

        static double ReadDoubleBetween(double From, double To, string Errormessage = "Invalid Number, Enter again:\n"){
            double Number = ReadDoubleNumber(Errormessage);
            while (!IsNumberBetween(Number, From, To)){
                cout << Errormessage;
                Number = ReadDoubleNumber(Errormessage);
            }
            return Number;
        }

        static string ReadString(){
		string  S1="";
		// Usage of std::ws will extract all the whitespace character
		getline(cin >> ws, S1);
		return S1;
	}
};