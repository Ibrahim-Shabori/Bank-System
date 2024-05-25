#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"


using namespace std;

class clsScreen
{
protected :
    static void _DrawScreenHeader(string Title,string SubTitle ="")
    {
        cout << "\t\t\t\t\t_____________________________________";
        cout << "\n\n\t\t\t\t\t" << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t" << SubTitle;
        }
        cout << "\n\t\t\t\t\t_____________________________________\n\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.GetUserName() << "\n";
        clsDate Date;
        cout << "\t\t\t\t\tDate: "; Date.Print(); 
    }

    static bool CheckAccessRights(clsUser::enPermissions Permissions){
        if (!CurrentUser.CheckAccessPermission(Permissions)){
            cout << "\t\t\t\t\t_____________________________________";
            cout << "\n\n\t\t\t\t\t Access Denied!";
            cout << "\n\t\t\t\t\t_____________________________________\n\n";
            return false;
        } else{
            return true;
        }
    }
};

