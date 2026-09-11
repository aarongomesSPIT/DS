
const char *locations[] = {
        "Main Gate (YOU ARE HERE)",     // 0  - Marked at the bottom entrance
        "Library",                      // 1  - Labeled "LIBRARY" on map
        "Bhavan's College",             // 2  - Labeled "BHAVAN'S COLLEGE"
        "Bhavan's Cultural Centre",     // 3  - Labeled "BHAVAN'S CULTURAL CENTRE" (British spelling on map)
        "Bhavan's Research Centre",     // 4  - Labeled "BHAVAN'S RESEARCH CENTRE MICROBIOLOGY"
        "Amphitheatre",                 // 5  - Labeled "AMPHITHEATRE" (small curved label near Lake)
        "Hostel",                       // 6  - Labeled "HOSTEL" (top left)
        "SPJIMR",                       // 7  - Labeled "SPJIMR"
        "SPJIMR Hostel",                // 8  - Labeled "SPJIMR HOSTEL" (top center)
        "Library Extension",            // 9  - Labeled "LIBRARY EXTENSION" (bottom left)
        "SPCE",                         // 10 - Labeled "SPCE" (adjacent to SPIT)
        "SPIT",                         // 11 - Labeled "SPIT"
        "Temple",                       // 12 - Labeled "TEMPLE" (small icon near Main Gate)
        "Gymkhana",                     // 13 - Located near Sports Complex/Playground
        "Lake",                         // 14 - Labeled "LAKE"
        "Playground",                   // 15 - Labeled "PLAYGROUND"
        "Sports Complex",               // 16 - Labeled "SPORTS COMPLEX"
        "A H Wadia Highschool"          // 17 - Labeled "A H WADIA HIGHSCHOOL" (top right)
    };

void startCustomMap()
{
    int numEdges;
    int numVertices;
    printf("Enter Number of campus locations (vertices): ");
    scanf("%d", &numVertices);
    printf("Enter the number of roads (edges) in your custom map: ");
    scanf("%d", &numEdges);
    initializeGraph();
    for (int i = 0; i < numEdges; i++)
    {
        int u, v;
        printf("Enter edge %d (format: u v): ", i + 1);
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
}


void startCampusMap()
{
    initializeGraph();

    // Main Gate (0) - marked as "YOU ARE HERE" near bottom center
    addEdge(0, 9);   // Main Gate -> SPJIMR Library Extension
    addEdge(0, 7);   // Main Gate -> SPJIMR
    addEdge(0, 12);  // Main Gate -> Temple (small structure near entrance)
    addEdge(0, 2);   // Main Gate -> Bhavan's College
    addEdge(0, 15);  // Main Gate -> Playground
    addEdge(0, 16);  // Main Gate -> Sports Complex

    // Bhavan's Library (1)
    addEdge(1, 2);   // Library -> Bhavan's College
    addEdge(1, 4);   // Library -> Bhavan's Research Center

    // Bhavan's College (2)
    addEdge(2, 0);   // Bhavan's College -> Main Gate
    addEdge(2, 1);   // Bhavan's College -> Library
    addEdge(2, 3);   // Bhavan's College -> Cultural Centre
    addEdge(2, 10);  // Bhavan's College -> SPCE
    addEdge(2, 14);  // Bhavan's College -> Lake

    // Bhavan's Cultural Center (3)
    addEdge(3, 1);   // Cultural Centre -> Library
    addEdge(3, 2);   // Cultural Centre -> Bhavan's College
    addEdge(3, 4);   // Cultural Centre -> Research Center
    addEdge(3, 5);   // Cultural Centre -> Amphitheater
    addEdge(3, 17);  // Cultural Centre -> High School

    // Bhavan's Research Center (4)
    addEdge(4, 1);   // Research Center -> Library
    addEdge(4, 3);   // Research Center -> Cultural Centre
    addEdge(4, 15);  // Research Center -> Playground

    // Amphitheater (5)
    addEdge(5, 3);   // Amphitheater -> Cultural Centre
    addEdge(5, 14);  // Amphitheater -> Lake
    addEdge(5, 8);   // Amphitheater -> SPJIMR Hostel

    // Hostel (6)
    addEdge(6, 8);   // Hostel -> SPJIMR Hostel
    addEdge(6, 11);  // Hostel -> SPIT / SPCE Workshop

    // SPJIMR (7)
    addEdge(7, 0);   // SPJIMR -> Main Gate
    addEdge(7, 9);   // SPJIMR -> Library Extension
    addEdge(7, 11);  // SPJIMR -> SPIT

    // SPJIMR Hostel (8)
    addEdge(8, 6);   // SPJIMR Hostel -> Hostel
    addEdge(8, 5);   // SPJIMR Hostel -> Amphitheater
    addEdge(8, 17);  // SPJIMR Hostel -> High School

    // SPJIMR Library Extension (9)
    addEdge(9, 0);   // Library Extension -> Main Gate
    addEdge(9, 7);   // Library Extension -> SPJIMR

    // SPCE (10)
    addEdge(10, 2);  // SPCE -> Bhavan's College
    addEdge(10, 11); // SPCE -> SPIT

    // SPIT (11)
    addEdge(11, 7);  // SPIT -> SPJIMR
    addEdge(11, 10); // SPIT -> SPCE
    addEdge(11, 6);  // SPIT -> Hostel

    // Temple (12)
    addEdge(12, 0);  // Temple -> Main Gate

    // Gymkhana (13)
    addEdge(13, 16); // Gymkhana -> Sports Complex

    // Lake (14)
    addEdge(14, 2);  // Lake -> Bhavan's College
    addEdge(14, 5);  // Lake -> Amphitheater

    // Playground (15)
    addEdge(15, 0);  // Playground -> Main Gate
    addEdge(15, 4);  // Playground -> Research Center
    addEdge(15, 16); // Playground -> Sports Complex

    // Sports Complex (16)
    addEdge(16, 0);  // Sports Complex -> Main Gate
    addEdge(16, 13); // Sports Complex -> Gymkhana
    addEdge(16, 15); // Sports Complex -> Playground

    // High School (17)
    addEdge(17, 3);  // High School -> Cultural Centre
    addEdge(17, 8);  // High School -> SPJIMR Hostel

}