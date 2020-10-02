#include <stdio.h>
#include <string.h>
#include <mpi.h> 

double f(double x) {
   return x*x;
} 

double Trap( double left_endpt, double right_endpt,int trap_count,double base_len){
    double estimate, x;
    int i;
    estimate = (f(left_endpt) + f(right_endpt))/2.0;
    for (i = 1; i <= trap_count - 1; i++) {
        x = left_endpt + i*base_len;
        estimate += f(x);
    }
    estimate = estimate*base_len;
    return estimate;
} 

int main(void) {
    int rank, comm_sz, n = 1024, local_n;
    double a = 0.0, b = 3.0, h, local_a, local_b;
    double local_int, total_int;
    int source;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    h = (b - a)/n;
    local_n = n/comm_sz;
    local_a = a + rank*local_n*h;
    local_b = local_a + local_n*h;
    local_int = Trap(local_a, local_b, local_n, h);
    
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

    if (rank == 0) {
    	cout<<"con "<<n<<" trapezoides, se estima la integral desde "<<a<<" hasta "<<b<< " = "<<total_int<<endl;
    }
    MPI_Finalize();
    return 0;
 }