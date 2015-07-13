#pragma once
#include "NFEnginePCH.hpp"
namespace nfe
{
  class NIFRAME_API IThread
  {
  public:

    IThread();
    virtual ~IThread();
    //IThread( const IThread& thread ) = delete;

    typedef void *( IThreadFunc )( void* );


    /**
    @brief Initializes a thread with a function to update and optional a name for the thread.

    @param func The function which will be run when the thread is started
    @param name The name of the thread, useful for debugging purposes

    */
    virtual void Init( IThreadFunc* func, uint32 affinity = 0, const std::string& name = "" );

    virtual void Run( void* arg = nullptr) = 0;

    const std::string& Name() const;
    void Name( const std::string& val );


  protected:
    std::string m_Name;
    IThreadFunc* m_Func;
    uint32 m_Affinity;


  };

}
