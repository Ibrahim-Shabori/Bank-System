#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsLoginRegister.h"
#include <iomanip>

class clsLogRegisterScreen:protected clsScreen
{

private:
   static void PrintLoginRegisterRecordLine(clsLoginRegister Record)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Record.DateTime();
        cout << "| " << setw(20) << left << Record.UserName();
        cout << "| " << setw(20) << left << Record.Password();
        cout << "| " << setw(10) << left << Record.Permissions();
    }

public:
  

   static void ShowLoginRegistersList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegistersList)) return;
        vector <clsLoginRegister> vRecords = clsLoginRegister::GetLoginRegistersList();
        string Title = "\t  Login Register List Screen";
        string SubTitle ="\t    (" + to_string(vRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout <<  setw(8) << left << "" << "| " << left << setw(30) << "Date Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Login Registers Available In the System!";
        else

            for (clsLoginRegister Record : vRecords)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};
