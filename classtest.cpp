#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

ofstream fout;
ifstream fin;

class inventory
{
    public:
    string ID;
    int qty;

    inventory(string ID_inp, int qty_inp)
    {
        this->ID = ID_inp;
        this->qty = qty_inp;
    }

    inventory()
    {
        //default constructor
    }

    void output();

    //Getter functions
    string getID() const;
    int getQty() const;

    //Setter functions
    
};

void inventory::output()
{
    cout<<"ID: "<<this->ID<<endl;
    cout<<"Quantity: "<<this->qty<<endl;
}

string inventory::getID() const
{
    return this->ID;
}

int inventory::getQty() const
{
    return this->qty;
}

void fileIn(vector <inventory> &a)
{
    fin.open("inv.txt");

    for (inventory temp;
            fin >> temp.ID
                >> temp.qty; )
    {
        a.push_back(temp);
    }

    /*above code thanks to https://ideone.com/hMgoP from https://stackoverflow.com/questions/9979894/using-vector-of-user-defined-class-type-objects*/

    /*
    while(!fin.eof())
    {
        inventory fileInput;

        fin>>fileInput.ID;
        fin>>fileInput.qty;

        a.push_back(fileInput);
    }
    */

    fin.close();
}

void fileOut(vector <inventory> a)
{
    int size = a.size();

    for(int i = 0; i<size; i++)
    {
        if(i == 0)
        {
            fout.open("inv.txt");

            fout<<a[i].ID<<endl;
            fout<<a[i].qty<<endl;

            fout.close();
        }
        else
        {
            fout.open("inv.txt", ios::app);

            fout<<a[i].ID<<endl;
            fout<<a[i].qty<<endl;

            fout.close();
        }
    }
}

int search(vector <inventory> a, string query)
{
    auto it = find_if(a.begin(), a.end(),                                               //range
                    [&query](const inventory& obj) {return obj.getID() == query;});     //condition to find

    int index;

    if (it != a.end())
    {
        // found element. it is an iterator to the first matching element.
        // if you really need the index, you can also get it:
        index = distance(a.begin(), it);
    }

    return index;

    //from https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
}

int anotherSearch(vector<inventory> a, string query)
{
    vector<inventory>::iterator it;
    int index;

    for (it = a.begin(); it<a.end(); it++)
    {
        if ((*it).getID() == query)
        {
            index = distance(a.begin(), it);

            return index;
            break;
        }
    }

    /*---ERROR HANDLING---*/
    // Returns the value of the index at which the searched element resides only if
    // the element exists, if the element does not exist, the program is aborted.
    
    /* Could find better solution */

    try
    {
        if (index >= a.size() || index < 0)
        {
            throw std::invalid_argument("The element doesn't exist. Please try again. Aborting Program.");
        }
    }
    catch (const std::invalid_argument &e)
    {
        cerr<<e.what()<<endl;
    }
    
    return -1;
}

/*  Need to find which search is faster  */

void newItem(vector<inventory> &a)
{
    string newID;
    int newQty;

    cout<<"Enter the ID of the new item:"<<endl;
    cin>>newID;
    cout<<"Enter the Quantity of the new Item:"<<endl;
    cin>>newQty;

    int in;
    in = anotherSearch(a, newID);

    if(in == -1)
    {
        inventory temp(newID, newQty);
        a.push_back(temp);
    }
    else
    {
        cout<<"An item with the same ID already exists. Please choose from one the following options:"<<endl
            <<"1. Append the quantity of the new Items to the quantity of the existing Item."<<endl
            <<"2. Try Again"<<endl;
        int opt;
        cin>>opt;

        if (opt == 1)
        {
            a[in].qty = a[in].qty + newQty;
        }
        else
        {
            newItem(a);
        }
    }
    

    /* ------NOT COMPLETED------ */

}

void editItem(vector<inventory> &a)
{
    string queryinp;
    
    cout<<"search for element:"<<endl;
    cin>>queryinp;

    auto index = anotherSearch(a, queryinp);

    cout<<"the element is:"<<endl;
    a[index].output();
    cout<<"Enter new values:"<<endl;
    int newQty;
    string newID;
    cout<<"New Quantity:"<<endl;
    cin>>newQty;
    cout<<"New ID:"<<endl;
    cin>>newID;

    a[index].ID = newID;
    a[index].qty = newQty;
}

void mainMenu(vector<inventory> &a)
{
    bool runAgain = true;

    cout<<"Welcome."<<endl;
    
    do
    {
        cout<<"Please select an option from the following:"<<endl
            <<"1. View"<<endl
            <<"2. New"<<endl
            <<"3. Edit"<<endl
            <<"4. Search"<<endl;

        int menu_opt;
        
        cin>>menu_opt;


        if(menu_opt == 1)
        {
            for(int i = 0; i<a.size(); i++)
            {
                a[i].output();
            }
        }
        else if(menu_opt == 2)
        {
            newItem(a);
        }
        else if(menu_opt == 3)
        {
            editItem(a);
        }
        else if(menu_opt == 4)
        {
            string inputQuery;
            int searchIndex;

            cout<<"Enter search query: "<<endl;
            cin>>inputQuery;
            
            searchIndex = anotherSearch(a, inputQuery);
            a[searchIndex].output();
        }
        else
        {
            cout<<"Wrong input."<<endl;
        }
        

        char cont;
        
        cout<<"Do you want to run again? ('Y' or 'N')"<<endl;
        cin>>cont;

        if(cont == 'N' || cont == 'n')
        {
            runAgain = false;
            
            /*---- Asking user to save changes ----*/

            char save;

            cout<<"Do you want to save existing changes? (Y/N)"<<endl;
            cin>>save;

            if(save == 'Y' || save == 'y')
                fileOut(a);
        }
    } while (runAgain == true);
}

int main()
{
    vector <inventory> main;

    fileIn(main);

    //inventory h("LOLOL", 3);
    //main.push_back(h);

    // int size = main.size();

    //cout<<size<<endl;

    // for (int i = 0; i<main.size(); i++)
    // {
    //     main[i].output();
    // }

    //editItem(main);

    
    // int in;
    // in = anotherSearch(main, "AAAAB");
    // cout<<in<<endl<<endl<<endl;

    // newItem(main);

    // for (int i = 0; i<main.size(); i++)
    // {
    //     main[i].output();
    // }

    mainMenu(main);

    //fileOut(main);

    return 0;
    
}
