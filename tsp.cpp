#include<bits/stdc++.h>
using namespace std;

void sim_alln(vector<int>& path,int n,vector<vector<float> >& adjlist){
	float temperature=100000;
	int i,j;float prob,sum1,sum2;
	int temp;
	vector<int> path1(n);
	float maxdiff;int flag;
	pair<int,int> p;
	while(temperature>0){
		i=rand()%n;j=rand()%n;
		while(j==i){
			j=rand()%n;
		}
		maxdiff=FLT_MIN;flag=0;
		sum1 =  adjlist[path[i]][path[(i+1)%n]]+adjlist[path[(i-1+n)%n]][path[i]]+adjlist[path[j]][path[(j+1)%n]]+adjlist[path[(j-1+n)%n]][path[j]];
		temp=path[i];path[i]=path[j];path[j]=temp;
		sum2 =  adjlist[path[i]][path[(i+1)%n]]+adjlist[path[(i-1+n)%n]][path[i]]+adjlist[path[j]][path[(j+1)%n]]+adjlist[path[(j-1+n)%n]][path[j]];
		prob=1.0/(1+exp((sum1-sum2)/temperature));
		temp=path[i];path[i]=path[j];path[j]=temp;
		if(rand()/((float)RAND_MAX)<prob){
			temp=path[i];path[i]=path[j];path[j]=temp;
		}
		temperature-=10.0;
	}
}


int main(){
	int n;string eu;
	getline(cin,eu);
	cin>>n;
	for(int i=0;i<n;i++){
		float x,y;
		cin>>x>>y;
	}
	vector<float> t(n);
	vector<vector<float > > adjlist(n,t);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>adjlist[i][j];
		}
	}
	vector<int> path(n);
	vector<int> path_(n);
	float min_path=FLT_MAX;
	vector<int> final_path(n);
	vector<int> visit(n);
	float sum=0.0;
	int r;

	for(int counter=0;counter<min(200,n);counter++){
		r=rand()%n;
		path[0]=r;
		for(int i=0;i<n;i++)
			visit[i]=0;
		visit[r]=1;int curr=r,temp;
		for(int k=1;k<n;k++){
			float min=FLT_MAX;
			for(int ind=0;ind<n;ind++){
				if(adjlist[curr][ind]<min && visit[ind]==0 && curr!=ind){
					min=adjlist[curr][ind];
					temp=ind;
				}
			}
			visit[temp]=1;
			curr=temp;
			path[k]=temp;
			path_[k]=temp;
		}
	
		float sum1,sum2,maxdiff;int flag;
		pair<int,int> p;int j2;
		vector<int> path1(n);
		while(1){
			maxdiff=FLT_MIN;flag=0;
			for(int i=0;i<n;i++){
				j2=(i+2)%n;
				while((j2+1)%n!=i){
					sum1=adjlist[path[i]][path[(i+1)%n]]+adjlist[path[j2]][path[(j2+1)%n]];
					sum2=adjlist[path[i]][path[j2]]+adjlist[path[(i+1)%n]][path[(j2+1)%n]];
					if(sum2<sum1 && (sum1-sum2)>maxdiff){
						maxdiff=(sum1-sum2);
						p=make_pair(i,j2);flag=1;
					}
					j2=(j2+1)%n;
				}
			}
			if(flag==1){
				int low=(p.first+1)%n;
				int high=p.second;
				path1.erase(path1.begin(),path1.end());
				while(1){
					path1.push_back(path[low]);
					if(low==high)
						break;
					low=(low+1)%n;
				}
				low=(p.first+1)%n;
				for(int ind=path1.size()-1;ind>=0;ind--){
					path[low]=path1[ind];
					low=(low+1)%n;
				}
			}
			else
				break;
		}

		while(1){
			maxdiff=FLT_MIN;flag=0;
			for(int i=0;i<n;i++){
				for(int j=i+1;j<n;j++){
					sum1 =  adjlist[path[i]][path[(i+1)%n]]+adjlist[path[(i-1+n)%n]][path[i]]+adjlist[path[j]][path[(j+1)%n]]+adjlist[path[(j-1+n)%n]][path[j]];
					temp=path[i];path[i]=path[j];path[j]=temp;
					sum2 =  adjlist[path[i]][path[(i+1)%n]]+adjlist[path[(i-1+n)%n]][path[i]]+adjlist[path[j]][path[(j+1)%n]]+adjlist[path[(j-1+n)%n]][path[j]];
					if(sum2<sum1 && (sum1-sum2)>maxdiff){
						maxdiff=(sum1-sum2);
						p=make_pair(i,j);flag=1;
					}
					temp=path[i];path[i]=path[j];path[j]=temp;
				}
			}
			if(flag==1){
				temp=path[p.first];path[p.first]=path[p.second];path[p.second]=temp;
			}
			else
				break;
		}

		sum=0.0;
		for(int i=0;i<n;i++)
			sum+=adjlist[path[i]][path[(i+1)%n]];
		if(sum<min_path){
			for(int i=0;i<n;i++)
				final_path[i]=path[i];
			min_path=sum;
		}
	}

	sum=0.0;
	for(int i=0;i<n;i++){
		sum+=adjlist[final_path[i]][final_path[(i+1)%n]];
		cout<<final_path[i]<<" ";
	}
	cout<<endl;
	return 0;
}