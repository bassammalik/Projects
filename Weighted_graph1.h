/*****************************************

 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of those students
 * I had worked together in preparing this project:
 *    Ayah Ibrahim
 *    Keith Ly
 *    Bassam Malik
 *    Leslie Hsiao
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Excception.h"
// include whatever classes you want

//Vertex class
class Vertex {
public:
   int label;

   static inline int s_instCount = 0;

   Vertex(const int& vertexLabel) {
      label = vertexLabel;
   }
};

//Edge class
class Edge {
public:
   Vertex* fromVertex;
   Vertex* toVertex;
   double weight;

   Edge(Vertex* from, Vertex* to, double edgeWeight) {
      fromVertex = from;
      toVertex = to;
      weight = edgeWeight;
   }
};

//Class for Dijkstras Algortithm
class PathVertexInfo {
public:
   Vertex* vertex;
   double distance;
   Vertex* predecessor;

   PathVertexInfo(Vertex* vertex = nullptr) {
      this->vertex = vertex;
      distance = std::numeric_limits<double>::infinity();
      predecessor = nullptr;
   }

   // Utility function to remove and return the PathVertexInfo from the vector
   // that has the minimum distance
   static PathVertexInfo* RemoveMin(std::vector<PathVertexInfo*>& items) {
      if (0 == items.size()) {
         return nullptr;
      }

      int minIndex = 0;
      for (int i = 1; i < items.size(); i++) {
         if (items[i]->distance < items[minIndex]->distance) {
            minIndex = i;
         }
      }

      // Get the info with the minimum distance
      PathVertexInfo* infoWithMinDistance = items[minIndex];

      // Remove the info with the minimum distance
      items.erase(items.begin() + minIndex);

      return infoWithMinDistance;
   }
};

// Weighted graph class
class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions

		// Maps integer labels to vertices
		std::unordered_map<int, Vertex*> vertices;
        // Maps a vertex to a List of all edges that start from that vertex
        std::unordered_map<Vertex*, std::vector<Edge*>*> fromEdges;

        // Maps a vertex to an ArrayList of all edges that go to that vertex
        std::unordered_map<Vertex*, std::vector<Edge*>*> toEdges;

        int vertexNum = 50;

		static const double INF;

	public:
		Weighted_graph( int num ) {
		    if (num <= 0) {
                num = 1;
		    }
		    vertexNum = num;
		    for (int i = 0; i < num; i ++) {
                AddVertex(i + 1);
		    }
		}
		Weighted_graph( ) : Weighted_graph(50) {}
		~Weighted_graph() {
            // Get the set of vertices and the set of edges
            std::unordered_set<Vertex*> distinctVertices;
            std::unordered_set<Edge*> distinctEdges;
            for (auto& keyValue : fromEdges) {
                distinctVertices.insert(keyValue.first);
                for (Edge* edge : *keyValue.second) {
                    distinctEdges.insert(edge);
                }
            }
            for (auto& keyValue : toEdges) {
                distinctVertices.insert(keyValue.first);
                for (Edge* edge : *keyValue.second) {
                    distinctEdges.insert(edge);
                }
            }

            // Clear each map
            fromEdges.clear();
            toEdges.clear();

            // Free each edge and each vertex
            for (Edge* edge : distinctEdges) {
                delete edge;
            }
            for (Vertex* vertex : distinctVertices) {
                delete vertex;
            }
        }
        Vertex* AddVertex(int newVertexLabel) {
            // Create the new Vertex object
            Vertex* newVertex = new Vertex(newVertexLabel);

            // Every vertex must exist as a key in both maps
            fromEdges[newVertex] = new std::vector<Edge*>();
            toEdges[newVertex] = new std::vector<Edge*>();

            vertices.emplace(newVertexLabel, newVertex);

            return newVertex;
        }

        Edge* AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex, double weight) {
            // Don't add the same edge twice
            if (HasEdge(fromVertex, toVertex)) {
                return nullptr;
            }

            // Create the Edge object
            Edge* newEdge = new Edge(fromVertex, toVertex, weight);

            // Add the edge to the appropriate list in both maps
            fromEdges[fromVertex]->push_back(newEdge);
            toEdges[toVertex]->push_back(newEdge);

            return newEdge;
        }

        std::pair<Edge*, Edge*> AddUndirectedEdge(Vertex* vertexA, Vertex* vertexB,
            double weight) {
                return std::pair<Edge*, Edge*>(
                    AddDirectedEdge(vertexA, vertexB, weight),
                    AddDirectedEdge(vertexB, vertexA, weight));
        }

        // Returns an unordered_set of all of this graph's edges
        std::unordered_set<Edge*> GetEdges() const {
            std::unordered_set<Edge*> edgesSet;
            for (auto& keyValue : fromEdges) {
                std::vector<Edge*>* edges = keyValue.second;
                for (Edge* edge : *edges) {
                    edgesSet.insert(edge);
                }
            }
            return edgesSet;
        }

        // Returns a vector of edges with the specified fromVertex
        const std::vector<Edge*>* GetEdgesFrom(Vertex* fromVertex) const {
            return fromEdges.at(fromVertex);
        }

        // Returns a vector of edges with the specified toVertex
        const std::vector<Edge*>* GetEdgesTo(Vertex* toVertex) const {
            return toEdges.at(toVertex);
        }

        // Returns a vertex with a matching label, or nullptr if no such vertex exists
        Vertex* GetVertex(int vertexLabel) const {
            for (auto& keyValue : fromEdges) {
                Vertex* vertex = keyValue.first;
                if (vertex->label == vertexLabel) {
                    return keyValue.first;
                }
            }
            return nullptr;
        }

        // Returns a vector of all of this graph's vertices
        std::vector<Vertex*> GetVertices() const {
            std::vector<Vertex*> vertices;
            for (auto& keyValue : fromEdges) {
                vertices.push_back(keyValue.first);
            }
            return vertices;
        }

        // Returns true if this graph has an edge from fromVertex to toVertex
        bool HasEdge(Vertex* fromVertex, Vertex* toVertex) const {
            if (0 == fromEdges.count(fromVertex)) {                // fromVertex is not in this graph
                return false;
            }

            // Search the list of edges for an edge that goes to toVertex
            std::vector<Edge*>& edges = *fromEdges.at(fromVertex);
            for (Edge* edge : edges) {
                if (edge->toVertex == toVertex) {
                    return true;
                }
            }
            return false;
        }

    std::unordered_map<Vertex*, PathVertexInfo*> DijkstraShortestPath(Vertex* startVertex) {
        // Create the unordered_map for vertex information
        std::unordered_map<Vertex*, PathVertexInfo*> info;

        // Put all graph vertices in both the info unordered_map and the
        // vector of unvisited vertices
        std::vector<PathVertexInfo*> unvisited;
        for (Vertex* vertex : this->GetVertices()) {
            PathVertexInfo* vertexInfo = new PathVertexInfo(vertex);
            unvisited.push_back(vertexInfo);
            info[vertex] = vertexInfo;
    }

        // startVertex has a distance of 0 from itself
        info[startVertex]->distance = 0.0;

        // Iterate through all vertices in the priority queue
        while (unvisited.size() > 0) {
            // Remove info with minimum distance
            PathVertexInfo* currentInfo = PathVertexInfo::RemoveMin(unvisited);

            // Check potential path lengths from the current vertex to all neighbors
            for (Edge* edge : *this->GetEdgesFrom(currentInfo->vertex)) {
                Vertex* adjacentVertex = edge->toVertex;
                double alternativePathDistance = currentInfo->distance + edge->weight;

                // If a shorter path from startVertex to adjacentVertex is found,
                // update adjacentVertex's distance and predecessor
                PathVertexInfo* adjacentInfo = info[adjacentVertex];
                if (alternativePathDistance < adjacentInfo->distance) {
                    adjacentInfo->distance = alternativePathDistance;
                    adjacentInfo->predecessor = currentInfo->vertex;
                }
            }
        }

        return info;
        }

        // This function returns the number of edges connected to vertex A. It
        // throws an exception for any invalid vertex.
		int degree( int A ) const {
		    Vertex *a = GetVertex(A);

		    // if a is an invalid vertex throw exception
		    if (a == nullptr) {
                std:: cout << "Invalid value for vertex, Enter a value between 1 and " << vertexNum << std::endl;
                throw illegal_argument();
		    }
		    std::vector<Edge*> edges = *GetEdgesFrom(a);
		    int counter = 0;
		    for (Edge* edge : edges) {
                counter++;
		    }
		    return counter;
		}

		// This function returns the total number of edges. It takes into account if there are
		// no edges in the graph.
		int edge_count() const {
		    int counter = 0;
		    std::vector<Vertex*> lists = GetVertices();
		    for (Vertex* ver : lists) {
                counter += degree(ver->label);
		    }
		    if (counter == 0) {
                std:: cout << "There are no edges" << std::endl;
                return 0;
		    }
		    return counter / 2;
		}

		// This function returns the weight of the edge between vertex A and B. It takes into
		// account if the vertices are valid and if they have an edge.
		double adjacent( int A, int B) const {
            Vertex *a = GetVertex(A);
		    Vertex *b = GetVertex(B);

		    if (a == nullptr || b == nullptr) {
                std:: cout << "Invalid value for vertex, Enter a value between 1 and " << vertexNum << std::endl;
                throw illegal_argument();
		    }

		    if (a == b) {
                return 0;
		    }

		    if (HasEdge(a, b)) {
                // Search the list of edges for an edge that goes to toVertex
                std::vector<Edge*>& edges = *fromEdges.at(a);
                for (Edge* edge : edges) {
                    if (edge->toVertex == b) {
                        return edge->weight;
                    }
                }
		    }
		    else {
                std:: cout << "This edge does not exist" << std::endl;
                return INF;
		    }
		}

		// This returns the shortest distance between vertex A and B. This function
		// takes into account if the vertices are valid, if the vertices are connected,
		// and if the two vertices are the same.
		double distance( int A, int B) {
		    // Start from endVertex and build the path in reverse.
		    Vertex *a = GetVertex(A);
		    Vertex *b = GetVertex(B);

		    if (a == nullptr || b == nullptr) {
                std:: cout << "Invalid value for vertex, Enter a value between 1 and " << vertexNum << std::endl;
                throw illegal_argument();
		    }

		    if (a == b) {
                return 0.0;
		    }

		    int p;
		    std::unordered_map<Vertex*, PathVertexInfo*> infoMap = DijkstraShortestPath(a);
            Vertex* prevVertex = b;
            Vertex* currentVertex = infoMap[prevVertex]->predecessor;
            while (currentVertex != a) {
                std::vector<Edge*>& edges = *fromEdges.at(prevVertex);
                for (Edge* edge : edges) {
                    if (edge->toVertex == currentVertex) {
                        p += edge->weight;
                    }
                }
                if ( currentVertex == nullptr) {
                    std:: cout << "There is no connection between these verticies" << std::endl;
                    return INF;
                }
                prevVertex = currentVertex;
                if ( infoMap[currentVertex]->predecessor == nullptr) {;
                    return p;
                }
                currentVertex = infoMap[currentVertex]->predecessor;
            }
            std::vector<Edge*>& edges = *fromEdges.at(prevVertex);
            for (Edge* edge : edges) {
                if (edge->toVertex == currentVertex) {
                    p += edge->weight;
                }
            }
            return p;
		}

		// Inserts an edge between A and B of weight W. It only works if
		// the edges weight is a positive number other than zero or infinity.
		// It checks that the vertices are in the graph and if the vertex
		// is valid.
		void insert( int A, int B, double W){
		    if (W <= 0 || W == std::numeric_limits<double>::infinity()) {
                throw illegal_argument();
		    }
		    if (A > vertexNum || B > vertexNum || A < 1 || B < 1 || A == B) {
                std:: cout << "Invalid value for vertex, Enter a value between 1 and " << vertexNum << std::endl;
                throw illegal_argument();
		    }
		    Vertex* a = GetVertex(A);
		    Vertex* b = GetVertex(B);

            if (a == nullptr || b == nullptr) {
                std:: cout << "Invalid value for vertex, Enter a value between 1 and " << vertexNum << std::endl;
                throw illegal_argument();
		    }
            if (HasEdge(a, b)) {
                // Search the list of edges for an edge that goes to toVertex
                std::vector<Edge*>& edges = *fromEdges.at(a);
                for (Edge* edge : edges) {
                    if (edge->toVertex == b) {
                        edge->weight = W;
                        return;
                    }
                }
            }
            AddUndirectedEdge(a, b, W);
        }

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// You can modify this function however you want:  it will not be tested

    std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
        return out;
    }

// Is an error showing up in CIS22B.h or elsewhere?
// Did you forget a closing '}' ?

#endif
