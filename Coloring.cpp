#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
 
int n, e, i, j;
vector<int> color(n);
vector<int> arrange;
vector<vector<int> > graph;
vector<vector<int> > matrix;
bool vis[10011];

void greedyColoring()
{
    color[arrange[0]] = 0;
    for(i=1; i<n; i++)
        color[arrange[i]] = -1;
    bool unused[n];
    for(i=0; i<n; i++)
        unused[i] = 0;
    for(i=1; i<n; i++)
    {
        for(j=0; j<graph[arrange[i]].size(); j++)
            if(color[graph[arrange[i]][j]]!=-1)
                unused[color[graph[arrange[i]][j]]] = true;
        int cr;
        for(cr=0; cr<n; cr++)
            if(unused[cr] == false)
                break;
        color[arrange[i]] = cr; 
        for(j=0; j<graph[arrange[i]].size(); j++)
            if(color[graph[arrange[i]][j]]!=-1)
                unused[color[graph[arrange[i]][j]]] = false;
    }
}

int main()
{
	int x, y, k=0;
	
    //Input file dothi.txt
    FILE *fptrin;
    if ((fptrin = fopen("dothi.txt","r")) == NULL)
    {
       cout<<"Error! opening file";
       exit(1);
    }
    fscanf(fptrin,"%d", &n); //cout<<"So dinh: "<<n;
    fscanf(fptrin,"%d", &e); //cout<<"So canh: "<<e;
    vector<int>a(e), b(e);
	vector<int>deg(n,0);
	for(i=0; i<e; i++)
	{
		fscanf(fptrin,"%d", &a[i]); a[i]--;
		fscanf(fptrin,"%d", &b[i]); b[i]--;
		deg[a[i]]++;
    	deg[b[i]]++;
	}
    fclose(fptrin);
    
    //Tim bac k lon nhat
    vector<int>c(n,0);
   	for(i=0; i<deg.size(); i++)
		if(deg[i]>k)
	    	k = deg[i];
	for(i=0; i<deg.size(); i++)
	    if(deg[i]!=k)
	    {
	        arrange.push_back(i);
	        c[i] = 1;
	        break;
	    }
	
	//Chuyen ve ma tran ke
	matrix.resize(n);
	for(i=0; i<n;i++) 
	{
	    matrix[i].resize(n);
	    for(j=0; j<n; j++)
	    	matrix[i].push_back(0);
    }
	for(i=0; i<a.size(); i++)
    {
    	matrix[a[i]][b[i]] = 1;
    	matrix[b[i]][a[i]] = 1;
	}
	// for(i=0; i<n; i++){for(j=0; j<n; j++){cout<<matrix[i][j]<<" ";}cout<<'\n';}

    //Sap xep cac dinh cua do thi
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			if(matrix[arrange[i]][j]==1&&c[j]==0)
			{
				arrange.push_back(j);
				c[j] = 1;
		    }
		if(arrange.size()==n) break;
	}
	
	//Dao nguoc vector arrange
	for(i=0; i<n/2; i++)
    {
        int index = n - i - 1;
        int tmp = arrange[index];
        arrange[index] = arrange[i];
        arrange[i] = tmp;
    } 
	// for(i=0; i<n; i++) cout<<arrange[i]<<" ";
	
	//Dung thuat toan tham lam de to mau	
	graph.resize(n);
    color.resize(n);
    memset(vis,0,sizeof(vis));
	for(i=0; i<e; i++)
    {
        x = a[i]; y = b[i];
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    greedyColoring();
    for(i=0; i<n; i++) cout<<"Dinh "<<arrange[i]+1<<" co mau "<<color[arrange[i]]+1<<"\n";
    	 
    //Output file dothitomau.dot
    char mau[][20] = { "red","green","blue","tomato","yellow","purple","gray","lawn green","YellowGreen","light salmon","hot pink",
		"orange","chocolate","azure4","SlateGray3","gold4","light green","RosyBrown2","DodgerBlue1","MistyRose1" };
    FILE *fptrout;
    fptrout = fopen("tomaudothi.dot","w");
 
    if(fptrout == NULL)
    {
    	cout<<"Error!";
    	exit(1);
	}
    fprintf(fptrout,"%s","graph dothi\n{\n");
    for(i=0; i<n; i++)
    {
    	fprintf(fptrout, "  %d [fillcolor=%s, style=filled];\n", arrange[i]+1, mau[color[arrange[i]]]);
	}
	for(i=0; i<e; i++)
	{
	fprintf(fptrout, "  %d -- %d;\n", a[i]+1, b[i]+1);	
	}
	fprintf(fptrout,"%s","}");
	
    fclose(fptrout);
		 
	return 0;
}

