#include <iostream> //header file for input and output stream
#include <cstdlib> // C standard library
#include <vector> // header file for using vector
#include <cmath> // header file for using pow
using namespace std;
const double N = 1e-9; // Defining the value as const;
/*user defined data type struct is defined for a polynomial
 it has two variable one is (int)n(for degree) and another is vector(for storing coefficients)
*/
struct polyn{
    int n;
    vector<double> vec = vector<double> (); /*initialization of vector as vector<double>() --> it is of no use but to be in safe side vector is inialized whenever object of struct is created */
};
vector<struct polyn*> polynomials;    /*A vector for storing all the defined polynomials it is declared globally so that it is acesseable to all the function without passing it as argument*/
/*Print_polly takes vector as a argument which represt coefficent of any polynomials */
void print_polly(vector<double> vec){
    for(int j=0;j<vec.size();j++){
        if(j==0){
            if(vec[0]!=0)cout<<vec[0];continue;
        }
        if(vec[j]!=0){
            if(j==1 && vec[0]==0){
                cout<<vec[j]<<"x^"<<j;
                continue;
            }
            if(j!=vec.size()-1){
                cout<<" +";
                cout<<vec[j]<<"x^"<<j;
                // if(vec[j+1]!=0);
            }
            else cout<<" +"<<vec[j]<<"x^"<<j;
        }

    }
    cout<<endl;
}
/*create_poly() for allocation of memory for creating new polynomials*/
void create_poly(){
    double ele=0;
    int deg;
    int degi;
    cout<<"Enter the degree of polynomials :"<<endl;  /*Taking degree and coefficient as a input from user*/
    cin>>degi;
    struct polyn* a = new struct polyn;     /*used new for allocating dynamic memory idk why malloc was giving error for some particular cases(like if we are creating the second polynomials just after the creation of first polynomial it sometimes gives sigmentation fault  :( */
    cout<<"Enter the coefficients of polynomials with space seprated :"<<endl;
    for(int i=0;i<= degi;i++){
        cin>>ele;
        a->vec.push_back(ele);
        ele =0;
        if(a->vec[i] !=0){
            deg = i;
        }
    }
      a->n = deg;
    polynomials.push_back(a);
    cout<<"The created polynomial is : ";
    print_polly(a->vec);
    cout<<endl;
}
/*addremove it is overloaded function for adding or removing terms in polynomials*/

void addremove(int i,int deg,double c){
    if(deg<0){                              /*if the power of term entered is less than zero*/
        cout<<"Wrong input power of terms in polynomial should be positive: :( ERROR"<<endl;
        return;
    }
    if(deg > polynomials[i]->n){           /*for the power of term which is greater than degree of polynomial*/
       for(int j=(polynomials[i]->n)+1 ;j<deg ;j++){
          
           polynomials[i]->vec.push_back(0);
       }
       polynomials[i]->n = deg;
       polynomials[i]->vec.push_back(c);
    }else{
    polynomials[i]->vec[deg] = c;   /*if the power is less than degree*/
    }
    cout<<"Polynomial formed after adding term is :";
    print_polly(polynomials[i]->vec);       /*Printing the resultant polynomial*/
    cout<<endl;
        return;
}
/*overloading a function and using it for removing term */
void addremove(int i,int deg){
    if(deg<0){
        cout<<"Wrong input power of terms in polynomial should be positive: :( ERROR"<<endl<<endl; 
        return;
    }
    if(deg > polynomials[i]->n){        /*if the power is more than the degree*/
        cout<<"The power is greater than the degree of polynomial: :( ERROR"<<endl<<endl;
        return;
    }
    if(polynomials[i]->vec[deg] == 0){      /*The coefficient of that polynomial is made zero*/
        cout<<"The coefficent of this term is already zero "<<endl<<endl;
        return;
    }
    polynomials[i]->vec[deg] = 0;
    cout<<"Polynomial formed after Removing term is :";     /*Printing the formed polynomial*/
    print_polly(polynomials[i]->vec);
    cout<<endl;
}
/*overloading the function for removing terms whose coefficient are lsess than epsilon*/
void addremove(int i,int b,int c,int eps=N){    /*passing the defalut value N(1e-9) as a argument of eps*/
    int size = polynomials[i]->vec.size();
    for(int j=0;j<size;j++){
        if(abs(polynomials[i]->vec[j]) < eps){  /*tracing and checking and making the coefficients zero who are less than eps*/
            polynomials[i]->vec[j] = 0;
        }
    }
    cout<<"Polynomial formed after Removing term whose coefficients is lesser than epsilon("<<eps<<") :";
    print_polly(polynomials[i]->vec);           /*Printing the polynomial*/
    cout<<endl;
}
/*Funcion for evaluating the value of polynomial for any x */
double evaluate(int i,double a){ /*Takes the index of polynomial and value of x as arguemnt*/
    // cout<<a<<endl;
    if(i>polynomials.size())cout<<"The index entered is invalid :( "<<endl; return 0;      /*Checking if index entered is correct or not*/
    double val=0;
    for(int j=0;j<polynomials[i]->vec.size();j++){
        double z = (double)polynomials[i]->vec[j];      /*Using pow function to evaluate the value */
        val += (z)*pow(a,j);
    }
    return val;             /*Returning the evaluated value*/

}
/*Function for adding Two polynomial*/
void addpoly(int i,int j){
    if(i<0 || i >=polynomials.size() || j<0 || j>=polynomials.size()){    /*Checking if the index entered is correct or not*/ 
        cout<<"Wrong Polynomial index entered : :( ERROR"<<endl;
        return;
    }else{       /*Running the loop for max(degree of poly1,degree of poly2)*/
        int mx=max(polynomials[i]->n ,polynomials[j]->n);
        vector<double> v(mx+1,0);
        int degree =0;
        for(int k=0;k<polynomials[i]->vec.size() || k < polynomials[j]->vec.size() ; k++){
            if(k>= polynomials[i]->vec.size()){
                v[k]=polynomials[j]->vec[k];            /*condition if we had traced all the terms of poly1*/
            }
            else if(k >= polynomials[j]->vec.size()){
                v[k] = polynomials[i]->vec[k];          /*condition if we had traced all the terms of poly1*/
            }else{
                v[k] = polynomials[j]->vec[k] + polynomials[i]->vec[k]; /*condition when all the terms of both are not traced*/
            }
            if(v[k]!=0){
                degree = k;         /*Updating the degree of polynomial if the coefficient is not zero*/
            }
        }
        /*Asking user want to stor the summed polynomial or not*/
        cout<<"Do u want to Store the resulantant polynomial into list of polynomials(Press 1) or Just want to see the result(Press 2) "<<endl;
        int des;
        cin>>des;
        if(des == 1){
         struct polyn* a = new struct polyn;    /*if user wants to store polynomial then allocation dynamic memory and assigning value to n and vec and then pushing the formed polynomial(a) into the list of polynomials*/
       
         a->n = degree;
         a->vec = v;
         polynomials.push_back(a);
         cout<<"The polynomial is stored :)"<<endl;
        }
        cout<<"The summed polynomial is"<<" ";  /*Printing the summed polynomial*/
        print_polly(v);
        cout<<endl;
        v.clear();
    }
}
/*Defing the derivative function for calculating derrivative and storing it*/
void derivative(int in,int def=0){          /*Passed the defalut argument def so that it can be used by zero-newton function and doesn't print anything while computing derivative */
    vector<double> v;
    for(int i=0;i<polynomials[in]->vec.size()-1;i++){
         v.push_back(polynomials[in]->vec[i+1]*(i+1)) ;/*Storing the coefficinet of differentiated polynomial*/
    }
    if(def==1){         /*For every call made by zero-newton function def is changed to 1 since this part will run and nothing will be printed form stream*/
        int degree = polynomials[in]->n;
        struct polyn* a = new struct polyn;
        a->n = degree -1;
        a->vec = v;
        polynomials.push_back(a);
        return;
    }
    /*The rest of code will run when we want to derivate a paticular problem using interface*/
    cout<<"Do u want to Store the resulantant polynomial into list of polynomials(Press 1) or Just want to see the result(Press 2) "<<endl;
        int des;
        cin>>des;
        if(des==1 || def==1){
            int degree = polynomials[in]->n;        /*Allocating memory assigning n and vec and pushing it into the polynomials list*/
            struct polyn* a = new struct polyn;
            a->n = degree -1;
            a->vec = v;
            polynomials.push_back(a);
            
            cout<<"The Derivative is stored succesfully :) "<<endl;
            
        }
    cout<<"The derivative of polynomial is ::";     /*Printing the polynomials*/
    print_polly(v);
    cout<<endl;
}
/*Zero-newton funciton for calculating root of polynomial*/
void zero_newton(int in,double x0 =0,double ep = N){
    
    derivative(in,1);       /*Finding the derivative of polynomial and storing it into last before ending of the function this temporary derivative will be popped out*/
    int l = polynomials.size();
    while(evaluate(l-1,x0) == 0){   /*if the value of f' is zero at x0,then it will take another value for x0 where f' is zero*/
        x0++;
    }
    double y = evaluate(in,x0);     /*Evaluating f(x0) for x0 */
    double x;
    int count=0;
    while(abs(y) > ep && count<90){
        x = evaluate(l-1,x0);
        y = evaluate(in,x0);        /*Evaluating the f'(x0)*/
        x0 -= (y/x);                /*Updating x0 as x0 - f(x0)/f'(x0)*/
        count++;                    /*if the polynomial doesn't have root it will iterate infinitly so a count parameter which will stop the iteration after 90*/
    }
    polynomials.pop_back();         /*popping back the differentiated polynomial*/
    if(count==90){                  /*if the count reaches 90*/
        cout<<"Sorry !! The root of polynomial doesn't exist :("<<endl;
        return;
    }
    cout<<"Value of x for which f(x)=0 is :"<<x0<<endl;     /*Printing the root*/
}
/*Funciton for Deleting the polynomial*/
void delpoly(int in){
    if(in >= polynomials.size()){           /*Checking for the correct index if index entered is less then the polynomial size*/
        cout<<"Wrong index entered : No polynomial exist at this index : :("<<endl;
        return;
    }
    polynomials[in] = polynomials[polynomials.size()-1]; /*Replacing the polynomial with the last polynomial */
    polynomials.pop_back();     /*Popping out the last polynomial*/
    cout<<"Polynomial is Deleted Sucessfully :) "<<endl;
}

int main(){
    int a=0;
    while(a!= -1){
        cout<<"1. Create a polynomial"<<endl;
        cout<<"2. To Add or Remove "<<endl;
        cout<<"3. To Evaluate the value of Polynomial"<<endl;
        cout<<"4. To Add Two Polynomials"<<endl;
        cout<<"5. To Differentiate the Polynomial"<<endl;
        cout<<"6. To Find the Root of Polynomial"<<endl;
        cout<<"7. To delete any polynomial from List"<<endl;
        cout<<"8. To display all the polynomials in List"<<endl;
        cout<<"To exit press -1"<<endl;
        
        cin>>a;
        if(a==1){
            create_poly();
        }
        if(a==2){
            if(polynomials.size()==0){
                cout<<"No polynomial in a List :( "<<endl<<endl;       
                continue;
            }
            int b;                                              /*Defing b so that user can choose what to do*/
            cout<<"Choose a Polynomial to Add Remove"<<endl;
            int z=0;         /*Printing the list so that user can chose operation on polynomial*/
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";                        
                print_polly(polynomials[i]->vec);
                
            }
            cin>>z;
             cout<<"To Add Term Press 1"<<endl;
            cout<<"To Remove Term Press 2"<<endl;
            cout<<"To Remove all Terms whose coefficients are smaller than EPSILON press 3"<<endl;
            cin>>b;
            if(b==1){       /*call of first addremove for adding term*/
                cout<<"Enter the Power and Coefficents of term you want to Add :"<<endl;
                int d;
                double c;
                cin>>d;
                cin>>c;
                addremove(z-1,d,c);
            }else if(b==2){     /*Program for removing the term in polynomial*/
                cout<<"Enter the power of term to remove"<<endl;
                int d;
                cin>>d;
                addremove(z-1,d);
            }else if(b==3){
                cout<<"Do u want to Enter the value of epsilon (Press 1) or pass its default value(Press 2)"<<endl;
                int ch;
                cin>>ch;
                if(ch==1){
                cout<<"Enter the epsilon value"<<endl;
                double eps;
                cin>>eps;
                addremove(z-1,0,0,eps);
                }else{
                    addremove(z-1,0,0);
                }
            }

        }
        if(a==3){
            cout<<"Choose a polynomial to evaluate"<<endl;
            int z=0;                                /*Printing the list so that user can chose operation on polynomial*/
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";
                print_polly(polynomials[i]->vec);
            }
            cin>>z;             /*Taking the value of polynomial index from user*/
            cout<<"Enter the value of x"<<endl;
            double x;           /*Taking value of x from user*/
            cin>>x;
            double val = evaluate(z-1,x);
            cout<<"Evaluated value of f(x) for x="<<x<<" is :"<<val<<endl;
        }
        if(a==4){
            cout<<"Choose two polynomials to add"<<endl;    /*Printing the list so that user can chose operation on polynomial*/
            int z,y;
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";
                print_polly(polynomials[i]->vec);
            }               /*Taking index of two polynomial form user and passing it in addpoly function*/
            cin>>z>>y;
            addpoly(z-1,y-1);
        }
        if(a==5){
            cout<<"Choose the polynomial to differntiate"<<endl;        /*Printing the list so that user can chose operation on polynomial*/
            int z;
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";
                print_polly(polynomials[i]->vec);
            }       /*Taking index from user and pasing it into derivative function*/
            cin>>z;
            derivative(z-1);
            polynomials.pop_back();
        }
        if(a==6){
            cout<<"Choose the polynomial for finding the root"<<endl;   /*Printing the list so that user can chose operation on polynomial*/
            int z;
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";
                print_polly(polynomials[i]->vec);
            }           /*Passing the index of polynomial into zero-newton*/
            cin>>z;
            zero_newton(z-1,0);
            
        }if(a==7){
            if(polynomials.size()==0){
                cout<<"Sorry !! No POlynomial in a List currently :("<<endl;
                continue;
            }           /*Printing the list so that user can chose operation on polynomial*/
             cout<<"Choose the polynomial which u  want to delete"<<endl;
             int z;
            for(int i=0;i<polynomials.size();i++){
                cout<<i+1<<". ";
                print_polly(polynomials[i]->vec);
            }               /*Taking inde of polynomial and passing it into delpoly function*/
            cin>>z;
            delpoly(z-1);
        }
        if(a==8){
            cout<<"The list of polynomials are :"<<endl;
            for(int i=0;i<polynomials.size();i++){      /*Printing the list so that user can chose operation on polynomial*/
                cout<<i+1<<".: ";
                print_polly(polynomials[i]->vec);
            }
            cout<<endl;
        }
    }
    return 0;
}
/*I used vector instead of creating a user defined type list because it is easy to find an element in vector for vector it is O(1) while for list it is O(n) so for every type when we want to do operation of we have to get the polynomial and with vector it is possible in O(1) time while while list O(n) time. There is only one thing where we have edge using list is that in list deletion is more easy we have to just connect the prev and next polynomial and free the polynomial which we want to delete. So for this operation i used vector and if want to delete any polynomial let its index be x so it replaced the last polynomial with that polynomial and pop_back tha last possible in this process we still have a list of polynomials and we did the operation in O(1) complexity */