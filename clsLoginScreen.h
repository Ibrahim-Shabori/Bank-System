#pragma once

#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"
#include "clsLoginRegister.h"

class clsLoginScreen :protected clsScreen
{

private :
  static bool _Login()
    {
        bool LoginFaild = false;
        int Trials = 3;
        string Username, Password;
        do
        {
            if (LoginFaild)
            {
                Trials--;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "You Have "<< Trials << " Trils left!\n";
            }
            if (Trials==0) return false;
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        
        clsLoginRegister NewLoginRegister;
        NewLoginRegister.Save();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

