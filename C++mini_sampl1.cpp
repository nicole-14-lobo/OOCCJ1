#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>
#include<string>
#include<algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
using namespace std;
class owner
{
protected:
    int n;
    int ch;
    int cars[10]={100,101,103,104,105};
    int carprice[10]={2000,3500,5000,3500,5500};
    string carnm[50]={"Maruti Swift","Hyundai i10","Toyota Fortuner","Hyundai Verna","Mahindra XUV500"};
    string cardesc[50]={"5-Seater","5-Seater","7-Seater","5-Seater","7-Seater"};
public:
    void owner1()
    {
        fstream file1;
        file1.open("Cars12.dat",ios::app);
        cout<<"1.Do you want to add cars\n2.Check the bookings\n"<<endl;
        cin>>ch;

        if(ch==1)
        {
            cout<<"How many car records you want to add? "<<endl;
            cin>>n;
            int j=sizeof(cars)/sizeof(cars[0]);
            for(int i=j+1;i<j+n+1;i++)
            {
                cout<<"Car registration: "<<endl;
                cin>>cars[i];
                cout<<"Car name: "<<endl;
                cin>>carnm[i];
                cout<<"Car Price: "<<endl;
                cin>>carprice[i];
                cout<<"Car Description: "<<endl;
                cin>>cardesc[i];
            }
            file1.seekg(0, std::ios::end);
            for(int i=sizeof(cars)/sizeof(cars[0])+1;i<sizeof(cars)/sizeof(cars[0])+n+1;i++)
            {
                file1<<cars[i]<<"\t"<<carnm[i]<<"\t\t"<<cardesc[i]<<"\t"<<carprice[i]<<endl;
            }
            file1.close();
        }

        if(ch==2)
        {
            file1.open("customers1.dat",ios::in|ios::out);
            string line;
            string file_contents = "";
            while (getline(file1, line))
            {
                file_contents += line + "\n";
                cout << line << endl;
            }
            file1.close();
        }
    }
    ~owner(){}
};


class Customer: public owner
{
protected:
    string name, phone_no,address,aadhar_no,pincode;
    string delivery_loc;
    int veh_reg,no_days,flag=1;
    vector<int>vec={100};
    float crpr=0;
    string strnm;
    friend int excep1(Customer &C);

public:
    Customer()
    {}

    void Customer1()
    {
        cout<<"Name: "<<endl;
        cin>>name;
        cout<<"Phone Number: "<<endl;
        cin>>phone_no;
        cout<<"Address: "<<endl;
        cin>>address;
        cout<<"Choose your Favourite Model"<<endl;
        cout<<"Enter the VEHICLE REGISTRATION NUMBER to book: "<<endl;
        cin>>veh_reg;
        cout<<"How many days? "<<endl;
        cin>>no_days;
        cout<<"Delivery Location: "<<endl;
        cout<<"If delivery address is same as Address enter 'same'"<<endl;
        cin>>delivery_loc;
        if(delivery_loc=="same"||delivery_loc=="Same")
        {
                delivery_loc=address;
        }
        cout<<"Pincode: "<<endl;
        cin>>pincode;
    }

    int cndns();
    ~Customer(){}
};


int Customer::cndns()
{
    int flag=0;
    for(int i=0;i<sizeof(cars)/sizeof(cars[0]);i++)
    {
        if(veh_reg==cars[i])
        {
            crpr=carprice[i];
            flag=1;
            strnm=carnm[i];
        }
    }
    if(flag==0)
    {
        cout<<"Invalid registration vehicle number"<<endl;
        return 0;
    }
    else
    {
        try
        {
            std::vector<int>::iterator it;
            it= find(vec.begin(),vec.end(),veh_reg);
            if(it!=vec.end())
            {
                throw(veh_reg);
            }
        }
        catch(int &veh_reg)
        {
            cout<<"\t\t This car is Already Booked!!!! We are very Sorryy!!!"<<endl;
            flag=0;
        }
    }
    if(flag==0)
    {
            return 0;
    }
    else
    {
        vec.push_back(veh_reg);
        return 1;
    }
}


int excep1(Customer &C)
{
    int flag=1;
    vector<string> vec{"411","421","431"};
    int i;
    std::vector<string>::iterator it;
    it = find(vec.begin(),vec.end(), C.pincode);
    try
    {
        if(it == vec.end())
        {
            throw(C.pincode);
        }
    }
    catch (string &pincode)
    {
        cout<<"We deliver only in Mumbai"<<endl;
        flag=0;
    }
    if(flag==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


class Calcs: public Customer
{
protected:
    static int i;
    fstream file2;
    float total_bill;
public:
    void Calcs1()
    {
        file2.open("customers1.dat",ios::app);
        if(no_days>=7)
        {
            total_bill=(crpr*no_days)-(crpr*no_days)*0.2;
        }
        else
        {
            total_bill=(crpr*no_days);
        }
        file2<<"Name: "<<name<<"\n"<<"Phone Number: "<<phone_no<<"\n"<<"Address: "<<address<<"\n"<<"Pincode: "<<pincode<<"\n";
        file2<<"Vehicle Registration Number: "<<veh_reg<<"\n"<<"Duration: "<<no_days<<"\n"<<"Delivery Location: "<<delivery_loc<<"\n"<<"Total Bill: "<<total_bill<<"\n";
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&time);
        cout<<endl<<endl;
        cout<<"\t\t\tInvoice No. :"<<i<<endl;
        cout<<"\t\t\tCustomer Name: "<<name<<endl;
        cout<<"\t\t\tCustomer Mobile Number: "<<phone_no<<endl;
        cout<<"\t\t\tCar Model: "<<strnm<<endl;
        cout<<"\t\t\tCar No.:  "<<veh_reg<<endl;
        cout<<"\t\t\tNumber of days: "<<no_days<<endl;
        cout<<"\t\t\tYour Rental Amount is: "<<total_bill<<endl;
        cout<<"\t\t\tAdvanced amount to pay is: "<<(total_bill/2)<<endl<<endl;
        cout<<"\t\t----This is a computer generated invoice and it does not require an authorised signture ----"<<endl<<endl;
        cout<<"\t\t\tYou are advised to pay up the amount before "<< (now_tm->tm_year + 1900) << '-'<< (now_tm->tm_mon + 1) << '-'<< (now_tm->tm_mday)+5<<endl;
        cout<<"\t\t\tYOU WILL GET CONFIRMATION BY "<<(now_tm->tm_year + 1900) << '-'<< (now_tm->tm_mon + 1) << '-'<< (now_tm->tm_mday)+1<<endl;
        cout<<"\t\t\tYou can pay on ram19456@okhdfc-bank Google-Pay"<<endl;
        file2.close();
    }

    void  virtual avail()
    {
        cout<<"\t\tThe following are the cars booked"<<endl;
        cout<<"\t\t\tTHESE CARS AREN'T AVAILABLE"<<endl;
        int it;
        for(it=0;it<vec.size();it++)
        {
            cout<<"\t\t\t"<<vec[it] <<"\t"<<carnm[it]<<endl;
        }
        int flag;
        cout<<"\t\t\tThe following are the list of cars AVAILABLE: "<<endl;
        cout<<"\t\t\t\tLIST OF CARS AVAILABLE NOW!!!!!!!!"<<endl;
        fstream file4;
        string line;
        file4.open("Cars12.dat",ios::in);
        while(getline(file4, line))
        {
                cout<<"\t\t\t"<<(line)<<endl;
        }
        file4.close();
    }
    ~Calcs(){}
};
int Calcs::i=11;

class Payments:  public Calcs
{
protected:
    int choice;
    string ans;
    string upi;
    string mode;
    fstream file6;
    void avail()
    {
        file6.open("customers1.dat",ios::app);
        xyz: cout<<"\t\t\tWhich mode of payment will you prefer"<<endl;
        cout<<"\t\t1.Full Payment while Delivery\n\t\t2.Google-Pay Advance payment and rest at the time of delivery"<<endl;
        cin>>choice;
        if(choice==1)
        {
            cout<<"Are you sure(y/n)?"<<endl;
            cin>>ans;
            if(ans=="y")
            {
                mode="WHILE DELIVERY";
                file6<<"Mode of Payment"<<mode<<endl;
                cout<<"!!!!!YOU ARE IN WAITING LIST!!!!"<<endl;
                cout<<"Have a great day ahead"<<endl;
            }
            else
            {
                goto xyz;
            }
        }
        if(choice==2)
        {
            mode="G-PAY";
            cout<<"Enter your UPI"<<endl;
            cin>>upi;
            cout<<"OPEN YOUR UPI TO PAY!!!!!!"<<endl;
            sleep(5);
            file6<<"Mode of Payment: "<<mode<<endl<<endl<<endl;
            cout<<"YOUR CAR IS 50% BOOKED!!!! YOU'LL GET CONFIRMATION SOON"<<endl;
            cout<<"ELSE MONEY WILL BE REFUNDED!!!!"<<endl;
        }
        file6.close();
    }
};
int main()
{
    int ch,ans,ans1;
    int pass;
    string sec_no;
    Calcs A;
    Calcs *aref;
    Payments B;
    aref=&A;
    aref->avail();
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"\t\t\tWELCOME TO CAR RENTAL SYSTEM"<<endl;
    cout<<"\t\t\tWE RENT CARS IN MUMBAI ONLY"<<endl<<endl;
    cout<<"\t\t\tBOOK YOUR CAR 5 DAYS PRIOR"<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<endl<<endl;
    cout<<"\t\t1.Customer login\n\t\t2.Owner Login\n\t\t3.Exit"<<endl;
    cout<<"\t\t\tEnter your choice: "<<endl;
    cin>>ch;
    if(ch==1)
    {
        A.Customer1();
        ans=A.cndns();
        ans1=excep1(A);
        if(ans==1 && ans1==1)
        {
            A.Calcs1();
            aref=&B;
            aref->avail();

        }
    }
    else if(ch==2)
    {
        cout<<"Enter the password: "<<endl;
        cin>>pass;
        cout<<"Enter the security number: "<<endl;
        cin>>sec_no;
        if(pass=9009 && sec_no=="THM")
        {
            A.owner1();
        }
    }
    else if(ch==3)
    {
        cout<<"Exited"<<endl;
    }
    else
    {
        cout<<"Wrong Choice"<<endl;
    }
    return 0;
}
