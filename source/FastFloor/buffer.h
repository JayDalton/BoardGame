#pragma once

#include <SDL2/SDL_opengl>

class BufferObject
{
public:
    BufferObject(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
    {
        glGenBuffers(1, &object_);
        glBindBuffer(target, object_);
        glBufferData(target, size, data, usage);
        glBindBuffer(target, 0);
    }
    
    //Cannot be copied.
    BufferObject(const BufferObject &) = delete;
    BufferObject &operator=(const BufferObject &) = delete;
    
    //Can be moved
    BufferObject(BufferObject &&other) noexcept 
       : object_(other.Release())
    {}
    
    //Self-assignment is OK with this implementation.
    BufferObject &operator=(BufferObject &&other) noexcept
    {
        Reset(other.Release());
    }
    
    //Destroys the old buffer and claims ownership of a new buffer object.
    //It's OK to call glDeleteBuffers on buffer object 0.
    GLuint Reset(GLuint object = 0)
    {
        glDeleteBuffers(1, &object_);
        object_ = object;
    }
    
    //Relinquishes ownership of the object without destroying it
    GLuint Release()
    {
        GLuint ret = object_;
        object_ = 0;
        return ret;
    }    
    
    ~BufferObject()
    {
        Reset();
    }
    
    //Accessors and manipulators
    void Bind(GLenum target) const 
    {
       glBindBuffer(target, object_);
    }
    GLuint GetObject() const { return object_; }

private:
    GLuint object_;
};

BufferObject CreateStaticBuffer(GLsizeiptr byteSize) 
{ 
   return BufferObject(GL_ARRAY_BUFFER, byteSize, nullptr, GL_STATIC_DRAW); 
}

class BindBuffer
{
public:
   BindBuffer(GLenum target, const BufferObject& buff) 
      : target_(target)
   {
      buff.Bind(target_);
   }

   //Non-copyable.
   BindBuffer(const BindBuffer&) = delete;
   BindBuffer& operator=(const BindBuffer&) = delete;

   //Move-constructible.
   BindBuffer(BindBuffer&& other) noexcept 
      : target_(other.target_)
   {
      other.target_ = 0;
   }

   //Not move-assignable.
   BindBuffer& operator=(BindBuffer&&) = delete;

   ~BindBuffer()
   {
      //Only unbind if not moved from.
      if (target_)
      {
         glBindBuffer(target_, 0);
      }
   }

private:
   GLenum target_;
};
