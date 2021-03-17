# CountryListProject
 A web application that lists all the countries between USA and destination. 

User inputs a destination (from the US), the name is sent to the server via jQuery POST,
the server runs a C++ script that runs Dijkstra's algorithm on the map (where
countries are nodes and edges are borders), takes in the name, and returns the
shortest path between the US and the destination based on the shortest path
tree.

The server sends the response back to the client inside a ul tag. A div tag is
then inserted in the index.html file, and div innerHTML is set to the html
received.

I assumed that the app would need to be extendible, so I made it possible to make additions.
It is possible to extend the app to add more countries, or even cities if desired. The app 
could also serve more functions, if desired. I assumed that if this was a project for a client, which might be outside the US, they might want to be able to choose the starting point. 


