#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void){
    int rank;int comm_sz;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int counter = 0;
    int tag = (rank + 1) % 2;
 
    for(int i=0;i<5;i++){
    	if (rank == counter % 2) {
            counter++;
            MPI_Send(&counter,1,MPI_INT,tag,0,MPI_COMM_WORLD);
            cout<<rank<<" a "<<tag<<" envia e incrementa el contador a "<<counter<<endl;
        } else {
            MPI_Recv(&counter,1,MPI_INT,tag,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            cout<<tag<<" a "<<rank<<" recibe el contador a "<<counter<<endl;
        }
    }
    MPI_Finalize();
    return 0;
}


