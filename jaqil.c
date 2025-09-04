/*
        Pick leader from here. 
        Leader shares data with other sqlite server
        If leader goes down then next server becomes the leader 
        When the server comes back up the other server remains the leader until it goes down
        

        Leader receives messages from the client. Non leader doesn't receive messages from the client
        

*/

#include <stdio.h> 


