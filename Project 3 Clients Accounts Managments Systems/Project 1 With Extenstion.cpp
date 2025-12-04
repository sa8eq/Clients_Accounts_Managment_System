#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
void ShowMainMenuScreen();
void ShowTransactionScreen();
const string ClientsFileName = "Clients.txt";
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool MarkForDelete = false;
};
enum enOption
{
    enPrintClientsList = 1, enAddClient, enDeleteClient,
    enUpdateClient, enFindClient, eTransAction, enExit
};
enum enTransOption
{
    enDeposit = 1, enWithdrawl, enShowTotalBalances, GoToMainMenue
};
short ChooseOption(short From, short To)
{
    short a = 0;
    do
    {
        cout << "Choose What You Want To Do [" << From << "/" << To << "] ";
        cin >> a;
    } while (a > To || a < From);
    return a;
}
void ReturnToMainMenuScreen()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    system("cls");
    ShowMainMenuScreen();
}
void ReturnToTransactionMenu()
{
    cout << "\n\nPress any key to go back to Transaction Menue...";
    system("pause>0");
    system("cls");
    ShowTransactionScreen();
}
void ProgramEndScreen()
{
    cout << "==========================================================\n";
    cout << "\t\t      Program Ends\n";
    cout << "==========================================================\n";
}
vector <string> SplitWords(string S1, string delim)
{
    vector <string> Elements;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            Elements.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != "")
    {
        Elements.push_back(S1);
    }
    return Elements;
}
stClient ConvertLineToRecord(string Line, string delim = "#//#")
{
    vector <string> Elements = SplitWords(Line, delim);
    stClient C;
    C.AccountNumber = Elements[0];
    C.PinCode = Elements[1];
    C.Name = Elements[2];
    C.Phone = Elements[3];
    C.Balance = stod(Elements[4]);
    return C;
}
vector <stClient> LoadDataFromFile(string FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
void PrintClientRecord(stClient C)
{
    cout << "| " << left << setw(20) << C.AccountNumber;
    cout << "| " << left << setw(15) << C.PinCode;
    cout << "| " << left << setw(40) << C.Name;
    cout << "| " << left << setw(12) << C.Phone;
    cout << "| " << left << setw(12) << C.Balance;

}
void ShowClientsListScreen()
{
    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\t\tClients List\n";
    cout << "================================================================================================================\n";
    cout << "| " << setw(20) << left << "Account Number";
    cout << "| " << setw(15) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Name";
    cout << "| " << setw(12) << left << "Phone";
    cout << "| " << setw(12) << left << "Account Balance";
    cout << "\n================================================================================================================\n";
    if (vClients.size() == 0)
    {
        cout << "\n\t\t\t\t\tTheir Is No Clients To Display\n";
    }
    else
    {
        for (stClient& C : vClients)
        {
            PrintClientRecord(C);
            cout << endl;
        }
    }
    cout << "================================================================================================================\n";


}
bool FindClientByAccoutNumber(string AccountNumber, string FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
    }
    return false;
}
stClient ReadNewClient()
{
    stClient C;
    cout << "\nEnter Account Number:  ";
    getline(cin >> ws, C.AccountNumber);
    while (FindClientByAccoutNumber(C.AccountNumber, ClientsFileName))
    {
        cout << "\nThis Account Number Already Exists, Enter Another Account Number: ";
        getline(cin >> ws, C.AccountNumber);
    }
    cout << "\nEnter Pin Code: ";
    getline(cin, C.PinCode);
    cout << "\nEnter Name: ";
    getline(cin, C.Name);
    cout << "\nEnter Phone Number: ";
    getline(cin, C.Phone);
    cout << "\nEnter Accout Balance: ";
    cin >> C.Balance;
    return C;
}
void AddDataLineToFile(string FileName, string Line)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << Line << endl;

        MyFile.close();
    }
}
string ConverRecordToLine(stClient C)
{
    string delim = "#//#";
    string Line = "";
    Line += C.AccountNumber + delim;
    Line += C.PinCode + delim;
    Line += C.Name + delim;
    Line += C.Phone + delim;
    Line += to_string(C.Balance);
    return Line;
}
void AddNewClient()
{
    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConverRecordToLine(Client));
}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        AddNewClient();
        cout << "\nClient Has Added Successfully. Do You Want To Add More Clients [Y/N] ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}
void ShowAddClientsScreen()
{
    cout << "--------------------\n";
    cout << "  Adding Clients:\n";
    cout << "--------------------\n\n";

    AddNewClients();
}
string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Enter Account Number\n";
    cin >> AccountNumber;
    return AccountNumber;
}
bool SearchClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool MarkForDelete(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
void PrintClientCard(stClient C)
{
    cout << "\n\nThe Followinngs Are The Client Info\n\n";
    cout << "------------------------------------------\n";
    cout << "Account Number  : " << C.AccountNumber << "\n";
    cout << "Pin Code        : " << C.PinCode << "\n";
    cout << "Name            : " << C.Name << "\n";
    cout << "Phone Number    : " << C.Phone << "\n";
    cout << "Account Balance : " << C.Balance << endl;
    cout << "------------------------------------------\n\n";

}
bool SaveChangesToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClient& C : vClients)
        {
            string Line;
            if (C.MarkForDelete != true)
            {
                Line = ConverRecordToLine(C);
                MyFile << Line << endl;
            }
        }
        return true;
    }
    return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient> vClients)
{
    stClient Client;
    char Delete = 'n';
    if (SearchClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "Are You Sure You Want To Delete This Client [Y/N]\n";
        cin >> Delete;
        if (toupper(Delete) == 'Y')
        {
            MarkForDelete(AccountNumber, vClients);
            SaveChangesToFile(ClientsFileName, vClients);

            vClients = LoadDataFromFile(ClientsFileName);

            cout << "\nClient Has Been Successfully Deleted\n";
            return true;
        }
    }
    else
    {
        cout << "\nThere Is No Client With This Account Number";
        return false;
    }
}
void DeleteClient()
{
    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowDeleteClientsScreen()
{
    cout << "--------------------\n";
    cout << "  Adding Clients:\n";
    cout << "--------------------\n\n";

    DeleteClient();
}
stClient UpdateClientRecord(string AccountNumber)
{
    stClient C;
    C.AccountNumber = AccountNumber;

    cout << "\nEnter New Pin Code: ";
    getline(cin >> ws, C.PinCode);
    cout << "\nEnter New Name: ";
    getline(cin, C.Name);
    cout << "\nEnter New Phone Number: ";
    getline(cin, C.Phone);
    cout << "\nEnter New Account Balance: ";
    cin >> C.Balance;

    return C;
}
bool UpdateRecord(vector <stClient>& vClients, string AccountNumber)
{
    stClient Client;
    char Update = 'n';
    if (SearchClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "Are You Sure You Want To Update This Client Info [Y/N]\n";
        cin >> Update;
        if (toupper(Update) == 'Y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = UpdateClientRecord(AccountNumber);
                    break;
                }
            }
            SaveChangesToFile(ClientsFileName, vClients);

            cout << "\nClient Updated Succesfully\n";
            return true;
        }
    }
    else
    {
        cout << "\nThere Is No Client With This Account Number\n";
        return false;
    }
}
void ShowUpdateClientScreen()
{
    cout << "--------------------\n";
    cout << "  Updating Client:\n";
    cout << "--------------------\n\n";

    string AccountNumber = ReadAccountNumber();
    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    UpdateRecord(vClients, AccountNumber);
}
bool SearchForClient(vector <stClient> vClients, string AccountNumber)
{
    stClient Client;
    if (SearchClientByAccountNumber(AccountNumber, vClients, Client))
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                PrintClientCard(C);
                return true;
            }
        }
    }
    else
    {
        cout << "\nThere is No Client With This Account Number\n";
        return false;
    }
}
void ShowClientInfoScreen()
{
    cout << "--------------------\n";
    cout << "  Finding Client:\n";
    cout << "--------------------\n\n";

    string AccountNumber = ReadAccountNumber();
    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    SearchForClient(vClients, AccountNumber);
}
void PrintClientsBalances(stClient C)
{
    cout << "| " << setw(20) << left << C.AccountNumber;
    cout << "| " << setw(40) << left << C.Name;
    cout << "| " << setw(12) << left << C.Balance;
}
void ShowTotalBalancesScreen()
{
    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    
    if (vClients.size() > 0)
    {
        double TotalBalance = 0;
        cout << "=================================================================================";
        cout << "\n\t\t\t  Balanaces of [" << vClients.size() << "] Clients\n";
        cout << "=================================================================================\n";
        cout << "| " << setw(20) << left << "Account Number";
        cout << "| " << setw(40) << left << "Name";
        cout << "| " << setw(12) << left << "Account Balance";
        cout << "\n=================================================================================\n";
        for (stClient& C : vClients)
        {
            PrintClientsBalances(C);
            TotalBalance += C.Balance;
            cout << endl;
        }
        cout << "=================================================================================";
        cout << "\n\t\t\t   Total Balanace is " << TotalBalance << endl;
        cout << "=================================================================================\n";


    }
    else
    {
        cout << "=================================================================================";
        cout << "\n\t\t\t  Balanaces of [" << vClients.size() << "] Clients\n";
        cout << "=================================================================================\n";
        cout << "\t\t Their Are No Clients To Display Thier Balances";
        cout << "\n=================================================================================\n";

    }
}
bool UpdateAccountBalance(vector <stClient>& vClients, string AccountNumber, double Amount)
{
    stClient Client;
    char DepositYesOrNo = 'n';
    cout << "\nAre You Sure You Want To Deposit This Amount [Y/N]\n";
    cin >> DepositYesOrNo;
    if (toupper(DepositYesOrNo) == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (AccountNumber == C.AccountNumber)
            {
                C.Balance += Amount;
                cout << "\nDeposit Has Been Made Successfully. New Balance is: " << C.Balance << endl;
                SaveChangesToFile(ClientsFileName, vClients);
                break;
            }
            
        }
        return true;
    }
    return false;
}
void ShowWithdrawlScreen()
{
    cout << "--------------------\n";
    cout << "     WithDrawl\n";
    cout << "--------------------\n\n\n";

    vector <stClient> vClients = LoadDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    stClient Client;

    while (!SearchClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nTheir is no Account With This Account Number. Enter An Existing Account Number\n";
        cin >> AccountNumber;
    }
    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nEnter Amount To Withdraw\n";
    cin >> Amount;

    while(Amount > Client.Balance)
    {
        cout << "\nAmount Exceeds The Balance, You Can Withdraw up to: " << Client.Balance << endl;
        cout << "Please Enter Another Amount\n";
        cin >> Amount;
    }
    UpdateAccountBalance(vClients, AccountNumber, Amount * -1);
}
void ShowDepositScreen()
{
    cout << "--------------------\n";
    cout << "     Deposit\n";
    cout << "--------------------\n\n\n";

    vector<stClient>vClients = LoadDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    stClient Client;
    while (!SearchClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nTheir is no Account With This Account Number. Enter An Existing Account Number\n";
        cin >> AccountNumber;
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nEnter Amount To Deposit\n";
    cin >> Amount;
    UpdateAccountBalance(vClients, AccountNumber, Amount);

}
void PerformTransactionMenu(enTransOption enTrOption)
{
    switch (enTrOption)
    {
    case enTransOption::enDeposit:
        system("cls");
        ShowDepositScreen();
        ReturnToTransactionMenu();
        break;
    case enTransOption::enWithdrawl:
        system("cls");
        ShowWithdrawlScreen();
        ReturnToTransactionMenu();
        break;
    case enTransOption::enShowTotalBalances:
        system("cls");
        ShowTotalBalancesScreen();
        ReturnToTransactionMenu();
        break;
    case enTransOption::GoToMainMenue:
        system("cls");
        ShowMainMenuScreen();
        break;
    }
}
void ShowTransactionScreen()
{
    cout << "\n==========================================================\n";
    cout << "\t\t     Transaction Meue\n";
    cout << "==========================================================\n";
    cout << "\t\t  [1] Deposit.\n";
    cout << "\t\t  [2] Withdrawl.\n";
    cout << "\t\t  [3] Show All Balances.\n";
    cout << "\t\t  [4] Return To Main Menu." << endl;
    cout << "==========================================================\n";
    PerformTransactionMenu(enTransOption(ChooseOption(1, 4)));

}
void PerformMainScreenOption(enOption eOption)
{
    switch (eOption)
    {
    case enOption::enPrintClientsList:
        system("cls");
        ShowClientsListScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::enAddClient:
        system("cls");
        ShowAddClientsScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::enDeleteClient:
        system("cls");
        ShowDeleteClientsScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::enUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::enFindClient:
        system("cls");
        ShowClientInfoScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::eTransAction:
        system("cls");
        ShowTransactionScreen();
        ReturnToMainMenuScreen();
        break;
    case enOption::enExit:
        system("cls");
        ProgramEndScreen();
        break;
    }
}
void ShowMainMenuScreen()
{
    cout << "\n==========================================================\n";
    cout << "\t\t      Main Meue\n";
    cout << "==========================================================\n";
    cout << "\t\t  [1] Show Client List.\n";
    cout << "\t\t  [2] Add New Clients.\n";
    cout << "\t\t  [3] Delete Clients.\n";
    cout << "\t\t  [4] Update Clients.\n";
    cout << "\t\t  [5] Find Client.\n";
    cout << "\t\t  [6] Transactions\n";
    cout << "\t\t  [7] Exit\n";
    cout << "==========================================================\n";
    PerformMainScreenOption((enOption)ChooseOption(1,7));
}
int main()
{
    ShowMainMenuScreen();
    system("pause");
    return 0;
}