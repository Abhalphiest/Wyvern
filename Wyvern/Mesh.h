//Margaret Dorsey
//10/21/2015

#ifndef _MESH_H_
#define _MESH_H_

#include"definitions.h"
#include"ShaderMaster.h"
#include"CameraMaster.h"
#include"MaterialMaster.h"
#include"LightMaster.h"

///<summary>
/// The Mesh class contains functions to load and generate meshes, as well as stores
/// the necessary data to render a particular mesh, including the vertex data, the various GL buffer objects,
/// and some display style booleans. 
///</summary>
///<remark>
/// The Mesh class renders using indexed vertices, for optimization. Meshes are not named on construction, but rather when they are
/// added to the Mesh Master.
///</remark>
class Mesh
{

public:
	
	///<summary>
	///Procedurally generates a cube, centered about the origin.
	///</summary>
	///<param name ="p_size">
	///The side length of the desired cube, in world space.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Cube(float p_size);
	///<summary>
	///Procedurally generates a sphere with the given number of subdivisions both latitudinally and longitudinally, centered about the origin.
	///</summary>
	///<param name ="p_radius">
	///The radius of the sphere to be generated, in world space
	///</param>
	///<param name ="p_subdivisions">
	/// The number of subdivisions desired both latitudinally and longitudinally. Will be clamped to [3,360]. Subdivisions above 50
	/// are not, in general, recommended or worth it.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Sphere(float p_radius, uint p_subdivisions);
	///<summary>
	///Procedurally generates a torus with the given number of subdivisions both latitudinally and longitudinally, centered about the origin.
	///</summary>
	///<param name ="p_innerRad">
	///The distance from the center of the torus to the innermost ring of vertices, in world space.
	///</param>
	///<param name ="p_outerRad">
	///The distance from the center of the torus to the outermost ring of vertices, in world space.
	///</param>
	///<param name ="p_subdivisions">
	/// The number of subdivisions desired both latitudinally and longitudinally. Will be clamped to [3,360]. Subdivisions above 50
	/// are not, in general, recommended or worth it.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Torus(float p_innerRad, float p_outerRad, uint p_subdivisions);
	///<summary>
	///Procedurally generates a cone with the given number of subdivisions longitudinally, centered about the origin.
	///</summary>
	///<param name ="p_radius">
	///The radius of the base of the cone, in world space.
	///</param>
	///<param name ="p_height">
	///The distance from the base to the tip of the cone, in world space.
	///</param>
	///<param name ="p_subdivisions">
	/// The number of subdivisions desired longitudinally. Will be clamped to [3,360]. Subdivisions above 50
	/// are not, in general, recommended or worth it.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Cone(float p_radius, float p_height, uint p_subdivisions);
	///<summary>
	///Procedurally generates a cylinder with the given number of subdivisions longitudinally, centered about the origin.
	///</summary>
	///<param name ="p_radius">
	///The radius of the cylinder, in world space.
	///</param>
	///<param name ="p_height">
	///The distance from the base to the top of the cylinder, in world space.
	///</param>
	///<param name ="p_subdivisions">
	/// The number of subdivisions desired longitudinally. Will be clamped to [3,360]. Subdivisions above 50
	/// are not, in general, recommended or worth it.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Cylinder(float p_radius, float p_height, uint p_subdivisions);
	///<summary>
	///Procedurally generates a pipe with the given number of subdivisions longitudinally, centered about the origin.
	///</summary> 
	///<param name ="p_innerRadius">
	///The distance from the center of the pipe to the innermost ring of faces.
	///</param>
	///<param name ="p_outerRadius">
	///The distance from the center of the pipe to the outermost ring of faces.
	///</param>
	///<param name ="p_height">
	///The distance from the base to the top of the pipe, in world space.
	///</param>
	///<param name ="p_subdivisions">
	/// The number of subdivisions desired longitudinally. Will be clamped to [3,360]. Subdivisions above 50
	/// are not, in general, recommended or worth it.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Pipe(float p_innerRadius, float p_outerRadius, float p_height, uint p_subdivisions);
	///<summary>
	///Procedurally generates a plane with the given dimensions, centered about the origin.
	///</summary> 
	///<param name ="p_width">
	///The width of the desired plane.
	///</param>
	///<param name ="p_height">
	///The distance from the base to the top of the pipe, in world space.
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Plane(float p_width, float p_height);
	///<summary>
	///Recursively generates a sphere from an icosohedron with the given number of recursions centered about the origin.
	///</summary>
	///<param name ="p_radius">
	///The radius of the sphere to be generated, in world space
	///</param>
	///<param name ="p_subdivisions">
	/// The number of recursions desired. Will be clamped to [0,60]. 0 subdivisions will give an icosohedron. 
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* Icosphere(float p_radius, uint p_subdivisions);
	///<summary>
	///Generates a complete Mesh object based on the data from an obj file
	///</summary>
	///<param name ="p_path">
	///The file path of the obj file, starting in the application directory
	///</param>
	///<returns> A pointer to the newly constructed Mesh object </returns>
	///<remark> Calls the Mesh constructor and allocates heap memory, which is the responsibility of the caller, who should either delete it
	/// manually or add it to the Mesh Master, which will handle deletions upon being released. </remark>
	static Mesh* LoadObj(const char* p_path);
	///<summary> Property for the Mesh name. </summary>
	///<returns> The name of the mesh </returns>
	String GetName(void){ return m_name; }
	///<summary> Property for the Mesh name. </summary>
	///<param name="p_name"> The desired name of the mesh. There is no checking for redundancy in this function, that is handled by the Mesh Manager.</param>
	void SetName(String p_name){ m_name = p_name;} 
	///<summary>Renders the model after transforming it with the given matrix, using the view and perspective matrices from the Camera Master</summary>
	///<param name="p_modelMatrix"> A reference to a 4x4 matrix of floats representing the position, orientation, and scale to use when rendering the mesh. </param>
	void Render(mat4 &p_modelMatrix);
	///<summary>Renders the model multiple times after transforming it with the given matrices, using the view and perspective matrices from the Camera Master</summary>
	///<param name="p_modelMatrix"> A list of  4x4 matrices of floats representing the position, orientation, and scale to use when rendering the mesh in each instance. </param>
	void RenderInstanced(std::vector<mat4> p_modelMatrices);
	///<summary> The Mesh class's destructor </summary>
	~Mesh(void); 
	///<summary> The Mesh class's assignment operator </summary>
	Mesh& operator=(Mesh& other); //assignment operator
	///<summary> The Mesh class' copy constructor </summary>
	Mesh(Mesh& other); 
	///<summary> Property for the Mesh class' wireframe display boolean </summary>
	///<param name="p_wireframe"> A boolean representing whether or not to display the mesh in wireframe when rendered. </param>
	void SetWireframe(bool p_wireframe){ m_renderWireframe = p_wireframe; }
	void SetMaterialIndex(uint p_materialIndex){ m_materialIndex = p_materialIndex; CompileMesh(); }
private:
	enum BufferType
	{
		VERTEX = 1,
		UV = 2,
		NORM = 4,
		COLOR = 8
	};

	///<summary> The Mesh class' private constructor, only called by primitive generation functions or the .obj loader. </summary>
	///<remarks> The constructor mainly sets up the OpenGL buffers and structures necessary for rendering. </remarks>
	Mesh(void); 
	///<summary>Assuming the vectors passed in are consecutive and oriented as desired, appends a quad to the index list as two tris.</summary>
	///<param name="p1"> The first vertex in the quad </param>
	///<param name="p2"> The second vertex in the quad </param>
	///<param name="p3"> The third vertex in the quad </param>
	///<param name="p4"> The fourth vertex in the quad </param>
	///<remark>"Correct" orientation is clockwise when facing the quad. Counter-clockwise faces are culled at render time, and non-consecutive
	/// vertices will result in non-quad geometry. The AddQuad function does not check for this.</remark>
	void AddQuad(vec3 &p1, vec3 &p2, vec3 &p3, vec3 &p4);
	///<summary>Assuming the vectors passed in are oriented as desired, appends a tri to the index list.</summary>
	///<param name="p1"> The first vertex in the tri</param>
	///<param name="p2"> The second vertex in the tri</param>
	///<param name="p3"> The third vertex in the tri</param>
	///<remark>"Correct" orientation is clockwise when facing the tri. Counter-clockwise faces are culled at render time. The AddTri function
	///does not check for orientation.</remark>
	void AddTri(vec3 &p1, vec3 &p2, vec3 &p3);
	///<summary> Checks to see if the vertex has already been used in the mesh, and if not, it adds it. Truncates vertices to the 5th decimal place before
	/// comparison to eliminate redundancy due to rounding error.</summary>
	///<param name="p"> The vertex to be be checked. </param>
	void CheckVertex(vec3 &p);
	///<summary> Passes the finished vertex and index data to the Mesh's OpenGL buffers, so that it can be rendered at will. </summary>
	void CompileMesh(void);
	///<summary>The recursive function for subdividing the icosphere. Changes the list of vertices given to it to a list of vertices of the icosphere.</summary>
	///<param name="p1"> The number of recursions remaining</param>
	///<param name="p2"> A reference to the list of vertices</param>
	///<remark>Although the function does not explicitly return anything, it passes data back through the reference parameter.</remark>
	void RecurseIcosphere(uint p_subdivisions, std::vector<vec3>& p_vertices);
	///<summary>Gives the vertex of the midpoint of the edge formed by the given vertices.</summary>
	///<param name="p1"> The first vertex of the edge</param>
	///<param name="p2"> The second vertex of the edge</param>
	///<returns> The the midpoint of the two vertices</returns>
	///<remark>DivideEdge also normalizes the vectors given as parameters, which is why it is important that they are by reference.
	///however, the length is checked before normalization just to avoid costly square roots as the vertex list becomes normalized.</remark>
	vec3 DivideEdge(vec3& p1, vec3& p2);
	///<summary>Creates a list of indices for indexed rendering from the data read by an obj - this is neccessary because
	///an obj indexes by data type (vertex, uv, etc), while OpenGL indexes by the entire set of vertex data.</summary>
	///<param name="p_vertices">The list of vertices read from the obj file</param>
	///<param name="p_uvs"> The list of uv coordinates read from the obj file</param>
	///<param name="p_normals">The list of normal vectors read from the obj file</param>
	///<param name="p_vertIndices"> The list of vertex indices read from the obj file</param>
	///<param name="p_uvIndices"> The list of uv indices read from the obj file</param>
	///<param name="p_normIndices"> The list of normal indices read from the obj file</param>
	///<returns>A boolean indicating success or failure.</returns>
	///<remark>"Correct" orientation is clockwise when facing the tri. Counter-clockwise faces are culled at render time. The AddTri function
	///does not check for orientation.</remark>
	bool IndexObj(std::vector<vec3> &p_vertices, std::vector<vec2> &p_uvs, std::vector<vec3> &p_normals, std::vector<uint> &p_vertIndices, std::vector<uint> &p_uvIndices, std::vector<uint> &p_normIndices);
	///<summary> Truncates each component of a vector to the 5th decimal place. </summary>
	///<param name="v"> The vector to be truncated </param>
	vec3 TruncateVector(const vec3& v);
	uint m_numVertices = 0;
	uint m_materialIndex;
	GLuint m_vao = 0; //vertex array object index
	GLuint m_indexBuffer = 0; //indexed rendering buffer index
	GLuint m_vertexBuffer = 0; //vertex buffer index
	GLuint m_colorBuffer = 0; //color  buffer index
	GLuint m_uvBuffer = 0; //UV buffer index
	GLuint m_normalBuffer = 0; //normal buffer index
	GLuint m_tangentBuffer = 0; //tangent buffer index
	GLuint m_bitangentBuffer = 0; //bitangent buffer index
	GLuint m_matrixBuffer; //transformation matrix buffer index
	int m_bufferType; //using the buffertype enum, determines the kind of data the mesh has associated with - ex: only vertices and color
	//lists of the actual mesh data, in the formats most easily passed to opengl
	std::vector<float> m_vertices; 
	std::vector<float> m_normals;
	std::vector<float> m_uvs;
	std::vector<uint> m_indices;
	//to check for duplicate vertices while constructing an index list
	std::map<vec3, int, vec3Comparison> m_indexMap;


	//render just the edges? 
	bool m_renderWireframe = false;

	//Master Singletons
	CameraMaster* m_cameraMaster = nullptr;
	MaterialMaster* m_materialMaster = nullptr;
	LightMaster* m_lightMaster = nullptr;
	ShaderMaster* m_shaderMaster = nullptr;

	String m_name = ""; //empty string for uninitialized name

	

};
#endif