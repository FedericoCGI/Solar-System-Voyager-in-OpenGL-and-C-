#include "Model.h"

using namespace std;
using namespace glm;

Model::Model(string const &path,  bool gamma) : gammaCorrection(gamma) //constructor
{
	
	
	this->path=path;
	loadModel(path);//load the model set at filnema path specified
	
}



void Model::Draw(ShaderLinker* shaderProgram)//draw the model
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(shaderProgram);//for each mesh call its draw function
	}
	
}


void Model::loadModel(string const &path)//load a 3D Model given its filename path 
{
	//we use Assimp to load the model into a data structure of Assimp (called a scene object--> it's a root object)--> see page 157 of the book 

	//read and load a model file via Assimp
	Assimp::Importer importer;//declare an importer object from assimp namespace

	//create an aiScene object (root object)
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);//filepath-postprocessing option:
	//aiProcess_Triangulate--> force to transform model primitives into tringles
	//aiProcess_FlipUVs--> flip the u,v texture coordinates on the y-axis where necessary during the process

	//check for reading and loading errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)//if scene and its root node are null and check if the returned data is incomplete
	{
		cout << "\nERROR::ASSIMP::" << importer.GetErrorString() << endl;//specifies what the loading-error is!
		return;
	}
	else
	{
		cout << "\nAssimp Imported !" << endl;
	}

	//retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));
	

	//process all the scene's node, starting with the first node (root node)

	//process Assimp rootnode recorsively
	processNode(scene->mRootNode, scene);//
}

/*Each node contains a set of meshes indices, where each index points to a specific mesh located in the scene object.
 We want to retrieve these mesh indices, thus retrieve each mesh, and then process each mesh 
 */

void Model::processNode(aiNode* node, const aiScene* scene)//process scene object node recursively
{
	//process all the node's meshes (if any)
	for ( int i = 0; i < node->mNumMeshes; i++)
	{
		//the object node contains indices only, just to specify the actual considered object in the scene
		//otherwise, the scene contains all the data!
		
		//0.scene has an array called mMeshes, wich contains all the meshes of the scene (all scene's meshes)
		//to access to this array we need indices provided by aiNode structure
		
		//0.every node contains some meshes: node->mMeshes
		//1.so, we consider each meshe of the current node and for each mesh, we got the meshe's index in the scene (we name it as Meshe Scene Index MSI)
		
		//2.we can use the MSI index  to access to scene's mMeshes array
		//3.scene->mMeshes[MSI] returns a mesh, in particular it returns the i mesh of the current node

		//0.Example: in this current noed we have tre meshes: 0-->M1, 1-->M2, 2-->M3
		//1.node->mMeshes[0] return M1 index in the scene's mMesh array, for example we suppose to be 12
		//2. so, 12=node->mMeshes[0]. Using 12 I can access to the scene's meshes array!
		//3.we now pass 12 to scene->mMeshes: scene->mMeshes[12] = M1 , inasmuch it returns the a mesh (M1) of the scene

		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		
		this->meshes.push_back(processMesh(mesh, scene));//we proceeds the returned mesh nad then we add it to the vector<Mesh> meshes !
	}

	//then do the same thing for each children of the node (search for mesh and proceed it, and then add it to vector<Mesh> meshes)
	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);//the recursive function stops running when a node has no children to process!--> see Hanoi Tower Example !
	}
}


//now we process the mesh
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)//process mesh
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Textures> textures;

	//we can process a mesh in 3 step:
	//	1. retrieve vertex data
	//	2. retrieve meshes' indices
	//	3. retrieve material data

	for (int i = 0; i < mesh->mNumVertices; i++)//1. retrieve vertex data (we loop for each vertices conatined in the mesh we are processing)--> mNumVertices stands for meshNumberofVertices
	{
		Vertex vertex;//define a Mesh::vertex structure. We're gonna add it at vertices array after each iteration
		vec3 v;//we need to define a temp variable we can use to import data from Assimp to our Vertex structure

		//process vertex

		//process position
		v.x = mesh->mVertices[i].x;
		v.y = mesh->mVertices[i].y;
		v.z = mesh->mVertices[i].z;

		vertex.Position = v;

		//process normals
		v.x = mesh->mNormals[i].x;
		v.y = mesh->mNormals[i].y;
		v.z = mesh->mNormals[i].z;
		vertex.Normal = v;

		//process texture coordinates
		if (mesh->mTextureCoords[0])//Assimp have 8 texture coordinates per vertex, but we only care about the first texture coordinates set (u,v)--> if texture coordinate are not NULL, so the mesh contain texture coordinates
		{
			vec2 vect;//define a temp variable to copy data from Assimp to vertex structure
			vect.x = mesh->mTextureCoords[0][i].x;
			vect.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vect;
		}
		else
		{
			vertex.TexCoords = vec2(0.0f, 0.0f);
		}

		//tangent
		v.x = mesh->mTangents[i].x;
		v.y = mesh->mTangents[i].y;
		v.z = mesh->mTangents[i].z;
		vertex.Tangent = v;

		//bitangent
		v.x = mesh->mBitangents[i].x;
		v.y = mesh->mBitangents[i].y;
		v.z = mesh->mBitangents[i].z;
		vertex.Bitangent = v;

		vertices.push_back(vertex);//add vertex to vertices vector at the end of each iteration

		//this process is repeated for each vertex of the mesh

	}

	//process face

	//retrieve mesh face and retrieve the corrisponding vertex indices. Each mesh has an array of faces where each face isnrepresented by a primitive (triangle)
	//A face contains indices that define which vertex we need to draw and in what order for each primitive
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i]; //retrieve face 

		for (int j = 0; j < face.mNumIndices; j++)//retrieve vertex indices
		{
			indices.push_back(face.mIndices[j]);//store face indices in the vector<unsigned int> indices. this indices will be drawn via Mesh glDrawElements
		}
	}

	//process materials

	//a mesh only contains an index to a material object. 
	//material of a mesh is contained in scene material array and mesh's material index is set in materialIndex property.
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];//retrieve material index of the current mesh. Pass this resulting index to scene's material array to get the material

	//we are now using a Mesh::struct Textures vector

	//load mesh 's textures
	//a meterial object stores an array of texture llcation for each texture type.
	//
	
	//1. diffuse maps
	vector<Textures> diffuse_map = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");//retrieve diffuse texture from material
	textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());//copy elements that are in the [diffeuse_maps.begin(), diffuse_map.end()) range and insert them at textures.end() position

	//2. specular maps
	vector<Textures> specular_map = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specular_map.begin(), specular_map.end());//copy elements that are in the range [sm.begin(), sm.end()) and add them at t.end() position

	//3. normal maps
	vector<Textures> normal_map = loadMaterialTexture(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normal_map.begin(), normal_map.end());//copy elements in [nm.begin(), nm.end()) range and insert them to t.end() position

	//4. height map (create mountains model by a plant)
	vector<Textures> height_map = loadMaterialTexture(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), height_map.begin(), height_map.end()); //copy elements in [hm.begin(), hm.end()) range and insert them at t.end() position

	//return a mesh object

	return Mesh(vertices, indices, textures);
	
}

//retrieve texture from material
vector<Textures> Model::loadMaterialTexture(aiMaterial *material, aiTextureType type, string typeName)// load the texture of a given material and return a Mesh::Textures struct
{
	vector<Textures> textures;
	for (int i = 0; i < material->GetTextureCount(type); i++)//we iterate over all the texture locations of the given texture type
	{
		aiString str;
		material->GetTexture(type, i, &str);//retrieve texture file location

		//checkm if the texture has been loaded before, skip in case
		bool skip = false;
		for (int j = 0; j < this->texture_loaded.size(); j++)
		{
			if (strcmp(texture_loaded[j].path.data(), str.C_Str()) == 0)//texture path==str , exture already loaded
			{
				textures.push_back(texture_loaded[j]);//use texture loaded and add it to textures  structure
				skip = true; //a texture with the same filepath has already been loaded, skip the generation texture part
				break;
			}
		}

		if (!skip)//if texture has not been loaded yet
		{
			//load  not loaded textures
			
			Texture tex(GL_TEXTURE_2D);

			//load texture
			string filename = string(str.C_Str());
			filename = this->directory + '/' + filename;
			
			tex.load(filename.c_str(),0);//texture path is given by TextureFromFile(str,this->directory)

			//set texture object 
			tex.texWrapping(GL_TEXTURE_WRAP_S, GL_REPEAT);
			tex.texWrapping(GL_TEXTURE_WRAP_T, GL_REPEAT);
			tex.texFiltering(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			tex.texFiltering(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//assign texture object to texture structure
			Textures texts;//struct

			//store information in the textures structure
			texts.id = tex.getTexture();
			texts.type = typeName;
			texts.path = str.C_Str();
			//add texture to vector<Textures> textures
			textures.push_back(texts);
			//store texture as a texture loaded to avoid loading duplicated textures
			texture_loaded.push_back(texts);
		}


	}

	return textures;
}




Model::~Model()//destructor
{
	cout << "\nModel deleted!" << endl;
}
