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

      //Remove shared memory on construction and destruction
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove("MySharedMemory"); shared_memory_object::remove("Reader_has_read"); shared_memory_object::remove("Writer_has_written");}
         ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); shared_memory_object::remove("Reader_has_read");shared_memory_object::remove("Writer_has_written");}
      } remover;

      //Create a shared memory object.
      shared_memory_object shm (create_only, "MySharedMemory", read_write);
      //Set size
      shm.truncate(1000);

      //Map the whole shared memory in this process
      mapped_region region(shm, read_write);
      std::memset(region.get_address(), 1, region.get_size());
      shared_memory_object shm_signal (create_only, "Writer_has_written", read_write);
      //Write all the memory to 1
      //wait for reader to read
      while(!shared_mem_exists("Reader_has_read")){};
      return 0;
}
