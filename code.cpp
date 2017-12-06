#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<termios.h>
#include<unistd.h>

using namespace std;

int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

class District
{
private:
      string dist_name;
      char num[10];
public:
      void adddist()
      {
            fstream fp;
            string ar;
            char ch;
            ch = 'y';
            do{
                  int i = 0;
                  string unil;
                  cout<<"Enter the name of the district"<<endl;
                  getline(cin,ar);
                  getline(cin,dist_name);
                  cout<<"Enter the unique number of district"<<endl;
                  while(i<6)
                  {
                        num[i]=getch();
                        cout<<"&";
                        i++;
                  }
                  cout<<endl;
                  unil.append(num);
                  Admin ob;
                  char ar[50];
                  strcpy(ar,dist_name.c_str());
                  int che= ob.checkdistrict(ar); 
                  if(che==1)
                  {
                        cout<<"District with same name exist"<<endl;
                  }
                  else
                  {
                        fp.open("district.csv",ios::out|ios::app);
                        {
                              fp<<unil<<','<<dist_name<<','<<endl;
                        }
                        cout<<"Want to enter more districts- Y or N"<<endl;
                        cin>>ch;
                        fp.close();
                  }
            }while(ch=='y'||ch=='Y');
      }

      void super()
      {
            fstream fp,fq,fw;
            string s;
            char e[100];
            fp.open("super.csv",ios::in);
            fq.open("superuser.csv",ios::out);
            {
                  while (true)
                  {
                        fp >> s;
                        if( fp.eof() )
                              break;
                        s=s+".csv";
                        fw.open(s.c_str(),ios::in);
                        fq<<s<<endl;
                        while (true)
                        {
                              fw>>e;  
                              if( fw.eof() )
                                    break;
                              fq<<e<<endl;
                        }
                        fq<<endl;
                        fw.close();
                  }
            }

            fp.close();
            fq.close();
      }
};

class MedicineShop 
{
      private:
            string name,ar,password,add,unique,dist;
      public:
            Admin ad;
            fstream fp,fq,fj;
            char Id[300],username[300];
            char pass[20],a;
            int u,i=0; 
            void addshop()
            {
                  
                  getline(cin,ar);

                  cout<<"Enter the Name of the Shop"<<endl;
                  getline(cin,name);
                  cout<<"Enter the District of the Shop"<<endl;
                  getline(cin,dist);
                  cout<<"Enter the Address of the shop"<<endl;
                  getline(cin,add);

                  while(1)
                  {
                        cout<<"Unique 4 digit Id of the shopkeeper"<<endl;
                        cin>>Id;
                        int i = ad.checkid(Id); 
                        if(i==1)
                              cout<<"Please Re-enter Id"<<endl;
                        else
                              break;
                  }
                  while(1)
                  {
                        cout<<"Create the Username of the Shop"<<endl;
                        cin>>username;
                        int i = ad.checkid(username);
                        if(i==1)
                              cout<<"Please Re-enter Username"<<endl; 
                        else
                              break;
                  }

                  cout<<"Create Password"<<endl;
                  a = getch();
                 
                  while(i<6)
                  {
                        pass[i]=getch();
                        cout<<'*';
                        i++;
                  }
                  cout << endl;
                  password.append(pass);

                  unique = Id + password;
            }

            void regshop()
            {
                  
                  fp.open("shop.csv",ios::out|ios::app);
                  fj.open("login.csv",ios::out|ios::app);
                  fq.open("super.csv",ios::out|ios::app);
                  {
                        fp<<Id<<','<<name<<','<<username<<','<<password<<endl;
                        fj<<unique<<endl;
                        fq<<username<<endl;
                  }
                  fp.close();
                  fq.close();
                  fj.close();
            }
          
            bool check()
            {
                  string s,s2,s3,s4;

                  char p[10];
                  cout<<"Enter the Medicine Shop Id"<<endl;
                  getline(cin,s4); 
                  getline(cin,s); 
                  


                  cout<<"Enter the Password"<<endl;
                  while(i<6)
                  {
                        p[i]=getch();
                        cout<<'*';
                        i++;
                  }

                  cout<<endl;
                  s2.append(p); 
                  s3=s+s2; 
                  char* y=new char[s3.length() + 1];
                  strcpy(y, s3.c_str());

                  if(ad.uni(y)) 
                  {
                        cout<<"Medical store found"<<endl;
                        return 1;
                  }
                  else
                  {
                        cout<<"Medical Store not found!"<<endl;
                        return 0;
                  }

                  delete[] y;
            }
};

class Admin
{
    static int c;

public:
      void pepi()  
      {
            string line1, line, line3, ar, dist;
            int l = 0;
            int pu;
            fstream fp, tp;
            tp.open("soldist.csv", ios::in); 
            while(!tp.eof())
            {
                l = 0;
                getline(tp, line1, ','); 
                dist = line1; 
                line1 += ".csv"; 
                fp.open(line1, ios::in);
                while(!fp.eof())
                {
                      getline(fp, line, ',');
                      stringstream geek(line);
                      

                      pu = 0;
                      geek >> pu;
                      if(pu>0)
                      {
                          if(pu>l)
                          {
                            l = pu; 
                            ar = line; 
                          }
                      }
                }
                fp.close();

                if(l>0)
                {
                      ifstream stream;
                      stream.open(line1, ios::in); 

                      while (getline(stream, line)) 
                      {
                            if (line.find(ar) != string::npos) 
                                 cout << "District Name  -" << dist << endl;
                                 cout << "The maximum sold medicine in the district is" << endl << line << endl;
                                 cout << "The disease corresponding to this medicine is likely to spread in the district" << endl;
                            }
                      }

                      stream.close();
                }

            }
      }

      void epidermic() 
      {
            fstream fp;
            char ch;
            string line, a, b, c;
            int choi;
            cout << "1.View specific district's sold Medicines " << endl << "2.Predict epidermic " << endl;
            cin >> choi;
            switch(choi)
            {
                  case 1:
                  {
                      cout << "Districts in which medicines are sold" << endl;
                      fp.open("soldist.csv", ios::in);
                      while(!fp.eof())
                      {
                           getline(fp, line, ',');
                           cout<<line;
                      }
                      fp.close();

                      do{
                           cout << "Enter the name of district to display its details" << endl;
                           cin >> a;
                           int che = check2(a);
                           a = (a + ".csv");
                           if(che == 1)
                           {
                                fp.open(a, ios::in);
                                cout << "Medicine" << " " << "Quantity" << endl;
                                while(!fp.eof())
                                {
                                      getline(fp,line,',');
                                      cout<<" "<<line;
                                }
                                fp.close();
                           }
                           else
                           {
                                cout<<"NO such district exist"<<endl;
                           }
                           cout<<"want to see more details Y or N"<<endl;
                           cin>>ch;


                      }while(ch=='y'|| ch=='Y');

                      break;
                  }

                  case 2:
                  {
                          Admin ob;
                          ob.pepi();
                  }
                  break;  
            }
      };

      int check2(string dist) 
      {
            ifstream stream;
            stream.open("soldist.csv",ios::in);
            string line;
            while (getline(stream, line))
            {
                  if (line.find(dist) != string::npos)
                  {
                        return 1;
                  }
            }
            return 0;
      }

      void admindist(string user,string searc,int q) // dist, name of medicine, quantity sell kri
      {
            user=user+".csv";
            int x,y,pu;
            fstream fp,tp,pt;
            string line,ser2,dist;
            if(c==0)
            {
                  fp.open(user,ios::app|ios::out);
                  fp<<"end of details of shop"<<','<<endl;
                  fp.close();
                  c++;
            }
            Admin ob1;
            int check = ob1.check(searc,user);
            if(check==0)
            {
                  ob1.changedist(user,searc,q);
            }
            else
            {
                  fp.open(user,ios::in|ios::out);
                  tp.open("temp.csv",ios::app|ios::out);
                  ser2 ="end of details of shop";
                  while(!fp.eof())
                  {
                        getline(fp,line,',');
                        tp<<line<<',';
                        if (line.find(searc) != string::npos||line.find(ser2) != string::npos)
                        {
                            break;
                        }
                  }
                  getline(fp,line,',');
                  int x = fp.tellg();
                  {
                        stringstream geek(line);
                        pu = 0;
                        geek >> pu;
                  }

                  q = (pu+q); 
                  ostringstream str1;
                  str1 << q<<',';
                  string geek = str1.str();
                  tp<<geek;
                  fp.seekp(x);
                  tp<<endl;
                  while(!fp.eof()){
                        getline(fp,line);
                        tp<<line<<endl;
                  }
                  fp.close();
                  tp.close();
                  char oldname[] ="temp.csv";
                  char newname[100] ;
                  strcpy(newname,user.c_str());
                  int result = remove(newname);
                  result = rename(oldname,newname);
            }
    }

    int checkmedicine(char token[]) 
    {
          ifstream stream;
          stream.open("shop.csv",ios::in);
          string line;
          while (getline(stream, line))
          {
                if (line.find(token) != string::npos)
                {
                      return 1;
                }
          }
          return 0;
    }

    int checkdistrict( char token[]) 
    {
          ifstream stream;
          stream.open("district.csv",ios::in);
          string line;
          while (getline(stream, line))
          {
                if (line.find(token) != string::npos)
                {
                      return 1;
                }
          }

          return 0;
    }

    int checkid(char token[]) 
    {
          ifstream stream;
          stream.open("shop.csv",ios::in);
          string line;
          while (getline(stream, line))
          {
                if (line.find(token) != string::npos)
                {
                      return 1;
                }
          }
          return 0;
    }

    int uni(char token[]) 
    {
          ifstream stream;
          stream.open("login.csv",ios::in);
          string line;
          while (getline(stream, line))
          {
                if (line.find(token) != string::npos)
                {
                     return 1;
                }
          }
          return 0;
    }

    int check(string s1,string s2)
    {
          ifstream stream;
          stream.open(s2.c_str(),ios::in);
          string line;
          while (getline(stream, line))
          {
                if (line.find(s1) != string::npos)
                {
                     return 1;
                }
          }
          return 0;

    }

    void changedist(string user,string ser2,int q)
    {
          fstream fp,tp;
          int count;
          string line,ser3;
          ser3 = "end of details of shop";
          fp.open(user,ios::in|ios::out);
          tp.open("u.csv",ios::app|ios::out);

          while(!fp.eof())
          {
                getline(fp,line,',');
                if (line.find(ser3) != string::npos)
                {
                      break;
                }
                tp<<','<<line<<',';
          }

          tp<<endl;
          tp<<ser2<<','<<q<<','<<endl; 
          tp<<line<<',';


          fp.close();
          tp.close();
          char oldname[] ="u.csv";
          char newname[100] ;
          strcpy(newname,user.c_str());
          int result = remove(newname);
          result = rename(oldname,newname);
    }


    void changefile(string user,string y )
    {
          

          fstream fp,tp;
          int count; 
          string name,ser2,line;
          ser2 = "end of details of shop";
          int q;
          fp.open(user,ios::in|ios::out);
          tp.open("u.csv",ios::app|ios::out);

          while(!fp.eof())
          {
                getline(fp,line,',');
                if (line.find(ser2) != string::npos)
                {
                      count = 1;
                      break;
                }
                tp<<line<<',';
          }
          tp<<endl;
          cout<<"enter the qanti"<<endl;
          cin>>q;
          cout<<"enter id"<<endl;
          int id;
          cin>>id;
          tp<<id<<','<<y<<','<<q<<','<<endl;
          tp<<line<<',';
          fp.close();
          tp.close();
          char oldname[] ="u.csv";
          char newname[100] ;
          strcpy(newname,user.c_str());
          int result = remove(newname);
          result = rename(oldname,newname);
    }
};
int Admin::c;

class Medicine
{
      private:
            string name,exp,number,a;
            int d,m,y;
      public:
            fstream fp;
            void create()
            {

                  

                  cout<<"Enter the Name of the Medicine "<<endl;
                  getline(cin,a); // What is this? :(
                  getline(cin,name);
                  cout<<"Enter the Medicine Id"<<endl;
                  getline(cin,number);
                  cout<<"Enter the expiry date of the medicine in the form dd/mm/yyyy"<<endl;
                  cin>>d;
                  while(1)
                  {
                        if ( cin.get() != '/' )
                              cout << "expected /\n";
                        else
                              break;
                  }
                  cin >> m;
                  while(1)
                  {
                        if ( cin.get() != '/' )
                              cout << "expected /\n";
                        else
                              break;
                  }
                  cin >> y;
                  
                  exp=to_string(d)+"/"+to_string(m)+"/"+to_string(y);
            }

            void writemedi()
            {
                  fp.open("MEDICINE.csv",ios::out|ios::app);
                  {
                        fp<<number<<','<<name<<','<<exp<<','<<endl;
      	          }
                  fp.close();
            }
            
            void disp()
            {
                  char s[50];
                  fp.open("MEDICINE.csv",ios::in);
                  {
                        while (true)
                        {
                              fp >> s;
                              if( fp.eof() )
                                    break;
                              cout<<s<<endl;
                        }
                  }
                  fp.close();
            }

            void addmedicine()
            {
                  

                  string user;
                  cout<<"Enter the username"<<endl;
                  getline(cin,a);
                  getline(cin,user);
                  user=user+".csv";
                  int x,y,q,pu;
                  fstream fp,tp,pt;
                  string line,searc,ser2,dist;
                  fp.open(user,ios::app|ios::out);
                  fp<<"End of details of shop"<<','<<endl;
                  fp.close();

                  cout<<"Enter the name of medicine"<<endl;
                  cin>>searc; 

                  Admin ob1;

                  int check = ob1.check(searc,user); 
                  if(check==0)
                  {
                        ob1.changefile(user,searc);
                  }
                  else
                  {
                        fp.open(user,ios::in|ios::out);
                        tp.open("SHOP.csv",ios::app|ios::out);
                        ser2 ="end of details of shop";
                        while(!fp.eof())
                        {
                               getline(fp,line,',');
                               tp<<line<<',';
                               // searc -> name of medicine
                               // ser2 -> end of details of shop
                               if (line.find(searc) != string::npos||line.find(ser2) != string::npos)
                                    break;
                        }
                        getline(fp,line,',');
                        x = fp.tellg(); // get postion in input sequence
                        cout<<line<<endl;

                        {
                              stringstream geek(line);
                              pu = 0;
                              geek >> pu;
                              cout << "Value of x : " << pu; 
                        }
                        cout<<"Enter the quantity of Medicine to be added"<<endl;
                        cin>>q;
                        y = pu+q;
                        ostringstream str1; 
                        str1 << y<<','; 
                        string geek = str1.str(); 
                        tp<<geek;

                        
                        fp.seekp(x);
                        
                        tp<<endl;
                        while(!fp.eof())
                        {
                              getline(fp,line);
                              tp<<line<<endl;
                        }
                        fp.close();
                        tp.close();
                        char oldname[] ="SHOP.csv";
                        char newname[100] ;

                        strcpy(newname,user.c_str());

                        // Inbuilt function, remove and rename
                        int result = remove(newname); 
                        result = rename(oldname,newname);
                  }
            }

            void delmedicine()
            {
                  string user,dist;
                  cout<<"enter the name of district in which medicine shop is located"<<endl;
                  cin>>dist; 
                  cout<<"Enter the username"<<endl;
                  getline(cin,a);
                  getline(cin,user); 
                  user=user+".csv";
                  int x,y,q,pu;
                  fstream fp,tp,pt,qt;
                  string line,searc,ser2;
                  fp.open(user,ios::in|ios::out);
                  tp.open("SHOP.csv",ios::app|ios::out);
                  cout<<"enter the name of medicine"<<endl;
                  cin>>searc;
                  Admin ob1;
                  int check = ob1.check(searc,user);
                  if(check==0)
                  {
                        cout<<"No medicine available"<<endl;
                  }
                  else
                  {
                        ser2 ="end of details of shop";
                        while(!fp.eof())
                        {
                              getline(fp,line,',');
                              tp<<line<<',';
                              if (line.find(searc) != string::npos||line.find(ser2) != string::npos)
                              {
                                   break;
                              }
                        }
                        getline(fp,line,',');
                        x = fp.tellg();
                        cout<<line<<endl;
                        {
                              stringstream geek(line);
                              pu = 0;
                              geek >> pu;
                              cout << "Value of x : " << pu<<endl;
                        }
                        while(1)
                        {
                              cout<<"Enter the quantity of Medicine to Sell"<<endl;
                              cin>>q;
                              if(q<pu)
                              {
                                    break;
                              }
                              if(q>pu)
                              {
                                    cout<<"That much quantity not available"<<endl;
                              }
                        }
                        ob1.admindist(dist,searc,q);
                        qt.open("soldist.csv", ios::app|ios::out); 
                        string d;int c;

                        c =ob1.check2(dist); 
                        if(c==0)
                        {
                              qt<<dist<<','<<endl;
                        }
                        qt.close();
                        y = pu-q;
                        ostringstream str1;
                        str1 << y<<',';
                        string geek = str1.str();
                        tp<<geek;
                        fp.seekp(x);
                        tp<<endl;
                        while(!fp.eof())
                        {
                              getline(fp,line);
                              tp<<line<<endl;
                        }
                        fp.close();
                        tp.close();
                        char oldname[] ="SHOP.csv";
                        char newname[100] ;
                        strcpy(newname,user.c_str());
                        int result = remove(newname);
                        result = rename(oldname,newname);
                  }
            } 
};


int main()
{
      int l, s=1, o, i, r=1;
      while(s!=0)
      {
            cout<<"1. Enter as Medical Store Owner"<<endl<<"2. Enter as Admin "<<endl<<"3. Enter as a Superuser"<<endl<<"4. Exit"<<endl;
            cin>>l;
            switch(l) 
            {
                  case 1:
                  {
                        cout<<"1. Register as a New User"<<endl<<"2. Log-in as a Registered User "<<endl<<"3. Go to the Previous Menu"<<endl;
                        cin>>o;
                        switch(o)
                        {
                              case 1:
                              {
                                    MedicineShop *m=new MedicineShop();
                                    m->addshop();
                                    m->regshop();
                                    delete m;
                                    break;
                              }
                              case 2:
                              {
                                    MedicineShop *t=new MedicineShop();
                                    if(t->check())
                                    {
                                          while(r!=0)
                                          {
                                                cout<<"1. Enter a new medicine "<<endl<<"2. Enter stock into the shop"<<endl<<"3. Sell Medicine"<<endl<<"4. Go to previous menu"<<endl;
                                                cin>>i;
                                                switch(i)
                                                {
                                                      case 1:
                                                      {
                                                            Medicine *q=new Medicine();
                                                            q->create();
                                                            q->writemedi();
                                                            delete q;
                                                            break;
                                                      }
                                                      case 2:
                                                      {
                                                            Medicine *p=new Medicine();
                                                            p->disp();
                                                            p->addmedicine();
                                                            delete p;
                                                            break;
                                                      }
                                                      case 3:
                                                      {
                                                            Medicine *r = new Medicine();
                                                            r->delmedicine();
                                                            delete r;
                                                            break;
                                                      }
                                                      case 4:
                                                      {
                                                            r=0;
                                                            break;
                                                      }
                                                      default:
                                                      {
                                                            cout<<"Invalid input try again "<<endl;
                                                      }
                                                }
                                          }
                                    } 
                                    delete t;
                                    break;
                              }
                        }
                        break;
                  }
                  case 2:
                  {
                        cout<<"1.Enter a New District"<<endl<<"2.Epidemic Status"<<endl;
                        int choice;
                        cin>>choice;
                        switch(choice)
                        {
                              case 1:
                              {
                                    District *dp=new District();
                                    dp->adddist();
                                    delete dp;
                                    break;
                              }
                              case 2:
                              {
                                    Admin *d=new Admin();
                                    d->epidermic();
                                    delete d;
                                    break;
                              }
                        }
                        break;
                  }

                  case 3:
                  {
                        District *d=new District();
                        d->super();
                        delete d;
                        break;
                  }
                  case 4:
                  {
                        s=0;
                        break;
                  }
            }
      }

      return 0;
}
