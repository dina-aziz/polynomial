#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<math.h>
using namespace std;


struct term
{
	double coef;
	int power;
	term *next;
};

class polynomial
{
private:
	term * head;
public:
	polynomial()
	{
		head=NULL;
	}
	polynomial(polynomial &p)
	{
		term *ptr2=p.head;
		term *ptr1=head;
		int a=0;
		while(ptr2!=NULL)
		{
			if(ptr1==head && a!=1)
			{
				term *t=new term;
			    t->coef=ptr2->coef;
			    t->power=ptr2->power;
				t->next=NULL;
				head=t;
				ptr1=t;
				ptr2=ptr2->next;
				a++;
			}
			else
			{
				term *t=new term;
			    t->coef=ptr2->coef;
			    t->power=ptr2->power;
				t->next=NULL;
			    ptr1->next=t;
			    ptr1=ptr1->next;
			    ptr2=ptr2->next;
		    }
		}
	}


    double PolyVal(double n)
	{
		term * p=head;
		double val=0;
		while(p!=NULL)
		{
			val+=(p->coef)*pow(n,p->power);
			p=p->next;
		}
		return val;
	}
	void RemoveTerm(int n)
	{
		term *prev=head;
		term *ptr=head;
		while(ptr!=NULL)
		{
			if(ptr->power==n && ptr==head)
			{
				head=head->next;
				delete ptr;
				break;
			}
			else if(ptr->power==n && ptr!=head)
			{
				term *t=ptr;
				ptr=ptr->next;
				prev->next=ptr;
				delete t;
				break;
			}
			else
				prev=ptr;
			    ptr=ptr->next;
		}
	}
    void AddTerm(double c,int p)
	{
		term *ptr1=head;
		term *prev=head;
		term *t=NULL;
	    if(head==NULL)
	    {
			t=new term;
			t->coef=c;
		    t->power=p;
		    t->next=NULL;
	        head=t;
	    }
		else while(ptr1!=NULL)
		{
			t=new term;
			t->coef=c;
			t->power=p;
			t->next=NULL;
			if(ptr1->power < t->power && prev!=head)
			{
				t->next=ptr1;
				prev->next=t;
				break;
			}
			if(ptr1->power < t->power && prev==head)
			{
				t->next=ptr1;
				head=t;
				break;
			}
			else if(ptr1->power ==  t->power)
			{
				ptr1->coef+=t->coef;
				delete t;
				break;
			}
			else if(ptr1->power > t->power)
			{
				if(ptr1->next!=NULL)
			    {
					prev=ptr1;
					ptr1=ptr1->next;
				    continue;
				}
				else
				{
					t->next=NULL;
					ptr1->next=t;
					break;
				}
		    }
		}
	     ptr1=head;
	     while(ptr1!=NULL)
	     {
			 if(ptr1->coef==0 &&ptr1==head)
			 {
				 term *p=ptr1;
				 head=head->next;
				 delete p;
				 ptr1=head;
				 continue;
			 }
			 else if(ptr1->coef!=0)
			{
				ptr1=ptr1->next;
				continue;
		    }
			 else if(ptr1->coef==0 && ptr1!=head)
			 {
				 term *p=head;
				 while(p->next->coef!=0)
					 p=p->next;
				 p->next=ptr1->next;
				 ptr1=ptr1->next;
				 p=p->next;
				 delete p;
			 }
	    }
    }
	polynomial & MulTerm(double c,int p)
	{
		polynomial *poly=new polynomial(*this);
		term *ptr=poly->head;
		while(ptr!=NULL)
		{
			(ptr->coef)*=c;
			(ptr->power)+=p;
			ptr=ptr->next;
		}
		return *poly;
	}
	int HeighestExponent()
	{
		return head->power;
	}
	int LowestExponent()
	{
		term *p=head;
		while(p->next!=NULL)
			p=p->next;
		return p->power;
	}
	void Print()
	{
		string sp="  ";
		char sign='+';
		string ex ="X^";
		term *p=head;
		while(p!=NULL)
		{
			if(p==head && p->power!=0)
                cout<<p->coef<<ex<<p->power<<sp;
			else if(p!=head && p->coef >0 && p->power!=0 )
				cout<<sign<<sp<<p->coef<<ex<<p->power<<sp;
			else if(p!=head && p->coef<0 && p->power!=0)
			    cout<<p->coef<<ex<<p->power<<sp;
			else if(p==head && p->power==0)
                cout<<p->coef<<sp;
			else if(p!=head && p->power==0 && p->coef>0)
                cout<<sign<<sp<<p->coef<<sp;
			else if(p!=head && p->power==0 &&p->coef<0)
                cout<<p->coef<<sp;
			else if(p!=head && p->coef >0 && p->power!=0 )
				cout<<sign<<sp<<p->coef<<sp;
			else if(p!=head && p->coef<0 && p->power!=0)
			    cout<<p->coef<<sp;

			p=p->next;
		}
		cout<<endl;
	}
	void Coefficient(int p)
	{
		int f=0;
		term *ptr=head;
		while(ptr!=NULL)
		{
			if(ptr->power==p)
			{
				f=1;
				cout<<endl<<ptr->coef;
				ptr=ptr->next;
			}
			else ptr=ptr->next;
		}
		if(f==0) cout<<0<<endl;

	}
	polynomial & Integral()
	{
		polynomial *poly=new polynomial;
		term *p=head;
		term *pp=NULL;
		while(p!=NULL )
		{
			term *t=new term;
			t->power=p->power+1;
			t->coef=p->coef/(p->power+1);
			t->next=NULL;
			if(pp==NULL)
			{
				poly->head=t;
				pp=poly->head;
			}
			else
		    {
			   pp->next=t;
			   pp=pp->next;
			}
			if(poly->head==NULL)
		    {
			    term *t=new term;
			    t->coef=0;
			    t->power=0;
			    t->next=NULL;
			    poly->head=t;
		    }
			p=p->next;
		}
		return *poly;
    }
	polynomial & Differentiate()
	{
		polynomial *poly=new polynomial;
		term *p=head;
		term *pp=NULL;
		while(p!=NULL && p->power!=0)
		{
			term *t=new term;
			t->power=(p->power)-1;
			t->coef=(p->coef)*(p->power);
			t->next=NULL;
			if(pp==NULL)
			{
				poly->head=t;
				pp=poly->head;
			}
			else
		    {
			   pp->next=t;
			   pp=pp->next;
			}
			p=p->next;
		}
		if(poly->head==NULL)
		{
			term *t=new term;
			t->coef=0;
			t->power=0;
			t->next=NULL;
			poly->head=t;
		}
		return *poly;
    }
	int Terms()
	{
		int count=0;
		term *p=head;
		while(p!=NULL)
		{
			count ++;
			p=p->next;
		}
		return count;
	}
    int* Exponents()
	{
		int k=this->Terms();
		int *arr=new int[k];
		term *p=head;
		for(int j=0;j<k;j++)
		{
			arr[j]=p->power;
			p=p->next;

		}
		return arr;
	}
	string ToString()
	{
		string poly="";
		term *p=head;
		string ex="^X";
		string pos="+";
		char arr[20];
		while(p!=NULL)
		{
           sprintf(arr,"%f",p->coef);
		    string cc=arr;
		    poly+=cc;
			poly+=ex;
			sprintf(arr,"%i",p->power);
			string pp=arr;
			poly+=pp;
			if(p->next!=NULL &&p->next->coef>=0)
				poly+=pos;
			p=p->next;
	    }
		return poly;
	}

	bool operator == (polynomial &p)
	{
		term *ptr1=head;
		term *ptr2=p.head;
		while(ptr1!=NULL && ptr2!=NULL) 
		{
			if(ptr1->coef==0)
			{
				ptr1=ptr1->next;
				continue;
			}   // skip zero coefficient terms in ptr1
			if(ptr2->coef==0)
			{
				ptr2=ptr2->next;
				continue;
			}  // skip zero coefficient terms in ptr2
			if(ptr1->power!=ptr2->power ||ptr1->coef!=ptr2->coef)
				return 0;
			ptr1=ptr1->next;
			ptr2=ptr2->next;
		}
		while(ptr1&&ptr1->coef==0)
		{
			ptr1=ptr1->next;
		}  // skip zero coefficient terms in ptr1 in the end of polynomial
		while(ptr2&&ptr2->coef==0)
		{
			ptr2=ptr2->next;
		}   // skip zero coefficient terms in ptr2 in the end of polynomial
		if(ptr1==ptr2)
			return 1;
		else
			return 0;
	}
	bool operator != (polynomial &p)
	{
		return !(*this==p);
	}
	polynomial &  operator + (polynomial &p)
	{
		polynomial *poly=new polynomial;
		term * p1=head;
		term * p2=p.head;
		term *p3=NULL;
		term *t=NULL;
		while(!(p1==NULL && p2==NULL))
		{
			if(((p1!=NULL && p2==NULL)||(p1!=NULL && p2!=NULL && p1->power > p2->power))&&p3==NULL)
		    {
			    t=new term;
			    t->coef=p1->coef;
			    t->power=p1->power;
			    t->next=NULL;
				poly->head=t;
			    p1=p1->next;
		    	p3=poly->head;
		    }
			if(((p1!=NULL && p2==NULL)||(p1!=NULL && p2!=NULL && p1->power > p2->power))&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=p1->coef;
			    t->power=p1->power;
			    t->next=NULL;
				p3->next=t;
			    p1=p1->next;
				p3=p3->next;
		    }
		    else if(((p1==NULL && p2!=NULL)||(p1!=NULL && p2!=NULL && p2->power > p1->power))&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=p2->coef;
			    t->power=p2->power;
			    t->next=NULL;
				p3->next=t;
			    p2=p2->next;
			    p3=p3->next;
		    }
			 else if(((p1==NULL && p2!=NULL)||(p1!=NULL && p2!=NULL && p2->power > p1->power))&&p3==NULL)
		    {
			    t=new term;
			    t->coef=p2->coef;
			    t->power=p2->power;
			    t->next=NULL;
				poly->head=t;
			    p2=p2->next;
			    p3=poly->head;
		    }
		    else if((p1->power==p2->power)&&p3==NULL)
		    {
			    t=new term;
			    t->coef=p1->coef+p2->coef;
			    t->power=p1->power;
			    t->next=NULL;
				poly->head=t;
			    p1=p1->next;
			    p2=p2->next;
				p3=poly->head;
		    }
			 else if((p1->power==p2->power)&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=p1->coef+p2->coef;
			    t->power=p1->power;
			    t->next=NULL;
				p3->next=t;
			    p1=p1->next;
			    p2=p2->next;
			    p3=p3->next;
		    }
		}
		return *poly;
	}
	polynomial &  operator - (polynomial &p)
	{
		polynomial *poly=new polynomial;
		term * p1=head;
		term * p2=p.head;
		term *p3=NULL;
		term *t=NULL;
		while(!(p1==NULL && p2==NULL))
		{
			if(((p1!=NULL && p2==NULL)||(p1!=NULL && p2!=NULL && p1->power > p2->power))&&p3==NULL)
		    {
			    t=new term;
			    t->coef=p1->coef;
			    t->power=p1->power;
			    t->next=NULL;
				poly->head=t;
			    p1=p1->next;
		    	p3=poly->head;
		    }
			if(((p1!=NULL && p2==NULL)||(p1!=NULL && p2!=NULL && p1->power > p2->power))&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=p1->coef;
			    t->power=p1->power;
			    t->next=NULL;
				p3->next=t;
			    p1=p1->next;
				p3=p3->next;
		    }
		    else if(((p1==NULL && p2!=NULL)||(p1!=NULL && p2!=NULL && p2->power > p1->power))&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=-1*(p2->coef);
			    t->power=p2->power;
			    t->next=NULL;
				p3->next=t;
			    p2=p2->next;
			    p3=p3->next;
		    }
			 else if(((p1==NULL && p2!=NULL)||(p1!=NULL && p2!=NULL && p2->power > p1->power))&&p3==NULL)
		    {
			    t=new term;
			    t->coef=-1*(p2->coef);
			    t->power=p2->power;
			    t->next=NULL;
				poly->head=t;
			    p2=p2->next;
			    p3=poly->head;
		    }
		    else if((p1->power==p2->power)&&p3==NULL)
		    {
			    t=new term;
			    t->coef=p1->coef-p2->coef;
			    t->power=p1->power;
			    t->next=NULL;
				poly->head=t;
			    p1=p1->next;
			    p2=p2->next;
				p3=poly->head;
		    }
			 else if((p1->power==p2->power)&&p3!=NULL)
		    {
			    t=new term;
			    t->coef=p1->coef-p2->coef;
			    t->power=p1->power;
			    t->next=NULL;
				p3->next=t;
			    p1=p1->next;
			    p2=p2->next;
			    p3=p3->next;
		    }
		}
		return *poly;
	}
	polynomial & operator * (polynomial &p)
	{
		polynomial *poly=new polynomial;
		polynomial *temp=new polynomial;
		term * ptr=p.head;
		while(ptr!=NULL)
		{
			*temp=MulTerm(ptr->coef,ptr->power);
			ptr=ptr->next;
			*poly=*poly+*temp;
		}
		return *poly;
	}
	polynomial & operator / (polynomial &p)
	{
		polynomial *poly = new polynomial;
		polynomial *temp = new polynomial;
		polynomial *tt = new polynomial(*this);
		term *p1=head;
		term *p2=p.head;
		term *p3=NULL;
		if(head==NULL)
		{
			term *t=new term;
			t->coef=0;
			t->power=0;
			t->next=NULL;
			poly->head=t;
		}
		else if(p.head==NULL)
		{
			cout<<"\nILLEGAL OPERATION !!";
			term *t=new term;
			t->coef=0;
			t->power=0;
			t->next=NULL;
			poly->head=t;
		}
		else while(!(p1==NULL || p2==NULL) && p1->power > p2->power)
		{
			term *t=new term;
			if (poly->head==NULL)
			{
			    t->coef=p1->coef/p2->coef;
			    t->power=p1->power-p2->power;
			    t->next=NULL;
			    poly->head=t;
				p3=poly->head;
			}
			else
			{
			    t->coef=p1->coef/p2->coef;
			    t->power=p1->power-p2->power;
			    t->next=NULL;
				p3->next=t;
				p3=p3->next;
			}

			*temp=p.MulTerm(t->coef,t->power);
			*tt=*tt-*temp;
            p1=tt->head;
	        while(p1!=NULL&&p1->coef==0)
	       /* {
		         term * pp=tt->head;
		         tt->head=tt->head->next;
                 delete pp;
		         p1=tt->head;
	        }*/
		    while(p1!=NULL)
	        {
			    if(p1->coef==0 &&p1==tt->head)
			    {
				    term *p=p1;
				    tt->head=tt->head->next;
				    delete p;
				    p1=tt->head;
				    continue;
			    }
			    else if(p1->coef!=0)
			   {
				   p1=p1->next;
				   continue;
		       }
			   else if(p1->coef==0 && p1!=tt->head)
			   {
			       term *p=head;
				   while(p->next->coef!=0)
				       p=p->next;
				   p->next=p1->next;
			       p1=p1->next;
				   p=p->next;
			       delete p;
			   }
	        }
	        p1=tt->head;
	    }
		return *poly;
	}
    polynomial & operator % (polynomial &p)
	{
		polynomial *poly = new polynomial;
		polynomial *temp = new polynomial;
		polynomial *tt = new polynomial(*this);
		term *p1=head;
		term *p2=p.head;
		term *p3=NULL;
		if(head==NULL)
		{
			term *t=new term;
			t->coef=0;
			t->power=0;
			t->next=NULL;
			poly->head=t;
		}
		else if(p.head==NULL)
		{
			cout<<"\nILLEGAL OPERATION !!";
			term *t=new term;
			t->coef=0;
			t->power=0;
			t->next=NULL;
			poly->head=t;
		}
		else while(!(p1==NULL || p2==NULL) && p1->power > p2->power)
		{
			term *t=new term;
			if (poly->head==NULL)
			{
			    t->coef=p1->coef/p2->coef;
			    t->power=p1->power-p2->power;
			    t->next=NULL;
			    poly->head=t;
				p3=poly->head;
			}
			else
			{
			    t->coef=p1->coef/p2->coef;
			    t->power=p1->power-p2->power;
			    t->next=NULL;
				p3->next=t;
				p3=p3->next;
			}

			*temp=p.MulTerm(t->coef,t->power);
			*tt=*tt-*temp;
            p1=tt->head;
	        while(p1!=NULL&&p1->coef==0)
	        /*{
		         term * pp=tt->head;
		         tt->head=tt->head->next;
                 delete pp;
		         p1=tt->head;
	        }*/
		    while(p1!=NULL)
	        {
			    if(p1->coef==0 &&p1==tt->head)
			    {
				    term *p=p1;
				    tt->head=tt->head->next;
				    delete p;
				    p1=tt->head;
				    continue;
			    }
			    else if(p1->coef!=0)
			   {
				   p1=p1->next;
				   continue;
		       }
			   else if(p1->coef==0 && p1!=tt->head)
			   {
			       term *p=head;
				   while(p->next->coef!=0)
				       p=p->next;
				   p->next=p1->next;
			       p1=p1->next;
				   p=p->next;
			       delete p;
			   }
	        }
	        p1=tt->head;
	    }
		return *tt;
	}

};

int main()
{
	cout<<endl<<endl;
	polynomial p1;
	p1.AddTerm(2,7);                        //AddTerm is OK !!
	p1.AddTerm(1,6);
	p1.AddTerm(6,4);
	p1.AddTerm(3,3);
	cout<<"\np1      = ";p1.Print();        //print is OK !!
	polynomial p2;
	p2.AddTerm(3,2);
	p2.AddTerm(-1,1);
	cout<<"\np2      = ";p2.Print();
	polynomial p3=p1;                      //the copy constructor is OK !!
	cout<<"\np3      = ";p3.Print();       //operators (+,-,*,/) are OK  !!
	p3=p1*p2;
	cout<<"\np1 * p2 = ";p3.Print();       //MulTerm is OK !!
    p1=p3/p2;
	cout<<"\np3 / p2 = ";p1.Print();
	p1.RemoveTerm(7);                       //RemoveTerm is OK !!
	p1.AddTerm(-3,3);
	p3.RemoveTerm(8);
	cout<<"\np3      = ";p3.Print();
	cout<<"\np1      = ";p1.Print();
	polynomial p7;
	p7=p1/p2;
	cout<<"\np1 / p2 = ";p7.Print();
	polynomial p4=p1%p2;
	cout<<"\np1 % p2 = ";p4.Print();
	cout<<"test to find if % works write"<<((p1/p2*p2+p4)==p1)<<endl;
	if(p1==p2)cout<<"\np1==p3"<<endl; 
	else if(p1!=p2)cout<<"\np1!=p2"<<endl;   //operators (== ,!=)are OK!!
	p3.AddTerm(3,0);
	cout<<"\np3      = ";p3.Print();
	polynomial p5;
	p5=p3.Differentiate();
    cout<<"\ndp5/dx    = ";p5.Print();    //differentiation is OK!!
	p5=p3.Integral();                     //integration is OK !!
	cout<<"\np5  = ";p5.Print();
	string pp5=p5.ToString();             //ToString is OK!!
	cout<<"\np5  = "<<pp5<<endl;
	int k=p5.HeighestExponent();
	cout<<"\nH.E.of p5 = "<<k<<endl;
	k=p5.LowestExponent();
	cout<<"\nL.E.of p5 = "<<k<<endl;
	int *exparr =p5.Exponents();
	int s=p5.Terms();
	for(int j=0;j<s;j++)                  //Terms & Exponents are OK !!
		cout<<*(exparr+j)<<endl;
	p3.Coefficient(5);                    //Coefficient is OK !!
    polynomial p6=p1*p3;

	 cout<<"\np6  = ";p6.Print();
	 string pp6=p6.ToString();
	 cout<<"\np6  = "<<pp6;


	 cout<<endl<<endl<<endl;

	

	return 0;
}






