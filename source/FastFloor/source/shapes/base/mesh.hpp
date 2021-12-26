#pragma once

#include "common.hpp"

namespace ogl
{
   static constexpr int MAX_BONE_INFLUENCE{ 4 };

   struct Vertex 
   {
      glm::vec3 Position;
      glm::vec3 Normal;
      glm::vec2 TexCoords;
      glm::vec3 Tangent;
      glm::vec3 Bitangent;

      std::array<int, MAX_BONE_INFLUENCE> m_boneIds;
      std::array<float, MAX_BONE_INFLUENCE> m_weights;
   };

   struct Texture
   {
      unsigned int id{ 0 };
      std::string type;
      std::string path;
   };

   using VertexVec = std::vector<Vertex>;
   using TextureVec = std::vector<Texture>;
   using IndicesVec = std::vector<unsigned int>;

   class Mesh
   {
   public:
      unsigned int m_VAO{ 0 };
      VertexVec m_vertices;
      IndicesVec m_indices;
      TextureVec m_textures;

      Mesh(VertexVec vertices, IndicesVec indices, TextureVec textures)
         : m_vertices(vertices), m_indices(indices), m_textures(textures)
      {
         setupMesh();
      }

      // render the mesh
      void Draw(Shader& shader)
      {
         // bind appropriate textures
         unsigned int diffuseNr = 1;
         unsigned int specularNr = 1;
         unsigned int normalNr = 1;
         unsigned int heightNr = 1;

         for (unsigned int i = 0; i < m_textures.size(); i++)
         {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                                              // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
               number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
               number = std::to_string(specularNr++); // transfer unsigned int to string
            else if (name == "texture_normal")
               number = std::to_string(normalNr++); // transfer unsigned int to string
            else if (name == "texture_height")
               number = std::to_string(heightNr++); // transfer unsigned int to string

                                                    // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
         }

         // draw mesh
         glBindVertexArray(m_VAO);
         glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
         glBindVertexArray(0);

         // always good practice to set everything back to defaults once configured.
         glActiveTexture(GL_TEXTURE0);
      }

   private:
      unsigned int m_VBO{ 0 };
      unsigned int m_EBO{ 0 };

      // initial all buffer objects/arrays
      void setupMesh()
      {
         // create buffers/arrays
         glGenVertexArrays(1, &m_VAO);
         glGenBuffers(1, &m_VBO);
         glGenBuffers(1, &m_EBO);

         glBindVertexArray(m_VAO);
         // load data into vertex buffers
         glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
         // A great thing about structs is that their memory layout is sequential for all its items.
         // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
         // again translates to 3/2 floats which translates to a byte array.
         glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

         // set the vertex attribute pointers
         // vertex Positions
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

         // vertex normals
         glEnableVertexAttribArray(1);
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

         // vertex texture coords
         glEnableVertexAttribArray(2);
         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

         // vertex tangent
         glEnableVertexAttribArray(3);
         glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

         // vertex bitangent
         glEnableVertexAttribArray(4);
         glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

         // ids
         glEnableVertexAttribArray(5);
         glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_boneIds));

         // weights
         glEnableVertexAttribArray(6);
         glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_weights));
         glBindVertexArray(0);
      }
   };
}
