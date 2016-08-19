
#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

pair<int, int> firstpoint;

list<pair<int,int>> hull;

bool comp(pair<double,pair<int,int>> a, pair<double,pair<int,int>> b)
{
    if(a.first!=b.first)
    return a.first<b.first;
    
    else
    {
        if((pow(a.second.first - firstpoint.first,2)+pow(a.second.second - firstpoint.second,2)) > 
        (pow(b.second.first - firstpoint.first,2)+pow(b.second.second - firstpoint.second,2)))
        return false;
        
        else
        return true;
    }
}

void convexHull(pair<int,int> points[],int n)
{
    int i,j,k,a,b,c;
    pair<int,int> min= {1000000,1000000};
    
    for(i=0;i<n;i++)
    {
        if(points[i].second<min.second)
        min = points[i];
        else if(points[i].second==min.second)
        {
            if(points[i].first<min.first)
            min = points[i];
        }
        
        //printf("%d %d\n",points[i].first,points[i].second);
    }
    
    firstpoint = min;
    
    //printf("%d %d\n",firstpoint.first,firstpoint.second);
    
    hull.push_back(min);
    
    vector<pair<double,pair<int,int>>> slopez(n);
    
    double angul, slope90 = 0, ydiff, xdiff, temp; 
    
    for(i=0;i<n;i++)
    {
        ydiff = points[i].second - firstpoint.second;
     
        xdiff = points[i].first - firstpoint.first;
        
        angul = atan2(ydiff,xdiff); //cout<<"angul is "<<angul<<endl;
        
        slopez[i] = {angul,points[i]};
        
       // cout<<i<<" "<<slopez[i].first<<" "<<slopez[i].second.first<<" "<<slopez[i].second.second<<endl;
    }
    
    sort(slopez.begin(),slopez.end(),comp);
    
    slopez.erase(slopez.begin());
    
    for(i=1;i<n-1;i++)
    {
        //printf("slopez[%d] is %f %d %d\n",i,slopez[i].first,slopez[i].second.first,slopez[i].second.second);
            
        if(slopez[i].first == slopez[i- 1].first)
            slopez[i-1].first = 100;
    }
    
    for(i=0;i<n-1;i++)
    {
        //printf("slopez[%d] is %f %d %d\n",i,slopez[i].first,slopez[i].second.first,slopez[i].second.second);
    }
    
    vector<pair<double,pair<int,int>>>::iterator it;
    
    if(slopez[n-1].second==firstpoint)
    {
        it = slopez.begin() + (n - 1);
        
        slopez.erase(it);
    }
    
    hull.push_back(slopez[0].second);
    
    pair<int,int> before1, before2; slopez.push_back({{0},firstpoint});
    
    for(it=slopez.begin()+1;it!=slopez.end();it++)
    {
        if(it->first==100)
        continue;
        
        printf("%d %d\n",(it->second).first,(it->second).second);
        
        pair<int,int> curr = it->second;
        
        list<pair<int , int>>::iterator itl;
        
        itl = hull.end(); itl--; before2 = *itl; itl--; before1 = *itl; 
        
        printf("before1 is %d %d, before2 is %d %d\n",before1.first,before1.second,before2.first,before2.second);
        
        printf("signed area is %d\n",(curr.second - before1.second)*(before2.first - before1.first) - (curr.first - before1.first)*(before2.second - before1.second));
        
        if((curr.second - before1.second)*(before2.first - before1.first) - (curr.first - before1.first)*(before2.second - before1.second)>=0)
        {
             printf("signed area is %d\n",(curr.second - before1.second)*(before2.first - before1.first) - (curr.first - before1.first)*(before2.second - before1.second));
             hull.push_back(it->second);
             printf("nice\n");
        }
        else
        {
            hull.pop_back();
            hull.push_back(it->second);
            printf("wrong\n");
        }
    }
}

int main()
{
	pair<int,int> points[] = {{1,2},{2,6},{3,9},{6,9},{7,9},{8,5},{7,4},{6,3},{3,1},{2,4},{3,4},{4,2},{3,6},{5,5},{6,6},
	    {3,7},{5,7},{5,6}
	};
	int n = sizeof(points)/sizeof(points[0]);
	convexHull(points, n);
	
	printf("potato\n");
	
	while(!hull.empty())
	{
	    cout<<(hull.back()).first<<" "<<(hull.back()).second<<endl;
	    hull.pop_back();
	}
	
	return 0;
}
