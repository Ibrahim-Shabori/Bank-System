#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsTransfer.h"

using namespace std;

class clsTransferScreen : protected clsScreen{
private:
    static clsBankClient _AskForSenderClient(){
        string AccountNumber = "";

        cout << "\nPlease Enter The Sender Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return clsBankClient::Find(AccountNumber);
    }

    static clsBankClient _AskForRecieverClient(){
        string AccountNumber = "";

        cout << "\nPlease Enter The Reciever Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return clsBankClient::Find(AccountNumber);
    }

    static void _PrintClient(clsBankClient Client){
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode();
        cout << "\nBalance     : " << Client.AccountBalance();
        cout << "\n___________________\n";

    }

    static void PrintTransferRecordLine(clsTransfer Record)
    {
        cout <<  setw(8) << left << "" << "| " << left << setw(25) << Record.DateTime();
        cout << "| " << left << setw(12) << Record.SenderAccountNumber();
        cout << "| " << left << setw(12) << Record.RecieverAccountNumber();
        cout << "| " << left << setw(10) << Record.Amount();
        cout << "| " << left << setw(15) << Record.SenderAmountAfterTransfer();
        cout << "| " << left << setw(15) << Record.RecieverAmountAfterTransfer();
        cout << "| " << left << setw(15) << Record.UserName();
    }
public:
    static void ShowTransferScreen(){
        _DrawScreenHeader("Transfer Screen");
        clsBankClient Sender = _AskForSenderClient();
        _PrintClient(Sender);
        clsBankClient Reciever = _AskForRecieverClient();
        _PrintClient(Reciever);
        cout << "\nPlease Enter The Amount You Want To Transfer: ";
        double Amount = clsInputValidate::ReadDoubleNumber();
        while(!Sender.Withdraw(Amount)){
            cout << "\nYou Can't Transfer This Amount! Please Enter a Possibe Ammount: ";
            Amount = clsInputValidate::ReadDoubleNumber();
        }
        cout << "Transfered Successfully!!\n";
        Reciever.Deposit(Amount);
        _PrintClient(Sender);
        _PrintClient(Reciever);
        clsTransfer NewTransfer(Sender, Reciever, Amount);
        NewTransfer.Save();
    }

    static void ShowTransfersList()
    {
        vector <clsTransfer> vRecords = clsTransfer::GetTransferList();
        string Title = "\t  Transfers List Screen";
        string SubTitle ="\t    (" + to_string(vRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);
        

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________\n" << endl;

        cout <<  setw(8) << left << "" << "| " << left << setw(25) << "Date Time";
        cout << "| " << left << setw(12) << "Sender Acc.";
        cout << "| " << left << setw(12) << "Reciever Acc.";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "Sender Balance";
        cout << "| " << left << setw(15) << "Reciver Balance";
        cout << "| " << left << setw(15) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsTransfer Record : vRecords)
            {

                PrintTransferRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________________\n" << endl;

    }
};
