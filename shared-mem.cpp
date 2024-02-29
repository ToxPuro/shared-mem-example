#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
bool
shared_mem_exists(const char* filename)
{
   using namespace boost::interprocess;
        try{
                shared_memory_object shm (open_only, filename, read_write);
                std::string name = shm.get_name();
                return(!name.empty());
        }
        catch(const std::exception & ex) {return false;}
        return true;
}

int main(int argc, char *argv[])
{

   using namespace boost::interprocess;
   for(auto name: {"MySharedMemory", "Reader_has_read", "Writer_has_writen"})
	if(shared_mem_exists(name)) shared_memory_object::remove(name);
   std::system("./shared-mem-write.o & ./shared-mem-read.o");
   return 0;
}
