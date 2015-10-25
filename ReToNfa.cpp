/* Simulate a ε-nfa from a regular expression. */

#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#define max 100

using namespace std;



typedef struct edge
{
	int target;
	//wchar_t label;
	char label;
}edge;
 
  
typedef struct node
{
	int nodeno;
	int noofedge;
	struct edge* Aedge;
}node;


typedef struct graph
{

	int tnodes;
	node *nodes;
}graph;


typedef struct stack 
{
	int top;
	graph *ar;
}stack;

typedef struct stackstr 
{
	int top;
	char ar[max];
}stackstr;

class test 
{

	string s,s1,s2;
	char pos[max];
		
	char ch;
	public:
	stackstr st;
	test(string str)
	{
		s.assign(str);
		
	}
//.......................................................putting dots in r.e ..........................................................	

	void putDot()
	{	int k=0;
		
		for(int i=0;i < s.length();i++,k++)
		{
			int j=i+1;
			s1+=s.at(i);
			
			if((s[i] >= 96 && s[i] <= 122) || s[i] == ')' || s[i] == '*' || s[i] == '+')
			{
				if((s[j]>= 96 && s[j] <= 122) || s[j]=='(')
				{
					
					k=k+1;
					s1.append(".");
				}
			}		
			
		
		}
		
	}

//...............................................................postfix...................................................................
	
	void init()
	{
		st.top = -1 ;
		
	}
	
	void push(char val)
	{	
		if(st.top == max)
			return;
		st.top++;
		st.ar[st.top]=val;
		
	}
	char pop()
	{
		if(st.top ==-1)
			return -1;
		return(st.ar[st.top--]);
	}
	int isopnd(char ch)
	{
		if(ch >= 96 && ch <= 122 )
			return 1;
		else
			return 0;
	}
	int isoptr(char ch)
	{
		switch(ch)
		{
			case '*':
			case '+':
			case '|':
			case '.':
			case '(':
			case ')':return 1;
				
			default:return 0;
		}
	}
	int precd(char ch)
	{
		switch(ch)
			{
				case '*':
				case '+':return 2;
				case '|':
				case '.':return 1;
				default:return 0;
			}
	}
	char peek()
	{
		char temp;
		if(st.top==-1)
			return 0;
		temp=pop();
		push(temp);
		return temp;
	}		
	string postfix()
	{
		int j=0,i;
		s2.assign(s1);
		
		s2.append(")");
		
		init();			
		
		
		push('(');
		
		for(i=0;i<s2.length();i++)
		{
			if(isopnd(s2.at(i)))
			{
				
				pos[j++]=s2.at(i);
				
			}			
			else if(s2[i]=='(')
				push('(');
			else if(s2[i]==')')
			{
				while((ch=pop())!='(')
					pos[j++]=ch;
			}
			else if(isoptr(s2[i]))
			{
				while(precd(peek())>=precd(s2.at(i)))
				{
					ch=pop();
					pos[j++]=ch;
				}
				push(s2[i]);
			}
			pos[j]='\0';
			
		}
		if(st.top==-1)
		return pos;
		else
			return s;
	}
};




class graphtest {
	public:

//............................................................Basic function ..........................................................

	graph* Basic(char x){
	
		graph *g;
		g=new graph;
		g->tnodes=2;
		g->nodes=new node[2];
		g->nodes[0].nodeno=0;
		g->nodes[1].nodeno=1;
		g->nodes[0].noofedge=1;
		g->nodes[1].noofedge=0;
		g->nodes[0].Aedge=new edge;
		g->nodes[0].Aedge[0].target=1;
		g->nodes[0].Aedge[0].label=x;
				
	
			
		return g;
		
	}	
//.............................................................Or Function............................................................

	graph* orGraph(graph *g1,graph *g2) {
		int i,j;
		graph *g;
		g=new graph;
		g->tnodes=g1->tnodes+g2->tnodes+2;
		g->nodes=new node[g->tnodes];
		
		int count=1;		
		for(i=0;g1->nodes[i].noofedge!=0;i++){
			g->nodes[count]=g1->nodes[i];
			if(g->nodes[count].noofedge==1)
				g->nodes[count].Aedge->target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge->target );
			else{
				g->nodes[count].Aedge[0].target=count+(g1->nodes[i].Aedge[0].target - g1->nodes[i].nodeno);
				if(g1->nodes[i].Aedge[1].target > g1->nodes[i].nodeno)
					g->nodes[count].Aedge[1].target=count+(g1->nodes[i].Aedge[1].target - g1->nodes[i].nodeno);
				else
					g->nodes[count].Aedge[1].target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge[1].target );
			}
			g->nodes[count].nodeno=count++;
			
			
		}			
		g->nodes[count]=g1->nodes[i];
		
		
		
		g->nodes[count].nodeno=count;
		int lsno=count++;

		for(j=0;g2->nodes[j].noofedge!=0;j++){
			g->nodes[count]=g2->nodes[j];
			if(g->nodes[count].noofedge==1){
					
					g->nodes[count].Aedge->target=count-(g2->nodes[j].nodeno-g2->nodes[j].Aedge->target );}
				else{
					
					g->nodes[count].Aedge[0].target=count+(g2->nodes[j].Aedge[0].target - g2->nodes[j].nodeno);
					if(g2->nodes[j].Aedge[1].target > g2->nodes[j].nodeno){
						
						g->nodes[count].Aedge[1].target=count+(g2->nodes[j].Aedge[1].target - g2->nodes[j].nodeno);}
					else
						g->nodes[count].Aedge[1].target=count-(g2->nodes[j].nodeno-g2->nodes[j].Aedge[1].target );

					
				}
			g->nodes[count].nodeno=count++;
		}
		g->nodes[count]=g2->nodes[j];
		
		g->nodes[count].nodeno=count++;
		 
		g->nodes[0].nodeno=0;
		g->nodes[0].noofedge=2;
		g->nodes[0].Aedge= new edge[2];
		g->nodes[0].Aedge[0].target=g->nodes[1].nodeno;
		g->nodes[0].Aedge[0].label='$';
		
		
		g->nodes[0].Aedge[1].target=g->nodes[lsno].nodeno+1;
		
		g->nodes[0].Aedge[1].label='$';		
		
		g->nodes[count].nodeno=count;		
		g->nodes[count].noofedge=0;
		
		g->nodes[lsno].Aedge= new edge;
		g->nodes[lsno].noofedge=1;
		g->nodes[lsno].Aedge->target=count;
		g->nodes[lsno].Aedge->label='$';
		g->nodes[count-1].Aedge= new edge;
		g->nodes[count-1].noofedge=1;
		g->nodes[count-1].Aedge->target=count;
		g->nodes[count-1].Aedge->label='$';
		
		
		return g;
		
	}
//............................................................And Function..............................................................
	
		graph* andGraph(graph *g1,graph *g2) {
			int i,j;
			
			graph *g=new graph;
					
			int x=g1->tnodes;
			int y=g2->tnodes;
			g->tnodes=x+y;

			g->nodes=new node[g->tnodes];
			
			int count=0;	
			
			for(i=0;g1->nodes[i].noofedge!=0;i++){
				
				g->nodes[count]=g1->nodes[i];
				if(g->nodes[count].noofedge==1)
					g->nodes[count].Aedge->target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge->target );
				else{
					g->nodes[count].Aedge[0].target=count+(g1->nodes[i].Aedge[0].target - g1->nodes[i].nodeno);
					if(g1->nodes[i].Aedge[1].target > g1->nodes[i].nodeno)
						g->nodes[count].Aedge[1].target=count+(g1->nodes[i].Aedge[1].target - g1->nodes[i].nodeno);
					else
						g->nodes[count].Aedge[1].target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge[1].target );
				}
				g->nodes[count].nodeno=count++;
				
			
			}			
			
			g->nodes[count]=g1->nodes[i];
				
			g->nodes[count].nodeno=count;
			
			g->nodes[count].Aedge=new edge;
			g->nodes[count].noofedge=1;
			g->nodes[count].Aedge->target=count+1;
			
			g->nodes[count].Aedge->label='$';
			
			int lsno=count++;
			
			for(j=0;g2->nodes[j].noofedge!=0;j++){
				
				g->nodes[count]=g2->nodes[j];
				if(g->nodes[count].noofedge==1){
					
					g->nodes[count].Aedge->target=count-(g2->nodes[j].nodeno-g2->nodes[j].Aedge->target );}
				else{
					
					g->nodes[count].Aedge[0].target=count+(g2->nodes[j].Aedge[0].target - g2->nodes[j].nodeno);
					if(g2->nodes[j].Aedge[1].target > g2->nodes[j].nodeno){
						
						g->nodes[count].Aedge[1].target=count+(g2->nodes[j].Aedge[1].target - g2->nodes[j].nodeno);}
					else
						g->nodes[count].Aedge[1].target=count-(g2->nodes[j].nodeno-g2->nodes[j].Aedge[1].target );

					
				}
				g->nodes[count].nodeno=count++;
			}				
			
			g->nodes[count]=g2->nodes[j];
			g->nodes[count].noofedge=0;
			g->nodes[count].nodeno=count;
		return(g);

	}
	
//.....................................................Closure Function.............................................................

	graph* closureGraph(graph *g1) {
		
		int i,j;
		graph *g;
		g=new graph;
		g->tnodes=g1->tnodes+2;
		g->nodes=new node[g->tnodes];
		int count=1;		
		for(i=0;g1->nodes[i].noofedge!=0;i++){
			
			
			g->nodes[count]=g1->nodes[i];
			
			if(g->nodes[count].noofedge==1)
				
				g->nodes[count].Aedge->target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge->target );
			else{
				
				g->nodes[count].Aedge[0].target=count+(g1->nodes[i].Aedge[0].target - g1->nodes[i].nodeno);
				if(g1->nodes[i].Aedge[1].target > g1->nodes[i].nodeno){
					
					g->nodes[count].Aedge[1].target=count+(g1->nodes[i].Aedge[1].target - g1->nodes[i].nodeno);}
				else
					g->nodes[count].Aedge[1].target=count-(g1->nodes[i].nodeno-g1->nodes[i].Aedge[1].target );
			}
			g->nodes[count].nodeno=count++;
			
		
		}
			
			g->nodes[count]=g1->nodes[i];
			g->nodes[count].noofedge=2;
			g->nodes[count].nodeno=count++;
			
			g->nodes[count].nodeno=count;
			g->nodes[count].noofedge=0;
			g->nodes[0].nodeno=0;
			g->nodes[0].noofedge=2;
			g->nodes[0].Aedge=new edge[2];
			g->nodes[0].Aedge[0].target=1;
			g->nodes[0].Aedge[0].label='$';
			
			g->nodes[0].Aedge[1].target=g->nodes[count].nodeno;
			g->nodes[0].Aedge[1].label='$';
			
			g->nodes[count-1].Aedge=new edge[2];
			g->nodes[count-1].Aedge[0].target=g->nodes[count].nodeno;
			g->nodes[count-1].Aedge[0].label='$';
			g->nodes[count-1].Aedge[1].target=g->nodes[1].nodeno;
			g->nodes[count-1].Aedge[1].label='$';
		return g;
		
	}
//.........................................................Print the graph...........................................................

	
	void print(graph g)
	{
		cout << "the ε-nfa is : " << endl <<"here $ is used as lebels in place of  ε ."<< endl;
		if(g.tnodes==0)
		{
			
			cout << "empty graph" << endl;
		}		
		else
		{

			int v;
			
			cout << "no of nodes :"<<g.tnodes <<endl;
			
			for (v = 0; v < g.tnodes; v++)
			{
				
				cout << "no of edge in " << v << " is ="<<g.nodes[v].noofedge<<endl;
				
				for(int e=0;e<g.nodes[v].noofedge;e++)
				{
					
					cout << "( " << v << " ) " <<"-->-----" ;
					wcout<< g.nodes[v].Aedge[e].label;
					cout<<"----->--" << "( "<< g.nodes[v].Aedge[e].target << " )" <<endl;				
				}
				cout << endl;
			}
			cout <<endl;
		}
	}
};

	

class stest
{
	string s;
	stack *st;
		
	graph *g;
	graphtest *gt;
	
	public:


	stest(string pos) {
		
		s.assign(pos);
		
		st=new stack;
		st->top = -1;
		st->ar=new graph[max];		
			
	
	}
		
	void push(graph* val)
	{	
		
		st->top++;
		
		st->ar[st->top]=*val;
		
		
	}
	graph pop()
	{
	
		return(st->ar[st->top--]);
		
	}
	int isopnd(char ch)
	{
		
		if(ch >= 96 && ch <= 122 )
			return 1;
		else
			return 0;
	}
	int isoptr(char ch)
	{
		
		switch(ch)
		{
			case '*':
			case '+':
			case '|':
			case '.':return 1;
				
			default:return 0;
		}
	}
	
	
 	graph* findval1(graph b,graph a,char sm)
	{
		
		
		if(sm=='|')
			return(gt->orGraph(&b,&a));			
		else
			
			return(gt->andGraph(&b,&a));
						
		
	}
	
	graph* findval2(graph* a)
	{
		
		
			g=gt->closureGraph(a);
	
		return g;
		

	}
	void poseve()
	{
		
		
		s.append(")");
		
		graph a,b,r;
	
		for(int i=0;s.at(i) != ')' ;i++){

			
			if(isopnd(s.at(i)))
			{
				
				g=gt->Basic(s.at(i));
										
				push(g);
				
				
	
			}
			if(isoptr(s.at(i))) 
			{
									
				if(s.at(i)=='|' || s.at(i)=='.')
				{
				
					a=pop();
					b=pop();
					g=findval1(b,a,s.at(i));
					
				}

				if(s.at(i)=='*' /*|| s[i]=='+'*/)
				{
					a=pop(); 				
					g=findval2(&a);
				}
				push(g);
			}
		}
		r=pop();
		gt->print(r);
				
	}


};
int main()
{
	string s1;
	cout<<"Enter a string:";
	cin >> s1;
	
	test t(s1);
	
	t.putDot();
		
	string s2=t.postfix();
	if(s2==s1)
	{
		cout<<"invalid regular expression"<<endl;
	}
	else
	{	
		cout <<"postfix exp is :"<<s2<<endl;

	
		stest ste(s2);
	
		ste.poseve();
	}
	return 0;
}
