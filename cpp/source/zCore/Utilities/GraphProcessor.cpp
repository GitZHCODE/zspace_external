#include <headers/zApp/include/zObjects.h>
#include <headers/zApp/include/zFnSets.h>
#include <stack>

using namespace std;

namespace zSpace
{
	class GraphProcessor
	{
	public:
		GraphProcessor() {};
		~GraphProcessor() {};

		vector<zObjGraph> separateGraph(zObjGraph& inputGraph)
		{
			vector<zObjGraph> separated_graphs;
			zFnGraph fnGraph(inputGraph);

			// If graph is empty, return empty vector
			if (fnGraph.numVertices() == 0) return separated_graphs;

			// Track visited vertices
			vector<bool> visited(fnGraph.numVertices(), false);

			// Process each unvisited vertex to find components
			for (int startVertex = 0; startVertex < fnGraph.numVertices(); startVertex++)
			{
				if (visited[startVertex]) continue;

				// Initialize new component
				vector<zVector> componentVertices;
				vector<int> componentEdges;
				map<int, int> oldToNewIndex;

				// Use stack for DFS
				stack<int> dfsStack;
				dfsStack.push(startVertex);

				// First pass: collect vertices
				while (!dfsStack.empty())
				{
					int currentVertex = dfsStack.top();
					dfsStack.pop();

					if (!visited[currentVertex])
					{
						visited[currentVertex] = true;

						// Add vertex to component
						//cout << "\n currentVertex: " << currentVertex;
						//cout << "\n numVertex: " << fnGraph.numVertices();

						zItGraphVertex v(inputGraph, currentVertex);
						if (!v.checkValency(0))
						{
							componentVertices.push_back(v.getPosition());
							oldToNewIndex[currentVertex] = componentVertices.size() - 1;

							// Get connected vertices

							vector<int> connectedVerts;
							v.getConnectedVertices(connectedVerts);

							// Add unvisited neighbors to stack
							for (int neighbor : connectedVerts)
							{
								if (!visited[neighbor])
								{
									dfsStack.push(neighbor);
								}
							}
						}
					}
				}

				// Second pass: collect edges
				for (auto& pair : oldToNewIndex)
				{
					int oldIndex = pair.first;
					zItGraphVertex v(inputGraph, oldIndex);

					vector<int> connectedVerts;
					v.getConnectedVertices(connectedVerts);

					for (int neighbor : connectedVerts)
					{
						// Add edge if both vertices are in this component
						if (oldToNewIndex.find(neighbor) != oldToNewIndex.end())
						{
							// For each vertex pair, only add the edge once
							if (oldIndex < neighbor ||
								// Special case: add closing edge for the last vertex in a loop
								(oldIndex == componentVertices.size() - 1 && neighbor == 0))
							{
								componentEdges.push_back(oldToNewIndex[oldIndex]);
								componentEdges.push_back(oldToNewIndex[neighbor]);
							}
						}
					}
				}

				// Create new graph component if valid
				if (componentVertices.size() >= 2 && !componentEdges.empty())
				{
					zObjGraph component;
					zFnGraph fnComponent(component);
					fnComponent.create(componentVertices, componentEdges);
					separated_graphs.push_back(component);
				}
			}

			return separated_graphs;
		}

		void mergeVertices(zObjGraph& graph, double tolerance)
		{
			zFnGraph fnGraph(graph);
			
			// Get original data
			zPointArray vertexPositions;
			zIntArray edgeConnections;
			fnGraph.getVertexPositions(vertexPositions);
			fnGraph.getEdgeData(edgeConnections);
			
			// Maps original vertex indices to new indices
			std::vector<int> vertexMapping(vertexPositions.size(), -1);
			
			// New vertex positions
			zPointArray newPositions;
			
			// First pass: Group vertices by proximity
			for (int i = 0; i < vertexPositions.size(); i++) {
				// Skip if this vertex is already mapped
				if (vertexMapping[i] != -1) continue;
				
				// This is a new unique vertex
				int newIndex = newPositions.size();
				newPositions.push_back(vertexPositions[i]);
				vertexMapping[i] = newIndex;
				
				// Find all vertices close to this one
				for (int j = i + 1; j < vertexPositions.size(); j++) {
					if (vertexMapping[j] == -1 && 
						vertexPositions[i].distanceTo(vertexPositions[j]) < tolerance) {
						// Merge j into i
						vertexMapping[j] = newIndex;
					}
				}
			}
			
			// Second pass: Update edge connections
			zIntArray newConnections;
			for (int i = 0; i < edgeConnections.size(); i++) {
				newConnections.push_back(vertexMapping[edgeConnections[i]]);
			}
			
			// Report results
			int numMerged = vertexPositions.size() - newPositions.size();
			// if (numMerged > 0) {
			// 	printf("\033[0;32m");
			// 	printf("\n Merged %d vert%s\n", numMerged, numMerged == 1 ? "ex" : "ices");
			// 	printf("\033[0m");
			// }
			
			// Recreate graph with new data
			fnGraph.create(newPositions, newConnections);
		}

		void resampleGraph(zObjGraph& oGraph, double sampleDist)
		{
			zItGraphHalfEdge he(oGraph, 0);

			for (zItGraphHalfEdge he_check(oGraph); !he_check.end(); he_check++)
			{
				if (he_check.getStartVertex().checkValency(1))
				{
					he = he_check;
					break;
				}
			}

			zPointArray pos;
			zIntArray pConnects;

			int startId = he.getId();
			pos.push_back(he.getStartVertex().getPosition());

			int counter = 0;
			zPoint pt = pos[0];
			double acc_dist = 0;
			do {
				pt = he.getStartVertex().getPosition();
				acc_dist += he.getPrev().getLength();
				if (acc_dist > sampleDist)
				{
					pos.push_back(pt);
					pConnects.push_back(counter);
					pConnects.push_back(counter + 1);
					counter++;
					acc_dist = 0;
				}
				he = he.getNext();

			} while (!he.getVertex().checkValency(1) && he.getId() != startId);

			pos.push_back(he.getVertex().getPosition());
			pConnects.push_back(counter);
			pConnects.push_back(counter + 1);

			zFnGraph fnGraph(oGraph);
			fnGraph.create(pos, pConnects);
		}

		bool makeClosed(zObjGraph& oGraph)
		{
			zFnGraph fnGraph(oGraph);
			zItGraphVertex v0(oGraph, 0);
			zItGraphVertex v1(oGraph, fnGraph.numVertices() - 1);

			if (v0.checkValency(1) && v1.checkValency(1))
			{
				zPointArray pos;
				zIntArray edgeConnects;
				fnGraph.getVertexPositions(pos);
				fnGraph.getEdgeData(edgeConnects);

				edgeConnects.push_back(fnGraph.numVertices() - 1);
				edgeConnects.push_back(0);
				pos.push_back(pos[0]);

				fnGraph.create(pos, edgeConnects);
				return true;
			}
			else return false;
		}

		private:

			int get_corrected_id(std::unordered_map<int, int>& map, int id_to_check, int id_to_set)
			{
				if (map.count(id_to_check))
					return map[id_to_check];
				else
				{
					map[id_to_check] = id_to_set;
					return -1;
				}
			};

	};
}