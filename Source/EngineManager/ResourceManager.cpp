#include "ResourceManager.h"

#include "../Ingredient/Mesh.h"
#include "../Ingredient/Model.h"
#include <iostream>


// function to get the file extension from a file name
std::string getFileExtension(const std::string& filename)
{
	std::filesystem::path path(filename);
	return path.extension().string();
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto& texture : m_textures)
	{
		glDeleteTextures(1, &texture.second);
	}
	m_textures.clear();
    for (auto& model : m_models) {

    }
}

GLuint ResourceManager::getTexture(std::string texturePath)
{
	if (m_textures.find(texturePath) != m_textures.end())
	{
		return m_textures[texturePath];
	}
	else
	{
		if (loadTexture(texturePath))
		{
			return m_textures[texturePath];
		}
		else
		{
			std::cerr << "Failed to load texture: " << texturePath << std::endl;
			return -1;
		}
	}
	return 0;
}

bool ResourceManager::loadTexture(std::string texturePath)
{
    if (m_textures.find(texturePath) != m_textures.end()) {
        // Texture already loaded
        return true;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        // Store texture in the map
        m_textures[texturePath] = textureID;
        return true;
    }
    else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        stbi_image_free(data);
        return false;
    }
}


Model* ResourceManager::getModel(std::string modelPath)
{
    if (m_models.find(modelPath) != m_models.end()) {
        return m_models[modelPath];
    } else {
        if (loadModel(modelPath)) {
            return m_models[modelPath];
        } else {
            std::cerr << "Failed to load model: " << modelPath << std::endl;
            return nullptr;
        }
	}
}

bool ResourceManager::loadModel(std::string modelPath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return false;
    }

    Model* model = new Model();
    model->setDirectory(modelPath.substr(0, modelPath.find_last_of('/')));
    processNode(scene->mRootNode, scene, model);
    m_models[modelPath] = model;
    return true;
}

void ResourceManager::processNode(aiNode* node, const aiScene* scene, Model* model)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model->addMesh(processMesh(mesh, scene, model));
    }

    for (unsigned int i = 0 ; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, model);
	}
}

Mesh* ResourceManager::processMesh(aiMesh* mesh, const aiScene* scene, Model* model)
{
    // data to fill
    std::vector<ModelVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        ModelVertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.textureCoord = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.textureCoord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", model);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", model);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", model);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", model);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
	return new Mesh(vertices, indices, textures);
}

std::vector<Texture> ResourceManager::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Model* model)
{
    std::vector<Texture> textures;
	std::vector<Texture> textures_loaded = model->getTextures();
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
			std::string fullPath = model->getDirectory() + '/' + str.C_Str();
            Texture texture;
			texture.id = loadTexture(fullPath);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            model->addTexture(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }
    }
    return textures;
}
