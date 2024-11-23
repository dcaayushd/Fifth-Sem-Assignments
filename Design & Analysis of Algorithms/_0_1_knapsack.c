#include<stdio.h>
// #include<conio.h>
 

int c[100][100];
 

void Knapsack(int W , int n , int wt[] ,int v[]){
int i,w;
for(i=0;i<=n;i++)
c[i][0]=0; 

for(w=0;w<=W;w++)
c[0][w]=0;
 

for(i=1;i<=n;i++){
for(w=1;w<=W;w++){
if(wt[i-1]>w)
c[i][w]=c[i-1][w];
else{
if((v[i-1]+c[i-1][w-wt[i-1]])>c[i-1][w]){
c[i][w]=v[i-1]+c[i-1][w-wt[i-1]];
}else{
c[i][w]=c[i-1][w];
}
}
}
 

}
}
int main(){
int w[100];
int v[100];
int W,n,i,wt;
 

printf("Enter the capacity and number of item:");
scanf("%d%d",&W,&n);
for(i=0;i<n;i++){
printf("Enter weight and value of  [%d] item\t",(i+1));
scanf("%d%d",&w[i],&v[i]);
}
Knapsack(W,n,w,v);
 
for(i=0;i<=n;i++){
for(wt=0;wt<=W;wt++){
printf("%d\t",c[i][wt]);
}
printf("\n");
}
 

 

return 0;
}
