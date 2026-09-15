#include <stdio.h>
#include <stdlib.h>
#include "delivery.c"

int main()
{
    printf("Delivery Network Management System\n");
    printf("===================================\n");

    CreateNetwork();
    AddTransportRoutes();
    DisplayNetwork();
    TraverseNetworkDFS();
    TraverseNetworkBFS();

    return 0;
}
