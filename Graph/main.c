#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    printf("---- Smart Campus Navigation System ----!\n");
    const char *locations[] = {
        "Main Gate",
        "Bhavan's Library",
        "Bhavan's College",
        "Bhavan's Cultural Center",
        "Bhavan's Research Center",
        "Amphitheater",
        "Hostel",
        "SPJIMR",
        "SPJIMR Hostel",
        "SPJIMR Library Extension",
        "SPCE",
        "SPIT",
        "Temple",
        "Gymkhana",
        "Lake",
        "Playground",
        "Sports Complex",
        "Administration Block"
    };

    initializeGraph();
    
    return 0;
}
