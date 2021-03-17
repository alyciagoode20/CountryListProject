# CountryListProject
 A web application that lists all the countries between USA and destination. 

User inputs a destination (from the US), the name is sent to the server via jQuery POST,
the server runs a C++ script that runs Dijkstra's algorithm on the map (where
countries are nodes and edges are borders), takes in the name, and returns the
shortest path between the US and the destination based on the shortest path
tree.

The server sends the response back to the client inside a <ul> tag. A <div> tag is
then inserted in the index.html file, and <div> innerHTML is set to the html
received.
