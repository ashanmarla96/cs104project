#ifndef TARJAN_H
#define TARJAN_H
#include <stack>
using namespace std;

void TwitEng::tarjanHelper(int u,vector< vector<int> > g,vector<int>& index, vector<int>& low_index, 
	stack<int>& S, int& disc, vector<int>& in_stack, vector<User*>& userVec){
    
	//cout << "Enter recur" << endl;

    index[u] = low_index[u] = ++disc;
    

    //disc = 0;
	in_stack[u] = 1;
	S.push(u);
	for(unsigned int i = 0;i < g[u].size();i++){
		int v = g[u][i]; 
		if(index[v] == -1){
			tarjanHelper(v,g,index,low_index, S, disc, in_stack, userVec);
			low_index[u] = min(low_index[v],low_index[u]);
		}
	                          		           
		else if(in_stack[v] == 1){
			low_index[u] = min(low_index[u],index[v]);
		}          
		        
	}
	//cout << "Index = " << index[u] << " Low = " << low_index[u] << endl; 
	int tup = 1;
	if(index[u] == low_index[u])              
	{                 
		//cout << "equal" << endl; 
		cout << "Component"  << endl;                     
		while(S.empty() == false )
		{
			int i_ = S.top();
			// cout<<S.top()<<" ";
			
			cout << userVec[i_]->name() << endl; 
			in_stack[S.top()] = 0;	
			S.pop();
			tup += 1;

			if(i_ == u){
				 
				break;
			}
		}
		cout << endl;

	}
}
#endif